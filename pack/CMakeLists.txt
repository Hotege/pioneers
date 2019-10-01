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
    gatherer
    lualib
)

add_executable(pack ${srcs})

if(UPX_PROGRAM)
    add_custom_command(
        TARGET pack
        COMMAND ${UPX_PROGRAM} "pack.exe" "-9"
    )
endif()

add_custom_command(
    TARGET pack
    COMMAND ".\\pack.exe" ARGS "${PROJECT_SOURCE_DIR}/scripts" "./package/scripts.lzp"
)

install(FILES ../build/pack/package/scripts.lzp DESTINATION game/bin)