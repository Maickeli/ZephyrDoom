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

file(GLOB doomgeneric_sources doomgeneric/doomgeneric/*.c)
file(GLOB doomgeneric_headers doomgeneric/doomgeneric/*.h)

target_sources(app PRIVATE
        src/main.cpp

        ${doomgeneric_sources}
        ${doomgeneric_headers}
)

