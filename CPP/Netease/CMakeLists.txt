cmake_minimum_required(VERSION 3.8)
project(Netease)

set(CMAKE_CXX_STANDARD 11)

#set(SOURCE_FILES main.cpp shooting_game.cpp share.h "Max_Increase_to_Keep_City_Skyline.cpp")
set(SOURCE_FILES main.cpp apple_orchard.cpp xiaoyi_dict.cpp)
add_executable(Netease ${SOURCE_FILES})