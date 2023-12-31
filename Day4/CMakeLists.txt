cmake_minimum_required(VERSION 3.16.3)
project(AdventOfCode2023)

add_executable(Day4.exe Day4.cpp)

target_link_libraries(Day4.exe PRIVATE testLib)