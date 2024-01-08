# Library-agnostic C
High level code need not depend on low-level implementations. Swapping libraries at compile time, using preprocessor directives, enables code reuse across platforms. Here we provide a simple demo of library-agnostic c code. 

As an example generalized library, [Basic Linear Algebra Subprograms (BLAS)](https://en.wikipedia.org/wiki/Basic_Linear_Algebra_Subprograms) has many implementations (e.g. Intel MKL, GSL). A specific function name may change slightly between implementations. However, a function's interface typically does not change.

Here we define a brief stand-alone application that computes the $l1$ norm of a vector. The main function, in ```app.c```, calls a routine ```dasum``` which is  defined in BLAS implementations. Our hand-written implementation is defined in ```mathlib.c```. The CMake configuration file ```CMakeLIsts.txt``` optionally chooses which implementation to utilize.

A stand-alone implementation is built and executed as follows from the terminal:
```
mkdir build
cd build
cmake ..
make
./myapp
```

Setting the CMAKE variable ```MATH_LIB_MKL``` to ```1``` will cause CMAKE to search for the MKL locally. The resulting build system will exclude ```mathlib.c``` from compilation, and link the target against the external library. After building the executable (i.e. ```make```), running the application (```./myapp```) will list the MKL version and the same $l1$ norm. 

```
cmake .. -DMATH_LIB_MKL=1
make
./myapp
```