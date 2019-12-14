cmake_minimum_required(VERSION 3.15)
project(SimpleChess)

set(CMAKE_CXX_STANDARD 14)

add_executable(SimpleChess main.cpp Chess.cpp Chess.h)