#include <iostream>
#include <sys/ioctl.h>

int main(){
  struct winsize window_size;
  while(1) {
    ioctl(1, TIOCGWINSZ, &window_size);
    std::cout <<  window_size.ws_col << std::endl;
  }
}
