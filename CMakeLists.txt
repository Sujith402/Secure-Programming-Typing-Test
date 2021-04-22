cmake_minimum_required(VERSION 3.10)
set(C_STANDARD 11)

project(TypingTest VERSION 1.0)

file(GLOB_RECURSE SRC_FILES src/*.c)
file(GLOB_RECURSE HDR_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
add_executable(TypingTest ${SRC_FILES})

#target_include_directories(TypingTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
#set(HEADER_FILES, input.h,terminal.h)

target_link_libraries(TypingTest PUBLIC ncurses)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/AddSplint.cmake)
add_splint(TypingTest ${SRC_FILES} ${HDR_FILES})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
