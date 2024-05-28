add_executable(speed_sim main.cpp simulation.cpp ../src/csv.cpp ../src/parser.cpp)

target_link_libraries(speed_sim PUBLIC compiler_flags)
