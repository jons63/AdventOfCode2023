cmake_minimum_required(VERSION 3.16.3)

add_library(Day7 src/Day7.cpp)

target_link_libraries(Day7 PRIVATE testLib)
target_include_directories(Day7 PRIVATE include)

add_subdirectory(test)