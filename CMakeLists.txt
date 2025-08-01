cmake_minimum_required(VERSION 3.31)
project(first)

set(CMAKE_CXX_STANDARD 11)

add_executable(first main.cpp)
add_executable(new_target main.cpp)
target_link_libraries(first libeasyx.a)