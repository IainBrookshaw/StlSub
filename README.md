# STL Sub
**Author:** Iain Brookshaw

**Date**  2016.12.06

**Version:** 0.1

**copyright** (c) 2016 Iain Brookshaw, released under the LGPL v 3.0
  
## Overview
    
Originally part of USC's entry into the 2017 "Kuka Unnovation Award",
**STLSub** is a tool to improve the resolution of STL files; subdividing
large triangles into an arbitrary number of smaller ones.

This is done by ensuring that each triangle face is smaller than a user
defined minimum, rather than a formal smoothing algorith. This is useful
for path planning over 3D objects -- such as necessary for controlling
manufacturing arms.
  
Note that the absolute size of each face is not gauranteed, we simply
ensure that face area is less than a minimum threshold.
  
STLSub does not rely upon any but the standard C++ libraries (c++11) and 
is intended to perform this task alone. 
     
## Build
  
This project is built with Make (rather than CMake) and can be built with 
the supplied Makefile.

It is assumed that the GCC (g++ 4.8.4) is being used to compile this 
library. GCC specific preprocessor macros are used.

This library was built specifically for Ubuntu Linux machines. Windows
is NOT supported.

## Install
```bash
   make install
   #note: You need sudo privileges to do this, installs to /usr/local/lib
```

## Linking
   TODO
   
   This library exists in the namespace "kia" (the "Kuka Innovation Award"
   for which it was developed).  

## Stand-Alone Utility
   TODO

## Unit-Testing
   The Google G-Test unit-testing framework was used to unit-test this 
   library. TODO: Install instructions

## Documentation
   run:
	doxygen myDoxyfile 
   to compile to documentation for this library.

## Licence
   This library and all related work is licenced under the LGPL v3 unless
   otherwise noted.

## Acknowledgements
