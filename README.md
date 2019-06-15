# String Finder   

Programme to search phrase in text file made as Eset C++ developer challenge.   

* Portable. Was developed, compiled and tested on Windows 7 (Visual Studio 2019 with MSVC v142) & Fedora 30 (Clang 8.0).
* Independent. Does not have any external dependencies, except C\++17 compiler support (C++14 using std\::experimental\::filesystem).
* Multithreaded. Could use 3-X thread (main thread, Traversing path thread, X searching threads).   
* Modularised. Could be added new searching algorithms or use Boost library for file traversing.

## Compile
- clone this repository

#### From Windows:
* Using Visual Studio 2019 solution file, compile and run.
* Using other IDE (like Clion), create project, add all source files (\*.cpp & \*.hpp).

#### From Linux:
* Using IDE (like Clion), create project, add all source files (\*.cpp & \*.hpp).
* make using terminal and choosed compiler (default is clang++).

## Run
- Using run from Visual Studio or other IDE with set up parameters.
- From terminal using command:

```bash
./app <path> <phrase>
```

\<path> - path for file or directory with length in range \<3, 128>  
\<phrase> - searched phrase in files with length in range \<3, 1000>  

