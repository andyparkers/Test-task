cmake_minimum_required(VERSION 3.12)

project(TestTask LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE) 

add_compile_options(-Wall -Wextra -Wpedantic -Werror -O3)

file(GLOB_RECURSE HEADERS "include/*.h")
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(test_task ${SOURCES} ${HEADERS})

target_include_directories(test_task
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)