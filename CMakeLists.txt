cmake_minimum_required(VERSION 3.13)

if(NOT DEFINED MATH_LIB_MKL)
    set(MATH_LIB_MKL 0)
endif()


# Set the version number for the library
set (LIBDEMO_VERSION_MAJOR 0)
set (LIBDEMO_VERSION_MINOR 1)
set (LIBDEMO_VERSION_PATCH 2)
math (EXPR LIBDEMO_VERSION_NUMERIC "10000 * ${LIBDEMO_VERSION_MAJOR} + 100 * ${LIBDEMO_VERSION_MINOR} + ${LIBDEMO_VERSION_PATCH}")

project(libDemo
        LANGUAGES CXX C
        VERSION "${LIBDEMO_VERSION_MAJOR}.${LIBDEMO_VERSION_MINOR}.${LIBDEMO_VERSION_PATCH}")


set(src_files "app.c")

if (NOT MATH_LIB_MKL)
    # Hand-written implementation
    # Must include source file.
    list (APPEND src_files "mathlib.c")
else()
    # Look for Intel MKL libraries using cmake config shipped with installer.
    # Must be linked later.
    # See https://www.intel.com/content/www/us/en/docs/onemkl/developer-guide-linux/2024-0/cmake-config-for-onemkl.html
    find_package(MKL CONFIG REQUIRED PATHS $ENV{MKLROOT})
    message(MATH_LIB_MKL="${MKL_FOUND}")
    add_compile_definitions(MATH_LIB_MKL)
endif()

add_executable(myapp ${src_files})

if (MATH_LIB_MKL)
    target_link_libraries(myapp PUBLIC MKL::MKL)
endif()