cmake_minimum_required (VERSION 3.19.0)

project (StringFinder_Main)

add_executable (${PROJECT_NAME} main.cpp main.hpp)

target_link_libraries (${PROJECT_NAME} PRIVATE StringFinder)