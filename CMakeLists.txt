cmake_minimum_required(VERSION 3.10.0)
project(YADRO-test-task-magnet-tapes VERSION 0.1.0 LANGUAGES C CXX)

add_library(tape_lib
    src/tape.h
    src/tape.cpp
)

add_executable(YADRO-test-task 
src/main.cpp
)

target_link_libraries(YADRO-test-task 
    tape_lib
)

include(CTest)
enable_testing()

