cmake_minimum_required(VERSION 3.21)
project(chip8)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(vendor/gflags)

add_executable(${CMAKE_PROJECT_NAME} main.cpp core/rom.cpp core/rom.h emulator.cpp emulator.h core/cpu.h core/cpu.cpp core/cpu.h)

target_link_libraries(chip8 gflags)