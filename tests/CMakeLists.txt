# Add test executable
add_executable(test_parser test_parser.cpp ../shared/parser.cpp)

target_link_libraries(test_parser PUBLIC compiler_flags)

target_include_directories(test_parser PRIVATE ${CMAKE_SOURCE_DIR}/shared)

