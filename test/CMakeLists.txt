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
    image
)

add_executable(test ${srcs})

if(UPX_PROGRAM)
    add_custom_command(
        TARGET test
        COMMAND ${UPX_PROGRAM} "test.exe" "-9"
    )
endif()

file(
    GLOB imgs
    ../resources/*.png
)

install(FILES ${imgs} DESTINATION test/bin)
install(TARGETS test DESTINATION test/bin)