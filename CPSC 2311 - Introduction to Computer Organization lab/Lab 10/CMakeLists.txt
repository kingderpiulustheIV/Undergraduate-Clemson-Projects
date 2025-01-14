cmake_minimum_required(VERSION 3.27)
project(Lab_10 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Lab_10
        ppm_utils.c
        main.c
        ppm_utils.h)
