cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s -Os")

file(
    GLOB srcs
    file.c
)

include_directories(
)

link_directories(
)

link_libraries(
)

add_library(file ${srcs})

install(TARGETS file DESTINATION file/lib)
install(FILES file.h DESTINATION file/include)