cmake_minimum_required(VERSION 3.12)
project(samknows)

set(CMAKE_C_STANDARD 11)

set(COMPILE_FLAGS "-std=c11 -pedantic -O3 -Winit-self -Wextra -Wall -Wundef -Wshadow")

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

add_definitions(${COMPILE_FLAGS})

add_subdirectory(lib)

add_subdirectory(examples)
