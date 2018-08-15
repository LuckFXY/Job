cmake_minimum_required(VERSION 3.8)
project(Leetcode)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp bag_problem_9.cpp 95_Unique_Binary_Search_Trees_II.cpp 842_Split_Array_into_Fibonacci_Sequence.cpp)
add_executable(Leetcode ${SOURCE_FILES})