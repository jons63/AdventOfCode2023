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

add_executable(main main.cpp)
target_include_directories(main PRIVATE include)

target_sources(main PRIVATE
src/Day8/Day8.cpp
)

target_link_libraries(main PRIVATE testLib Day7)

set_property(TARGET main PROPERTY CXX_STANDARD 17)