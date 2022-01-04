cmake_minimum_required(VERSION 3.21)

set(TESTS ${CMAKE_PROJECT_NAME}_tests)
set(SOURCES
    instructions_test.cpp
    parser_test.cpp
)

add_executable(${TESTS} ${SOURCES})

target_link_libraries(${TESTS} gtest_main)

target_include_directories(${TESTS} PUBLIC ${PROJECT_SRC_DIR})