// BLAS Math library
// The linked math library will depend on preprocessor definitions (MKL vs handwritten)

#if MATH_LIB_MKL == 1
    // MKL will be linked. Function implemented externally
    // Note, while mkl implementations use the same arguments the function names are different.
    #include "mkl.h"
    typedef MKL_INT BLAS_INT;

    #define dasum cblas_dasum
#else
    // Hand-written implementation of math functions required
    typedef unsigned long BLAS_INT;

    double dasum(const BLAS_INT n, const double *x, const BLAS_INT incx);
#endif
