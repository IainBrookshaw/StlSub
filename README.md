@author Iain Brookshaw
@date 30 December 2016
@version 1.0
@copyright GNU Public License
  
@section Introduction
   As part of USC's entry into the "Kuka Innovation Award" 2017, we 
   need to develop a tool to improve the resolution of STL files. 
   Instead of adding more points as part of a smoothing algorithm, we 
   found it necessary to simply ensure that each triangle face was 
   smaller than a user defined minimum. This implies loading and parsing
   a binary STL file and iterating through all the faces, checking to
   see if that face falls below some area threshold. If it does not, then
   we split that triangle into 4 smaller triangles (by placing a new vertex
   at the center of each existing edge) and recursively inspect them until
   all faces are smaller than the threshold.
  
   Note that the absolute size of each face is not gauranteed, we simply
   ensure that face area is less than a minimum threshold.
  
   Although this functionality is probably part of other libraries, such as
   the PCL, we find it useful to have it seperated into as a stand alone
   tool, limiting the linking complexity. Our subdivision library does
   not rely upon any but the standard C++ libraries (c++11) and 
   is intended to perform this task alone. 
     
@section Build
   This project is built with Make (rather than CMake) and can be built with 
   the supplied Makefile.

   It is assumed that the GCC (g++ 4.8.4) is being used to compile this 
   library. GCC specific preprocessor macros are used.

   This library was built specifically for Ubuntu Linux machines. Windows
   is NOT supported.

@section Install
   make install
   note: You need sudo privileges to do this, installs to /usr/local/lib

@section Linking
   TODO
   
   This library exists in the namespace "kia" (the "Kuka Innovation Award"
   for which it was developed).  

@section Stand-Alone Utility
   TODO

@section Unit-Testing
   The Google G-Test unit-testing framework was used to unit-test this 
   library. TODO: Install instructions

@section Documentation
   run:
	doxygen myDoxyfile 
   to compile to documentation for this library.

@section Licence
   This library and all related work is licenced under the LGPL v3 unless
   otherwise noted.

@section Acknowledgements
