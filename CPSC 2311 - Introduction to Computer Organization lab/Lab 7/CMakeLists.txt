cmake_minimum_required(VERSION 3.27)
project(Lab_7 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Lab_7
        ppmDriver.c
        ppmUtil.c
        ppmUtil.h)
