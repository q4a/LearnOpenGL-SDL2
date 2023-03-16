cmake_minimum_required(VERSION 3.3)

project(LearnOpenGL-SDL)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(GLM REQUIRED glm)
pkg_check_modules(ASSIMP REQUIRED assimp)

if (MSVC)
    # For vcpkg, include path is not provided directly
    find_path(SDL2_INCLUDE_DIR SDL2/SDL.h)
endif ()

include_directories(include)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})

add_subdirectory(src)
