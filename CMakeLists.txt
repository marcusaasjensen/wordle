cmake_minimum_required(VERSION 3.24)
project(wordle C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(SOURCE_FILES ./src/main.c ./src/functions.c)
add_executable(wordle ./src/main.c ./src/functions.c)