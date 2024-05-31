add_executable(speed_comm main.cpp)

target_link_libraries(speed_comm PUBLIC compiler_flags)

set_target_properties(speed_comm PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
