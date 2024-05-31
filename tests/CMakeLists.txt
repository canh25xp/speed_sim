# Add test executable
add_executable(test_parser test_parser.cpp ../shared/parser.cpp)
add_executable(test_csv test_csv.cpp ../shared/csv.cpp)
configure_file(${CMAKE_SOURCE_DIR}/tests/test.csv ${CMAKE_BINARY_DIR}/tests COPYONLY)
target_link_libraries(test_parser PUBLIC compiler_flags)

target_include_directories(test_parser PRIVATE ${CMAKE_SOURCE_DIR}/shared)

