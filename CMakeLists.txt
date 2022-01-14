cmake_minimum_required(VERSION 3.21)
project(http_server C)

set(CMAKE_C_STANDARD 99)

add_executable(http_server main.c tcp.c tcp.h http.c http.h utils.c utils.h)
