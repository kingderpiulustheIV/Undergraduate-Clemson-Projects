cmake_minimum_required(VERSION 3.27)
project(lab_4 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(lab_4
        driver.c
        functions.c
        functions.h)
