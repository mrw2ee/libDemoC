#include <stdio.h>
#include "mathlib.h"

int main()
{
    /* Using preprocessor definitions, determine which math library is linked. If MKL, print version.*/
    #if MATH_LIB_SELECTED == 1
        // MKL Print version
        MKLVersion mkl_version;
        mkl_get_version(&mkl_version);
        printf("You are using oneMKL %d.%d\n", mkl_version.MajorVersion, mkl_version.UpdateVersion);
    #elif MATH_LIB_SELECTED == 2
        printf("Apple vecLib.\n");
    #else
        printf("Hand-written library.\n");
    #endif

    /* The following code does not depend on a specific math library implementation, as long as the linker can find it.*/
    double x[] = {0.8,1.1,1.3};
    double xl1;
    xl1 = cblas_dasum(3,x,1);
    printf("Vector sum %f\n", xl1);

    return 0;
}