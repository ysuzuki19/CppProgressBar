#ifndef YSUZUKI_CPP_PROGRESS_BAR_HPP
#define YSUZUKI_CPP_PROGRESS_BAR_HPP

#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <cmath>
//#include <unistd.h>

class CppProgressBar {
  private:
    size_t progress_loop_number_;
    int preWinSize_;
    int nowWinSize_;
    std::string progress_bar_;
    std::string empty_line_;
    size_t percentage_;
    float oneHundledth_;
    std::string progress_line_;
    size_t loop_counter_;
  public:
    inline void cntSet(size_t first) {
      loop_counter_ = first;
    }
    inline size_t cntGet() {
      return loop_counter_;
    }
    inline void cntIncrement() {
      loop_counter_ ++;
    }
    void init_variable(size_t loop_number);
    void update_variable();
    inline void display_progress_bar();
    inline void finish_progress_bar();
    template <typename T> inline void stdout_in_for_progress (T& e);
};

void CppProgressBar::init_variable(size_t loop_number) {
  progress_loop_number_ = loop_number;
  struct winsize window_size;
  ioctl(1, TIOCGWINSZ, &window_size);
  percentage_ = 0;
  oneHundledth_ = loop_number/100.0;
  preWinSize_ = nowWinSize_ = window_size.ws_col;
  if(nowWinSize_ < 107) {
    progress_bar_.resize(nowWinSize_-8, '.');
    empty_line_.resize(nowWinSize_-1, ' ');
    empty_line_ += '\r';
  } else {
    progress_bar_.resize(100, '.');
    empty_line_.resize(107, ' ');
    empty_line_ += '\r';
  }
}

void CppProgressBar::update_variable() {
  /*
  //TODO: resize progress bar length for new terminal size
  struct winsize window_size;
  preWinSize_ = nowWinSize_;
  ioctl(1, TIOCGWINSZ, &window_size);
  nowWinSize_ = window_size.ws_col;
  std::cout << nowWinSize_  << std::endl;
  if(nowWinSize_!=preWinSize_) {
    std::cout << "diff" << std::endl;
    std::cout << nowWinSize_ << std::endl;
    if(nowWinSize_ < 107) {
      progress_bar_.resize(nowWinSize_-8, '.');
      empty_line_.resize(nowWinSize_-1, ' ');
      progress_bar_.resize(nowWinSize_-10, '.');
      empty_line_.resize(nowWinSize_-3, ' ');
      empty_line_ += '\r';
    } else {
      progress_bar_.resize(100, '.');
      empty_line_.resize(107, ' ');
      empty_line_ += '\r';
    }
    oneHundledth_ = progress_loop_number_/100.0;
  }
  */
  percentage_ = loop_counter_ / oneHundledth_;
  size_t k = 0;
  for(size_t j=0; j<percentage_; ++j) {
    k = std::round(j/100.0*progress_bar_.length());
    if(progress_bar_[k] != '=') {
      progress_bar_[k] = '=';
    }
  }
  progress_bar_[k] = '>';
  if(percentage_<10)
    progress_line_ = "  " + std::to_string(percentage_) + "% \[" + progress_bar_ + "]\r";
  else if(percentage_==100)
    progress_line_ = std::to_string(percentage_) + "% \[" + progress_bar_ + "]\r";
  else
    progress_line_ = ' ' + std::to_string(percentage_) + "% \[" + progress_bar_ + "]\r";
}

template <typename T> inline void CppProgressBar::stdout_in_for_progress  (T& e) {
  std::clog << empty_line_;
  std::cout << e << std::endl;
  std::clog << progress_line_;
}

inline void CppProgressBar::display_progress_bar() {
  std::clog << "\r" << progress_line_;
}

inline void CppProgressBar::finish_progress_bar() {
  for(size_t j=0; j<100 && j<progress_bar_.length()+1; ++j) {
    if(progress_bar_[j] != '=') {
      progress_bar_[j] = '=';
    }
  }
  std::clog << "100% \[" << progress_bar_ << ']' << std::endl;
}

template <typename Func>
void for_progress (size_t loop, Func process) {
  CppProgressBar cpb;
  cpb.init_variable(loop);
  for(cpb.cntSet(0); cpb.cntGet()<loop; cpb.cntIncrement()) {
    cpb.update_variable();
    std::string output_string;
    process(output_string);
    if(output_string != "") {
      cpb.stdout_in_for_progress(output_string);
    }
    cpb.display_progress_bar();
  }
  cpb.finish_progress_bar();
}

#endif /* _YSUZUKI_CPP_PROGRESS_BAR_HPP */
