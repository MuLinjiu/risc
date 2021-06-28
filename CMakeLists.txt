cmake_minimum_required(VERSION 3.19)
project(risc_v)

set(CMAKE_CXX_STANDARD 14)
###########///////
add_executable(risc_v
        main.cpp Types.hpp Simulator.hpp)
