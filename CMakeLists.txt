cmake_minimum_required(VERSION 3.10.0)
project(YADRO-test-task-magnet-tapes VERSION 0.1.0 LANGUAGES C CXX)

add_library(tape_lib
    src/tape.h
    src/tape.cpp
)

add_executable(YADRO-test-task 
    src/main.cpp
    src/sorter.h
    src/sorter.cpp
)

target_link_libraries(YADRO-test-task 
    tape_lib
)

include(CTest)
enable_testing()

# GoogleTest
add_subdirectory(external/googleTests)

# Test executable
add_executable(tests_runner
    test/src/test_basic.cpp
)
target_link_libraries(tests_runner
    tape_lib
    gtest_main
)

# Make sure tests can find the headers
target_include_directories(tests_runner PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

include(GoogleTest)
gtest_discover_tests(tests_runner)

