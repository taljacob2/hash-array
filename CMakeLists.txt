cmake_minimum_required(VERSION 3.16)
project(HashArray C)

set(CMAKE_C_STANDARD 99)

add_executable(HashArray main.c Hash.h Bool.h)