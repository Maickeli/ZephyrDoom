cmake_minimum_required(VERSION 3.21)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

set(CMAKE_CXX_VERSION 20)
set(CMAKE_CXX_VERSION_REQUIRED TRUE)

set(BOARD mimxrt1064_evk)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE INTERNAL "")
endif ()

list(APPEND CONF_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/prj.conf
        ${CMAKE_CURRENT_SOURCE_DIR}/prj_${CMAKE_BUILD_TYPE}.conf)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(ZephyrDoom)


set(DOOM_GENERIC_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/doomgeneric/doomgeneric")
file(GLOB doomgeneric_sources "${DOOM_GENERIC_SOURCE_DIR}/*.c")

set(SOURCES_TO_REMOVE "${DOOM_GENERIC_SOURCE_DIR}/doomgeneric_allegro.c" "${DOOM_GENERIC_SOURCE_DIR}/doomgeneric_emscripten.c" "${DOOM_GENERIC_SOURCE_DIR}/doomgeneric_sdl.c" "${DOOM_GENERIC_SOURCE_DIR}/doomgeneric_soso.c"
    "${DOOM_GENERIC_SOURCE_DIR}/doomgeneric_sosox.c" "${DOOM_GENERIC_SOURCE_DIR}/doomgeneric_win.c" "${DOOM_GENERIC_SOURCE_DIR}/doomgeneric_xlib.c"
    "${DOOM_GENERIC_SOURCE_DIR}/i_sdlmusic.c" "${DOOM_GENERIC_SOURCE_DIR}/i_sdlsound.c" "${DOOM_GENERIC_SOURCE_DIR}/i_allegromusic.c" "${DOOM_GENERIC_SOURCE_DIR}/i_allegrosound.c"
)
list(REMOVE_ITEM doomgeneric_sources ${SOURCES_TO_REMOVE})

file(GLOB doomgeneric_headers doomgeneric/doomgeneric/*.h)

add_library(doom_generic_lib STATIC
    ${doomgeneric_sources}
    ${doomgeneric_headers}
    src/doomgeneric_zephyr.c
)


target_include_directories(doom_generic_lib PUBLIC doomgeneric)

target_link_libraries(doom_generic_lib PUBLIC zephyr)


target_sources(app PRIVATE
        src/main.cpp
)

target_link_libraries(app PUBLIC doom_generic_lib)

