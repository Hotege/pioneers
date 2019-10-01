cmake_minimum_required(VERSION 2.8)

file(
    GLOB srcs
    test.c
)

include_directories(
)

link_directories(
)

link_libraries(
    crypt
)

add_executable(test ${srcs})

install(TARGETS test DESTINATION test/bin)