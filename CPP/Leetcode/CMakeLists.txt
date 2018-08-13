cmake_minimum_required(VERSION 3.8)
project(Leetcode)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp 654_Maximum_Binary_Tree.cpp 435_Non-overlapping_Intervals.cpp share.h)
add_executable(Leetcode ${SOURCE_FILES})