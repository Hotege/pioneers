project(pioneers)
cmake_minimum_required(VERSION 2.8)

include_directories(
    ${PNG_INCLUDE_DIR}
    ${ZLIB_INCLUDE_DIR}
    ${LUA_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
)

link_directories(
    ${PNG_LINK_DIR}
    ${ZLIB_LINK_DIR}
    ${LUA_LINK_DIR}
    ${GLFW_LINK_DIR}
)

add_subdirectory(file)
add_subdirectory(crypt)
add_subdirectory(resources)
add_subdirectory(image)
add_subdirectory(gatherer)
add_subdirectory(pack)
add_subdirectory(game)
add_subdirectory(test)

install(FILES README.md DESTINATION .)