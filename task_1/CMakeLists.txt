add_executable(speed_sim main.cpp simulation.cpp ../shared/csv.cpp ../shared/parser.cpp)

target_link_libraries(speed_sim PUBLIC compiler_flags)

set_target_properties(speed_sim PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
