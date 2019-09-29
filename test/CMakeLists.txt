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
    lualib
)

add_executable(test ${srcs})

if(UPX_PROGRAM)
    add_custom_command(
        TARGET test
        COMMAND ${UPX_PROGRAM} "test.exe" "-9"
    )
endif()

install(DIRECTORY ../scripts DESTINATION test/bin)
install(TARGETS test DESTINATION test/bin)