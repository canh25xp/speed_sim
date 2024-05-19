cmake_minimum_required(VERSION 3.10)
project(speed_sim)

# Generate Clangd compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)

add_executable(speed_sim main.cpp parser.cpp simulation.cpp csv.cpp)

target_link_libraries(speed_sim PUBLIC compiler_flags)
