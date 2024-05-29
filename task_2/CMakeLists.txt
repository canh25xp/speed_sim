add_executable(speed_process main.cpp process.cpp ../shared/csv.cpp ../shared/parser.cpp)

target_link_libraries(speed_process PUBLIC compiler_flags)

set_target_properties(speed_process PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
