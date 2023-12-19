cmake_minimum_required(VERSION 3.26)
project(TP C)

set(CMAKE_C_STANDARD 23)

add_executable(TP main.c
        algoritmo.h
        algoritmo.c
        utils.c
        )
