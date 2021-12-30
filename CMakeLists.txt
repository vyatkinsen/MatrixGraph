cmake_minimum_required(VERSION 3.20)
project(MatrixGraph C)

set(CMAKE_C_STANDARD 99)

add_library(myLib STATIC src/graph.c)

add_executable(MatrixGraph include/graph.h  src/main.c  src/graph.c asdad.cpp)
add_executable(MatrixTest include/tests.h src/tests.c)

target_link_libraries(MatrixGraph myLib)
target_link_libraries(MatrixTest myLib)