cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

project(speed_sim)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)

add_executable(speed_sim main.cpp parser.cpp)

target_link_libraries(speed_sim PUBLIC compiler_flags)
