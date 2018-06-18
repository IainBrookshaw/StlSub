/**
 * StlSub
 *
 * @author  Iain Brookshaw
 * @date    02 December 2016
 *
 * @brief Header for the "Mesh" class.
 *
 ******************************************************************************/
#ifndef __MESH_HPP__
#define __MESH_HPP__

// ==========================================================================
// |                          INCLUDES AND GLOBALS                          |
// ==========================================================================

// system includes
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

// our project includes
#include<triangle.hpp>



namespace StlSub {

  // ==========================================================================
  // |                            STL MESH CLASS                              |
  // ==========================================================================

  /**
   * @class Mesh
   * @brief The "Mesh" class is the master class for the STL meshes. It 
   *        includes the original user input mesh, methods to load this
   *        and subdivide it into a finer stl mesh. The subdivision does
   *        not alter the overall geometry, this is not a smoothing utility.
   *        It is also important to note that the exact size of the 
   *        final triangles is undefined, only the maximum triangle size is 
   *        specified.
   */
  class Mesh {
    
  public:

    // -----------------------------------------
    // Constructors & Destructors
    Mesh();
    ~Mesh();
    // -----------------------------------------


    // -----------------------------------------
    // Get & Set Methods
    //
    void setInputFile( std::string _input_fname );
    std::string getInputFile();
    //
    void setOutputFile( std::string _output_fname );
    std::string getOutputFile();
    //
    std::vector<Triangle>* getCoarseStlPtr();
    void setCoarseStl( std::vector<Triangle> _coarse_stl );
    //
    std::vector<Triangle>* getFineStlPtr();
    void setFineStl( std::vector<Triangle> _fine_stl_ptr );
    //
    void   setMaxTriangleArea( double _max_t_a );
    double getMaxTriangleArea();
    // -----------------------------------------

    
    // -----------------------------------------
    // Utility Methods
    //
    void   makeFine();    
    double getFaceArea( Triangle* _face_ptr );
    bool   checkFaceArea( Triangle* _face_ptr );
    int    getSubFacePoints( Triangle* _face_ptr, std::vector<Triangle>* _sub_faces );
    int    subdivide( Triangle* _in_face_ptr, std::vector<Triangle>* _out_faces_ptr );
    int    byte2int( unsigned char* _in_arr );
    float  byte2float( unsigned char* _in_arr );
    int    readNbytes( unsigned char* _arr, std::ifstream* _st_ptr, int* _idx_ptr, int _N );
    const char* type2byte( float* _in );
    const char* type2byte( int*   _in );
    // -----------------------------------------

    
    // -----------------------------------------
    // IO Methods
    //
    Vector3d readVector( int* _idx, std::ifstream* _in_str );
    int loadStl( std::string _in_stl );
    int saveStl();
    int writeVector( std::ofstream* _file_ptr, Vector3d* _v );
    int writeFineStl( std::string _fname );
    // -----------------------------------------

    
  private:

    // File IO
    std::string input_stl_fname;  //!< The input STL file name.
    std::string output_stl_fname; //!< The output STL file name. 

    // Parsed STL
    unsigned char* header_char_ptr;   //!< pointer to character headers.
    std::vector<Triangle> coarse_stl; //!< The coarse input stl triangles from the input_stl_fname file
    std::vector<Triangle> fine_stl;   //!< The post-processed finer stl triangles. 

    // stl refinement criteria
    double max_triangle_area; //!< The maximum triangle area for the fine stl.

    // recursion variables
    int recursion;
    
  }; // end of class "Mesh"

} // end of StlSub namespace
#endif
