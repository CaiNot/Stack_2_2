cmake_minimum_required(VERSION 3.12)
project(Stack_2_2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS -static)

add_executable(Stack_2_2 main.cpp)