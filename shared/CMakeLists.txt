cmake_minimum_required(VERSION 3.16.3)

add_library(testLib)

target_include_directories(testLib PUBLIC include)

add_subdirectory(src)