set(TARGET hello_norm)

add_executable(${TARGET} hello_norm.c)

target_link_libraries(${TARGET} PUBLIC blas_lib)
