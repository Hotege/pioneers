cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s -fvisibility=hidden -ffunction-sections -fdata-sections -Wl,--gc-sections -static-libgcc")

add_definitions("-DGLFW_EXPOSE_NATIVE_WIN32")

file(
    GLOB srcs
    main.c
    core/core.c
    lua/base.c
    lua/global.c
    lua/functions.c
)

include_directories(
)

link_directories(
)

link_libraries(
    gatherer
    lualib
    glfw3
)

add_executable(game ${srcs})

if(UPX_PROGRAM)
    add_custom_command(
        TARGET game
        COMMAND ${UPX_PROGRAM} "game.exe" "-9"
    )
endif()

install(TARGETS game DESTINATION game/bin)