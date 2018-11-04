# STL Subdivision
version 1.0
copyright (c) 2018 GNU Public License
  
## Introduction
Simple library and application to increase the resolution of STL files. Using this,
one can subdivide the input stl's triangles an arbitrary number of times (up to working 
precision) until the triangle area falls below a user specified threshold.

There are no dependencies other than the c++11 standard libraries
     
## Build
   This project is built with Make (rather than CMake) and can be built with 
   the supplied Makefile.

   It is assumed that the GCC (g++ 4.8.4 or higher) is being used to compile this 
   library. GCC specific preprocessor macros are used.

   This library was built specifically for Ubuntu Linux machines. Windows
   is NOT supported.

### Build as Shared Lib (`.so`)
   `make`

### Build as Stand Alone Executable
   `make` -- build the shared lib
   `make install` -- install the shared lib on the system (must have sudo privaleges, qv)
   `make exe` -- build the exe and link against shared lib 

## Install
   `make install`
   note: You need sudo privileges to do this, installs to /usr/local/lib

## Unit-Testing
   The Google G-Test unit-testing framework was used to unit-test this 
   library. TODO: Install instructions

## Documentation
   run:
	`doxygen myDoxyfile`
   to compile to documentation for this library.

## Licence
   This library and all related work is licenced under the LGPL v3 unless
   otherwise noted.

## Acknowledgements
This software was developed as part of the  Realization of Robotic Systems Lab (USC)'s entry into the 2016 Kuka Inovation Award
