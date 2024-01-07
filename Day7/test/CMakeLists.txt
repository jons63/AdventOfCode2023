cmake_minimum_required(VERSION 3.16.3)

add_executable(Day7_Test Test.cpp)

target_include_directories(Day7_Test PRIVATE ../include)
target_link_libraries(Day7_Test GTest::gtest_main testLib)

include(GoogleTest)
gtest_discover_tests(Day7_Test)

target_sources(Day7_Test PRIVATE ../src/Day7.cpp)