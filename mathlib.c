#include <math.h>
#include "mathlib.h"

double dasum(const BLAS_INT n, const double *x, const BLAS_INT incx)
{
    double rslt = 0;
    for (BLAS_INT i = 0; i<n; i++){
        rslt += fabs(x[i*incx]);
    }
    return rslt;
}