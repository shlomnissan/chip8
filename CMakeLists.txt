cmake_minimum_required(VERSION 3.21)
project(chip8)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(vendor/gflags)
add_subdirectory(vendor/SDL)

set(HEADERS
    emulator.h
    messages.h
    core/cpu.h
    core/chip8.h
    core/rom.h
    core/display.h
    core/memory.h
    os/window.h
)

set(SOURCES
    main.cpp
    emulator.cpp
    core/chip8.cpp
    core/rom.cpp
    core/memory.cpp
    os/window.cpp
        core/instructions.h)

add_executable(${CMAKE_PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(chip8 gflags SDL2-static)