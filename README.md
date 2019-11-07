# CppProgressBar
CppProgressBar is a C++ header-library to output progress bar to the terminal.

# Description

- simple progerss bar
- easy to use
- can visualize your output

# Demo
If you use this library, you can output like the gif below.

1. visualize probress bar without output
![demo_2](/demo/progressbar_nooutput.gif)

2. visualize probress bar with output
![demo_1](/demo/progressbar.gif)

# Dependencies
You need C++11 or later.

# Set up

```sh:
$ git clone https://github.com/ysuzuki19/CppProgressBar
```

This repository is header-only, so you can use without installing.
To use this header, there are 3 ways.

## 1. specify include directory
Add the following line to the top of the program.

```cpp
#include "/path/to/CppProgressBar.hpp"
```

## 2. compile option
Run following command to compile.

```sh
$ g++ main.cpp -I/path/to/CppProgressBar/include/ -o project
```

## 3. symlink
Run following command.

```sh
$ ln -s /path/to/CppProgressBar.hpp /usr/local/include/
```

# Usage
Definition lambda expression and call `for_progress(loop_number, lambda_func)` like following part.

- `loop_number` : number of loops
- `lambda_func` : your process

```cpp
int cnt = 0;
auto process = [&cnt](std::string& output_string) {
  /*your process*/
  cnt ++;
  /*if you don't need output, following line is unnecessary.*/
  output_string = /*your custom output*/;
};
for_progress(100, process);
```

Sample code is `/test/test.cpp`

# Authors
[ysuzuki19](https://github.com/ysuzuki19)

# License
[MIT](/LICENSE)

