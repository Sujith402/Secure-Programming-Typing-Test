cmake_minimum_required(VERSION 3.10)
set(C_STANDARD 11)

project(TypingTest VERSION 1.0)

file(GLOB_RECURSE SRC_FILES src/*.c)
add_executable(TypingTest ${SRC_FILES})

target_include_directories(TypingTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(TypingTest PUBLIC ncurses)
