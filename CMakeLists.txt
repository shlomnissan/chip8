cmake_minimum_required(VERSION 3.21)
project(chip8)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()

add_subdirectory(vendor/gflags)
add_subdirectory(vendor/SDL)
add_subdirectory(vendor/googletest)
add_subdirectory(tests)

set(HEADERS
    emulator.h
    messages.h
    main_loop.h
    core/chip8.h
    core/display.h
    core/memory.h
    core/input.h
    core/parser.h
    core/random.h
    core/rom.h
    core/types.h
    os/window.h
)

set(SOURCES
    main.cpp
    emulator.cpp
    core/chip8.cpp
    core/instructions.h
    core/rom.cpp
    os/window.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(chip8 gflags SDL2-static)