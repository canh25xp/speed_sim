cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(speed_sim)

find_package(CLI11 CONFIG REQUIRED)

add_executable(speed_sim main.cpp)

target_link_libraries(speed_sim PRIVATE CLI11::CLI11)
