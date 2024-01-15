#include <math.h> // fabs
#include "mathlib.h"

double cblas_dasum(const int n, const double *x, const int incx)
{
    double rslt = 0;
    for (int i = 0; i<n; i++){
        rslt += fabs(x[i*incx]);
    }
    return rslt;
}
