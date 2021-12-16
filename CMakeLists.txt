cmake_minimum_required(VERSION 3.21)
project(chip8)

set(CMAKE_CXX_STANDARD 20)

add_executable(chip8 main.cpp emulator.cpp emulator.h)
