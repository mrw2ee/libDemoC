
cmake_minimum_required(VERSION 3.13)

# Set the version number for the library
set (LIBDEMO_VERSION_MAJOR 0)
set (LIBDEMO_VERSION_MINOR 1)
set (LIBDEMO_VERSION_PATCH 2)
math (EXPR LIBDEMO_VERSION_NUMERIC "10000 * ${LIBDEMO_VERSION_MAJOR} + 100 * ${LIBDEMO_VERSION_MINOR} + ${LIBDEMO_VERSION_PATCH}")

project(libDemo
        LANGUAGES CXX C
        VERSION "${LIBDEMO_VERSION_MAJOR}.${LIBDEMO_VERSION_MINOR}.${LIBDEMO_VERSION_PATCH}")

add_subdirectory(src)

add_subdirectory(python)

add_subdirectory(exe)

