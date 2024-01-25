# Library-agnostic C

High level code need not depend on low-level implementations. Swapping libraries at compile time, using preprocessor directives, enables efficiency and portability across platforms. Here we provide a simple demo of library-agnostic C code, and calling the code from a stand-alone application and  python.

As an example generalized library, [Basic Linear Algebra Subprograms (BLAS)](https://en.wikipedia.org/wiki/Basic_Linear_Algebra_Subprograms) has many implementations: Intel Math Kernel Library (MKL), AMD Optimizing CPU Libraries (AOCL), GNU Scientific Library (GSL), and Apple Accelerate. Libraries typically employ the same function name and signature. For example, c-callable implementations of the $\ell_1$-norm is typically called ```cblas_dasum``` for ```doubles```.

In order to demonstrate swapping low-level libraries, we include an implementation of the $\ell_1$-norm in ```.\src\blas\mathlib.c```. Our goal is, at compile time, to choose between the hand-written implementation or an optimized library (e.g. Intel MKL). Both binary files and header files for optimized libraries will be located outside our project directory.  Two challenges arise: 1, including the correct header files in user software; and 2, linking the binary library of interest. 

Correct header file inclusion addressed with compiler directives (```#define statements```) in ```\src\blas\mathlib.h```. Software requiring $\ell_1$-norm need only include the single header ```mathlib.h```. Compiler directives will determine whether external headers (e.g. ```mkl.h```) should be included.

Linking is configured with ```\src\blas\CMakeLists.txt```. When ```cmake``` is called (see below), optional arguments will determine which library is utilized. By default, the library ```blas_lib``` will be compiled from ```.\src\blas\mathlib.c```. Alternatively, ```blas_lib``` will be defined as an interface (header-only, not compiled) library. When ```blas_lib``` is defined as an interface, ```blas_lib``` is then linked to the external library of interest (e.g. MKL). In this way, other ```CMakeLists.txt``` targets need only link to ```blas_lib``` without concerns as to the specific implementation (compiled or interface).


## Stand-alone executable
A stand-alone implementation is built and executed as follows from the terminal:
```
mkdir build
cd build
cmake ..
make
./exe/hello_norm
```

When calling ```cmake```, setting the variable ```MATH_LIB``` to ```MKL``` will cause ```cmake``` to search for the MKL locally. The resulting build system will exclude ```mathlib.c``` from compilation, and link the target against the external library. After building the executable (i.e. ```make```), running the application (```./myapp```) will list the MKL version and the same $l1$ norm. 

```
cmake .. -DMATH_LIB=MKL
make
./exe/hello_norm
```

If you are on OSX, the ```MATH_LIB``` also supports ```APPLE``` to link to yet another BLAS library.

## Python module
Next we define a python module as an interface to our custom math library. For python there are many approaches to interface with external libraries. We favor [pybind11](https://pybind11.readthedocs.io/) as the interface is written in C.  However, defining the interface is only part of the challenge. We are also interested in distributing the module. Ideally, users should not copy/paste files into locally projects. Instead, users should _install_ the python module for use in a local environment. Packaging our python module using [scikit-build](https://scikit-build.readthedocs.io), we can extend our ```CMakeList.txt``` files such that users simply install the custom module using ```pip```. 

Our approach was modified from the [scikit-build example](https://github.com/pybind/scikit_build_example).

From the build folder, the python module can be installed using ```pip``` with

```
pip install ..
```

the package can be uninstalled using
```
pip uninstall  scikit_build_example
```