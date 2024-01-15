// Math Library
// The linked math library will depend on preprocessor definitions (MKL vs handwritten)
#ifndef __MATHLIB_H__
#define __MATHLIB_H__
#endif

#if MATH_LIB_SELECTED == 1 // MKL
    // MKL will be linked. Function implemented externally
    // Note, while mkl implementations use the same arguments the function names are different.
    #include "mkl.h"

#elif MATH_LIB_SELECTED == 2 // Apple
    //#include <vecLib/cblas.h>
    #include <Accelerate/Accelerate.h>

#else
    // Hand-written implementation of math functions required
    double cblas_dasum(const int n, const double *x, const int incx);
#endif
