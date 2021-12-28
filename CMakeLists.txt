cmake_minimum_required(VERSION 3.20)
project(MatrixGraph C)

set(CMAKE_C_STANDARD 99)

add_executable(MatrixGraph include/graph.h include/tests.h src/graph.c src/main.c src/tests.c)
