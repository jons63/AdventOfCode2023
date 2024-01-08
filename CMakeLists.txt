cmake_minimum_required(VERSION 3.16.3)
project(AdventOfCode2023)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)

FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(. include)

add_subdirectory(Day1)
add_subdirectory(Day2)
add_subdirectory(Day3)
add_subdirectory(Day4)
add_subdirectory(Day5)
add_subdirectory(Day6)
add_subdirectory(Day7)
add_subdirectory(shared)

add_library(Day8 src/Day8/Day8.cpp)
target_include_directories(Day8 PRIVATE include)
target_link_libraries(Day8 PRIVATE testLib)
add_executable(main main.cpp)

target_link_libraries(main PRIVATE Day7 Day8)