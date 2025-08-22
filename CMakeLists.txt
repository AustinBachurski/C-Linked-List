cmake_minimum_required(VERSION 4.0)

project(LinkedList LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_compile_options(
    -Werror
    -Wall
    -Wcast-align
    -Wdouble-promotion
    -Wduplicated-branches
    -Wduplicated-cond
    -Wextra
    -Wconversion
    -Wimplicit-fallthrough
    -Wlogical-op
    -Wmisleading-indentation
    -Wnull-dereference
    -Wpedantic
    -Wshadow
    -Wsign-conversion
    -Wunused
)

add_subdirectory(src)

