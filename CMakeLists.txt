cmake_minimum_required(VERSION 3.21)
project(chip8)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(vendor/gflags)
add_subdirectory(vendor/SDL)

set(HEADERS
    emulator.h
    core/cpu.h
    core/rom.h
    core/display.h
    core/memory.h
    clients/client.h
    clients/sdl/sdl.h
)

set(SOURCES
    main.cpp
    emulator.cpp
    core/cpu.cpp
    core/rom.cpp
    core/memory.cpp
    clients/sdl/sdl.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(chip8 gflags SDL2-static)