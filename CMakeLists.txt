cmake_minimum_required(VERSION 3.21)
project(chip8)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(vendor/gflags)

set(HEADERS
    emulator.h
    core/cpu.h
    core/rom.h
)

set(SOURCES
    main.cpp
    emulator.cpp
    core/cpu.cpp
    core/rom.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(chip8 gflags)