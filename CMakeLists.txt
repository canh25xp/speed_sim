cmake_minimum_required(VERSION 3.22)
project(opencv_test VERSION 1.0)

find_package(OpenCV REQUIRED)

add_executable(opencv_test main.cpp)

target_link_libraries(opencv_test ${OpenCV_LIBS})