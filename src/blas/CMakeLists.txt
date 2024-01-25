
set(TARGET blas_lib)

set(MATH_LIB_SELECTED 0)

#  Optionally utilize optimized libraries
if (MATH_LIB MATCHES "MKL")
    # MKL ships with tools to find libraries and headers. Not distributed with CMake 

    # https://www.intel.com/content/www/us/en/docs/onemkl/developer-guide-linux/2024-0/cmake-config-for-onemkl.html
    find_package(MKL CONFIG REQUIRED PATHS $ENV{MKLROOT})
    message("MKL_FOUND = ${MKL_FOUND}")
    message("MKL_ROOT = ${MKL_ROOT}")
    message("MKL_INCLUDE = ${MKL_INCLUDE}")
    message("MKL_ENV = ${MKL_ENV}")
    if(${MKL_FOUND})
        set(MATH_LIB_SELECTED 1)
        set(MATH_LIB_IMPORT_TARGETS "MKL::MKL")
    endif()
endif()

if (MATH_LIB MATCHES "APPLE")
    # CMake includes tools to look for BLAS libraries. However, finding information like include directory locations are left as an exercise to the user. We have hand-coded the library's header file location in mathlib.h
    set( ENV{BLA_VENDOR} "Apple" )
    find_package( BLAS REQUIRED)
    message("BLAS_FOUND = ${BLAS_FOUND}")
    message("BLAS_LIBRARIES = ${BLAS_LIBRARIES}")
    message("BLAS_LINKER_FLAGS = ${BLAS_LINKER_FLAGS}")
    message("BLAS_INCLUDE_DIRS = ${BLAS_INCLUDE_DIRS}")
    if(${BLAS_FOUND})
        set(MATH_LIB_SELECTED 2)
        set(MATH_LIB_IMPORT_TARGETS "BLAS::BLAS")

    endif()
endif()


message("MATH_LIB_SELECTED = ${MATH_LIB_SELECTED}")

# This library links to BLAS routines which may be 3rd-party libraries or hand-written code. The distinction should not matter to future targets linking to this library. However, CMake distinguishes compiled libraries (i.e. hand-written code) from header-only libraries (e.g. Intel MKL). In the following we must determine  whether this library is compiled or simply an INTERFACE (in CMake terminology). Setting preprocessor directives and shared  header directories here, users need only link to this Target. 
if(MATH_LIB_SELECTED MATCHES 0)
    message("Hand-written BLAS")
    add_library(${TARGET} STATIC mathlib.c mathlib.h)
    set(ACCESS_SPECIFICATION PUBLIC)
    
else()
    message("External library")
    add_library(${TARGET} INTERFACE)
    target_link_libraries(${TARGET} INTERFACE ${MATH_LIB_IMPORT_TARGETS})
    set(ACCESS_SPECIFICATION INTERFACE)
endif()

# Set a few things for any future targets linking to this target
# Ensure access to headers
target_include_directories(${TARGET} ${ACCESS_SPECIFICATION} .)
# Add symbols to preprocessor (#define)
target_compile_definitions(${TARGET} ${ACCESS_SPECIFICATION} MATH_LIB_SELECTED=${MATH_LIB_SELECTED})
