cmake_minimum_required(VERSION 3.24)
project(CompArch_coursework)

set(CMAKE_CXX_STANDARD 20)

add_executable(CompArch_coursework main.cpp Pipeline.cpp Pipeline.hpp Command.cpp Command.hpp RandGen.cpp RandGen.hpp)
