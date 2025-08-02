cmake_minimum_required(VERSION 3.31)
project(Tick-tock)

set(CMAKE_CXX_STANDARD 11)

add_executable(Tick-tock main.cpp)
target_link_libraries(Tick-tock libeasyx.a)