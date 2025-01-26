cmake_minimum_required(VERSION 3.18.4)

project(SX1278_LORA C)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_executable(sx1278
    src/main.c
    src/sx1278.c
)

target_include_directories(sx1278 PUBLIC include)
