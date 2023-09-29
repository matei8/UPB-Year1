cmake_minimum_required(VERSION 3.25)
project(SteganographyOnImages C)

set(CMAKE_C_STANDARD 99)

add_executable(SteganographyOnImages main.c comandsFunctions.c codeDecode.c)
