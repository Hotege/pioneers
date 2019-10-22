cmake_minimum_required(VERSION 2.8)

file(
    GLOB srcs
    main.c
)

include_directories(
)

link_directories(
)

link_libraries(
    file
    crypt
)

add_executable(encrypt ${srcs})

add_custom_command(
    TARGET encrypt
    COMMAND ".\\encrypt.exe"
    ARGS
    "${PROJECT_SOURCE_DIR}/resources"
    "simsun-temp.ttc"
    "graphic/icon.png"
    "graphic/background.png"
)

install(FILES ../resources/simsun-temp.ttc ../resources/simsun-temp.ttc.hbc DESTINATION game/bin)
install(DIRECTORY ../resources/graphic DESTINATION game/bin)