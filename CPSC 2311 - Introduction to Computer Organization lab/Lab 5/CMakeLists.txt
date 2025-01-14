cmake_minimum_required(VERSION 3.27)
project(Lab_5 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Lab_5
        driver.c
        functions.c
        functions.h)