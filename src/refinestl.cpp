// ============================================================================
// |                          HEADERS AND SUCHLIKE                            |
// ============================================================================

// stl mesh parsing
#include <mesh.hpp>

// argparsing
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// output 
#define OUT std::cout << "[STL]: "


// ============================================================================
// |                                 USAGE                                    |
// ============================================================================
void usage(){
  std::cout << "\n"
	    << "Name:    refinestl\n"
	    << "Author:  Iain J. Brookshaw\n"
	    << "Date:    18th June 2018\n"
	    << "\n"
	    << "Description:\n"
	    << "\t This is a simple program which implements a STL subdivision libarary\n"
	    << "\t allowing the user to reduce the granularity of a 3D object STL file.\n"
	    << "\t Users may specify the source STL, the destination STL and the maximum\n"
	    << "\t triangle area. This STL subdivision gaurantees that all \n"
	    << "\t triangles in dst will be smaller than max-area. There are no gaurantees\n"
	    << "\t regarding the dimensions of the triangle other than its maximum area.\n" 
	    << "\n"
	    << "Inputs: \n"
	    << "\t -i -- source binary STL file\n"
	    << "\t -o -- destination binary STL file (may be src if you want to overwrite src)\n"
	    << "\t -m -- maximum area of dst STL triangles (units^2)\n"
	    << "\t -v -- verbose mode -- shows what this executable is doing\n"
	    << "\n"
	    << "Returns: \n"
	    << "\t 0 on success, 1 on failure\n"
	    << "\n"
	    << "Copyright\n"
	    << "\t Copyright (C) 2018 Iain Brookshaw\n"
	    << "\n"
	    << "\t This program is free software under the LGPL v3.0 and is distributed in the hope\n"
	    << "\t that it will be useful, but WITHOUT ANY WARRANTY, without even the implied warranty\n"
	    << "\t of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public\n"
	    << "\t License for  more details.\n";
}


// ============================================================================
// |                                  MAIN                                    |
// ============================================================================


int main( int argc, char** argv ){

  // input argument parsing.
  int         opt;
  std::string src;
  std::string dst;
  double      max;
  bool        verb = false;

  while( (opt = getopt(argc, argv, "hi:o:m:v")) != -1 ){
    
    switch( opt ){
    case 'h':
      usage();
      return 0;
      
    case 'i':
      src = std::string(optarg);
      break;

    case 'o':
      dst = std::string(optarg);
      break;

    case 'm':
      max = std::atof(optarg);
      break;

    case 'v':
      verb = true;
      OUT << "running verbose mode\n";
      break;

    default:
      OUT << "Input " << std::string((const char*)&opt) << " undefined!\n";
      usage();
      return 1;
    }
  }
     
  if( verb ) OUT << "creating mesh...\n";
  StlSub::Mesh* in_stl_mesh = new StlSub::Mesh();
  if( !in_stl_mesh ){
    OUT << "Unable to create mesh!\n";
    return 1;
  }
  if( verb ) OUT << "...done\n";

  if( verb ) OUT << "loading stl file...\n";
  if( in_stl_mesh->loadStl( src ) ){
    OUT << "Unable to load STL!\n";
    return 1;
  }
  if( verb ) OUT << "...done\n";

  
  // set maximum area
  if( verb ) OUT << "setting maximum area...\n";
  in_stl_mesh->setMaxTriangleArea( max );
  if( verb ) OUT << "...done\n";


  // subdivide
  if( verb ) OUT << "subdividing stl to fit maximum face area...\n";
  in_stl_mesh->makeFine();
  if( verb ) OUT << "...done\n";

  // write output.
  if( verb ) OUT << "writing to '" << dst << "'...\n"; 
  in_stl_mesh->writeFineStl( dst );
  if( verb ) OUT << "...done\n";

  return 0;

} // ----------- END OF PROGRAM ------------
