project(pioneers)
cmake_minimum_required(VERSION 2.8)

include_directories(
    ${ZLIB_INCLUDE_DIR}
    ${LUA_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
)

link_directories(
    ${ZLIB_LINK_DIR}
    ${LUA_LINK_DIR}
    ${GLFW_LINK_DIR}
)

add_subdirectory(gatherer)
add_subdirectory(pack)
add_subdirectory(game)
add_subdirectory(test)

install(FILES README.md DESTINATION .)