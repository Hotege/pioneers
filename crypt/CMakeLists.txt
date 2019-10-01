cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s -Os")

file(
    GLOB srcs
    crypt.c
    base16.c
    table.c
)

include_directories(
)

link_directories(
)

link_libraries(
)

add_library(crypt ${srcs})