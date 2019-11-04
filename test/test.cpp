#include <iostream>
#include <string>
#include <CppProgressBar.hpp>

//TODO:remove following line
#include <chrono>
#include <thread>

using namespace std;

int main()
{
  {// for_progress test for sum
    int sums = 0;
    int cnt = 0;
    auto process = [&sums, &cnt](std::string& output_string) {
      output_string = to_string(cnt) + " : " + to_string(sums);
      // add a timed delay for visuzalizing
      std::this_thread::sleep_for(std::chrono::milliseconds(30));
      sums += cnt;
      cnt ++;
    };
    for_progress(100, process);
  }

  {// for_progress test for times
    double times = 1;
    int cnt = 1;
    auto process_2 = [&times, &cnt](std::string& output_string) {
      // add a timed delay for visuzalizing
      std::this_thread::sleep_for(std::chrono::milliseconds(30));
      times *= cnt;
      cnt ++;
    };
    for_progress(10, process_2);
  }
  return 0;
}
