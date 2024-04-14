project(SX1278_LORA C)
cmake_minimum_required(VERSION 3.18.4)


set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
include_directories(include)
set(SOURCES 
    src/main.c
    src/sx1278.c
    )

add_executable(sx1278 ${SOURCES})
