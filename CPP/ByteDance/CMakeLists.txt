cmake_minimum_required(VERSION 3.8)
project(ByteDance)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp merge_overlap.cpp Fans_group.cpp share.h tools.cpp)
add_executable(ByteDance ${SOURCE_FILES})