/**
 * KUKA INNOVATION AWARD
 * Perception -- STL Subdivision
 *
 * @file    mesh.cpp
 * @author  Iain Brookshaw
 * @date    02 December 2016
 * @version 1.0
 *
 * @brief Method Source for the "Mesh" Class
 *
 ******************************************************************************/
#include <mesh.hpp>

namespace kia { 
  
  // ==========================================================================
  // |                     CONSTRUCTORS & DESTRUCTORS                         |
  // ==========================================================================
  
  /** -----------------------------------------------------------------------  
   * @brief Default Constructor
   */
  Mesh::Mesh(){
    input_stl_fname  = "none";
    output_stl_fname = "none";
    this->header_char_ptr = new unsigned char[80];
  }
  // ------------------------------------------------------------------------  



  /** -----------------------------------------------------------------------  
   * @brief Default Destructor
   */
  Mesh::~Mesh(){
    // nothing here for now
    if( this->header_char_ptr ) delete this->header_char_ptr;
  }
  // ------------------------------------------------------------------------  

  
  

  // ==========================================================================
  // |                         GET & SET METHODS                              |
  // ==========================================================================

  /** -----------------------------------------------------------------------  
   * @brief file name get and set.
   */
  void Mesh::setInputFile( std::string _input_fname ){ this->input_stl_fname = _input_fname; }
  std::string Mesh::getInputFile(){ return this->input_stl_fname; }
  //
  void Mesh::setOutputFile( std::string _output_fname ){ this->output_stl_fname = _output_fname; }
  std::string Mesh::getOutputFile(){ return this->output_stl_fname; }
  // ------------------------------------------------------------------------  


  /** ------------------------------------------------------------------------  
   * @brief get the pointers to the stl data
   */
  std::vector<Triangle>* Mesh::getCoarseStlPtr(){ return &this->coarse_stl; }
  std::vector<Triangle>* Mesh::getFineStlPtr(){   return &this->fine_stl; }
  //
  void Mesh::setCoarseStl( std::vector<Triangle> _new_c_stl ){ this->coarse_stl = _new_c_stl;}
  void Mesh::setFineStl(   std::vector<Triangle> _new_f_stl ){ this->fine_stl   = _new_f_stl;}
  // ------------------------------------------------------------------------  

  
  /** ------------------------------------------------------------------------  
   * @brief Get and set the maximum triangle area parameter for the fine 
   *        stl.
   */
  void Mesh::setMaxTriangleArea( double _max_t_a ){ this->max_triangle_area = _max_t_a; }
  double Mesh::getMaxTriangleArea(){ return this->max_triangle_area; }
  // ------------------------------------------------------------------------  


  
  
  // ==========================================================================
  // |                         UTILITY METHODS                                |
  // ==========================================================================

  /** ------------------------------------------------------------------------  
   * @brief This is the master method for making the mesh finer
   */
  void Mesh::makeFine(){

    std::vector<Triangle>::iterator it;
    this->recursion = 0;

    for( it=this->coarse_stl.begin(); it<this->coarse_stl.end(); it++ ){
      if( this->subdivide( &(*it), &this->fine_stl )){
	std::cout << std::string(__FUNCTION__) << "(): subdivision failed!\n";
	return;
      }
    }
  }    
  //-------------------------------------------------------------------------  

  
  /** ------------------------------------------------------------------------  
   * @brief This method computes the area of the input face. Area computation 
   *        is via vector cross product.
   * @param[in] _face_ptr --- pointer to the input face
   * @return the area of the input face in <units>^2, -1 if error
   */
  double Mesh::getFaceArea( Triangle* _face_ptr ){
    if(!_face_ptr){
      std::cout << std::string(__FUNCTION__) << "(): _face_ptr invalid!\n";
      return -1;
    } 

    Vector3d v1( _face_ptr->v2.x - _face_ptr->v1.x,
		 _face_ptr->v2.y - _face_ptr->v1.y,
		 _face_ptr->v2.z - _face_ptr->v1.z );

    Vector3d v2( _face_ptr->v3.x - _face_ptr->v1.x,
		 _face_ptr->v3.y - _face_ptr->v1.y,
		 _face_ptr->v3.z - _face_ptr->v1.z );

    Vector3d cross_vect = crossProduct( v1, v2 );
    double a = 0.5*(vector3dAbsolute( cross_vect ));
    return a;
  }
  //-------------------------------------------------------------------------  



  /** ------------------------------------------------------------------------  
   * @brief Checks if the face area is acceptable with maximum area.
   * @param[in] _face_ptr --- pointer to this face triangle
   * @return is this face acceptable? yes/no
   */
  bool Mesh::checkFaceArea( Triangle* _face_ptr ){

    // sanity check -- return true as fail-soft.
    if( !_face_ptr ){
      std::cout << std::string(__FUNCTION__) << "(): _face_ptr_invalid!\n";
      return true;
    }

    // area check
    if( this->getFaceArea( _face_ptr ) <= this->max_triangle_area ){
      return true;
    }else{
      return false;
    }
  }
  //-------------------------------------------------------------------------  



  /** ------------------------------------------------------------------------  
   * @brief This returns the four subdivided faces of the first triangle. 
   * @param[in] _face_ptr --- the triangle to be subdivided.
   * @param[in] _sub_faces -- pointer to a vector of 4 sub-faces
   * @return integer; 0 if success, 1 or higher if failed.
   */
  int Mesh::getSubFacePoints( Triangle* _face_ptr, std::vector<Triangle>* _sub_faces ){
    
    // sanity checks
    if( !_sub_faces ){
      std::cout << std::string(__FUNCTION__) << "(): sub_face_pointer is invalid!\n";
      return 1;
    }
    if( _sub_faces->size() != 4 ){
      std::cout << std::string(__FUNCTION__) << "(): sub_face_length is invalid! Please reserve 4 spaces!\n";
      return 1;
    }
    /*
    // the old points
    Vector3d Q1 = _face_ptr->v1;
    Vector3d Q2 = _face_ptr->v2;
    Vector3d Q3 = _face_ptr->v3;

    // the new points
    Vector3d P1;
    Vector3d P2;
    Vector3d P3;

    // compute the new points
    P1.x = Q1.x + (Q2.x - Q1.x);
    P1.y = Q1.y + (Q2.y - Q1.y);
    P1.z = Q1.z + (Q2.z - Q1.z);

    P2.x = Q2.x + (Q3.x - Q2.x);
    P2.y = Q2.y + (Q3.y - Q2.y);
    P2.z = Q2.z + (Q3.z - Q2.z);

    P1.x = Q1.x + (Q3.x - Q1.x);
    P1.y = Q1.y + (Q3.y - Q1.y);
    P1.z = Q1.z + (Q3.z - Q1.z);

    // assign the verticies for triangle 1
    (*_sub_faces)[0].v1 = Q1;
    (*_sub_faces)[0].v2 = P1;
    (*_sub_faces)[0].v3 = P3;

    // assign the verticies for triangle 2
    (*_sub_faces)[1].v1 = P1;
    (*_sub_faces)[1].v2 = Q2;
    (*_sub_faces)[1].v3 = P2;

    // assign the verticies for triangle 3
    (*_sub_faces)[2].v1 = P3;
    (*_sub_faces)[2].v2 = P2;
    (*_sub_faces)[2].v3 = Q3;

    // assign the verticies for triangle 4
    (*_sub_faces)[3].v1 = P1;
    (*_sub_faces)[3].v2 = P2;
    (*_sub_faces)[3].v3 = P3;

    */





    Vector3d p0;
    p0.x = _face_ptr->v1.x - (_face_ptr->v1.x - _face_ptr->v2.x)/2.0;
    p0.y = _face_ptr->v1.y - (_face_ptr->v1.y - _face_ptr->v2.y)/2.0;
    p0.z = _face_ptr->v1.z - (_face_ptr->v1.z - _face_ptr->v2.z)/2.0;
    
    Vector3d p1;
    p1.x = _face_ptr->v3.x - (_face_ptr->v3.x - _face_ptr->v2.x)/2.0;
    p1.y = _face_ptr->v3.y - (_face_ptr->v3.y - _face_ptr->v2.y)/2.0;
    p1.z = _face_ptr->v3.z - (_face_ptr->v3.z - _face_ptr->v2.z)/2.0;
    
    Vector3d p2;
    p2.x = _face_ptr->v3.x - (_face_ptr->v3.x - _face_ptr->v1.x)/2.0;
    p2.y = _face_ptr->v3.y - (_face_ptr->v3.y - _face_ptr->v1.y)/2.0;
    p2.z = _face_ptr->v3.z - (_face_ptr->v3.z - _face_ptr->v1.z)/2.0;

    // assign the sub-faces.
    //
    std::vector<Triangle>::iterator it;
    int i=0;
    for( it=_sub_faces->begin(); it<_sub_faces->end(); it++, i++ ){

      switch(i){
      case 0:
	// sub-face 1
	it->v1 = _face_ptr->v1;
	it->v2 = p0;
	it->v3 = p2;
      	break;

      case 1:
	// sub-face 2
	it->v1 = p0;
	it->v2 = _face_ptr->v2;
	it->v3 = p1;
	break;

      case 2:
	// sub-face 3
	it->v1 = p2;
	it->v2 = p1;//p0;
	it->v3 = _face_ptr->v3;//p1;
	break;

      case 3:
	// sub-face 4
	it->v1 = p2;
	it->v2 = p0;
	it->v3 = p1;
	break;
	
      default:
	std::cout << std::string(__FUNCTION__) << ": index error!\n";
	return 1;
      }
    }
    
    // end of method
    return 0;
  }
  //-------------------------------------------------------------------------  


  
  /** ------------------------------------------------------------------------  
   * @brief This is a recursive method that does the actual sub-dividing of 
   *        the face until the mimimum size is met for each face.
   * @param[in]  _in_face_ptr   -- pointer to "this" face we are subdividing
   * @param[out] _out_faces_ptr -- pointer to the vector of triangles that define the new
   *                               faces.
   * @return 0 on success, 1 on fail.
   */
  int Mesh::subdivide( Triangle* _in_face_ptr, std::vector<Triangle>* _out_faces_ptr ){

    // sanity checks
    if( !_in_face_ptr ){
       std::cout << std::string(__FUNCTION__) 
		 << "(): invalid _in_face_ptr!\n";
       return 1;
    }
    if( !_out_faces_ptr ){
       std::cout << std::string(__FUNCTION__) 
		 << "(): invalid _out_faces_ptr!\n";
       return 1;
    }

    // recursion safety catch
    this->recursion++;
    if( 1000 < this->recursion ){ /** @todo recursion safety: un-Hardwire this. Some faces might be very big */
      std::cout << std::string(__FUNCTION__) 
		<< "(): this->recursion = " 
		<< this->recursion 
		<< ", this is too much recursion for one face!\n";
      return 1;
    }

    
    // check if the face is already OK. If it is, just place it on the _out_faces vector, reset
    // and return.
    if( this->checkFaceArea( _in_face_ptr ) ){
      _out_faces_ptr->push_back( *_in_face_ptr );
      this->recursion = 0;
      return 0;
    }
    // ...Agh! No, it's too big! Do subdivision!

    // get new sub-divided faces for this _in_face. There are always 4 of these.
    std::vector<Triangle> sub_faces;
    sub_faces.resize(4);
    //
    if( this->getSubFacePoints(  _in_face_ptr, &sub_faces ) ){
      std::cout << std::string( __FUNCTION__ ) << "(): getSubFacePoints() Failed!\n";
      return 1;
    }
    
    // loop over all the sub-faces and check to see if further 
    // sub-division is necessary. This is where the recursion occurs.
    std::vector<Triangle>::iterator it;
    std::vector<Triangle> sub_faces2;
    int i = 0;
    //
    for( it=sub_faces.begin(); it<sub_faces.end(); it++, i++ ){
      if( this->subdivide( &(*it), _out_faces_ptr ) ) return 1;
    }
    return 0;
  }
  //-------------------------------------------------------------------------  

  



  

  // ==========================================================================
  // |                            IO METHODS                                  |
  // ==========================================================================


  /** -------------------------------------------------------------------------  
   * @brief converts a byte-char array to int. It is assumed that the length 
   *        of the char array makes sense for int. We further assume that this
   *        is a little endian environment. Your STL file must conform to this 
   *        assumption -- ie: it must be created on a little endian machine.
   * @param[in] _in_arr --- pointer to first entry of input array
   * @return the float conversion. -1 is error, but also legitimate return.
   */
  int Mesh::byte2int( unsigned char* _in_arr ){
    if( !_in_arr ){
      std::cout << std::string(__FUNCTION__) << "(): invalid input ptr!\n";
      return -1;
    }
    return *reinterpret_cast<int*>(_in_arr);
  }
  // -------------------------------------------------------------------------  



  /** -------------------------------------------------------------------------  
   * @brief converts a byte-char array to float. It is assumed that the length 
   *        of the char array makes sense for float. We further assume that this
   *        is a little endian environment. Your STL file must conform to this 
   *        assumption -- ie: it must be created on a little endian machine.
   * @param[in] _in_arr --- pointer to first entry of input array
   * @return the float conversion. -1  is error, but also legitimate return
   */
  float Mesh::byte2float( unsigned char* _in_arr ){
    if( !_in_arr ){
      std::cout << std::string(__FUNCTION__) << "(): invalid input ptr!\n";
      return -1;
    }
    return *reinterpret_cast<float*>(_in_arr);
  }
  // -------------------------------------------------------------------------  



  /** -------------------------------------------------------------------------  
   * @brief converts a signed integer to a byte array for writing to file.
   *        as usual, we assume little endian. 
   * @param[in]  _in_ptr --- pointer to number for transform.
   * @return pointer to the byte array.
   */
  const char* Mesh::type2byte( float* _in_ptr ){
    return reinterpret_cast<const char*>(_in_ptr);
  }
  // integer overload
  const char* Mesh::type2byte( int* _in_ptr ){
    return reinterpret_cast<const char*>(_in_ptr);
  }
  // -------------------------------------------------------------------------  

  
  
  /** -------------------------------------------------------------------------  
   * @brief reads in N bytes from an ifstream
   * @param[in]  _idx_ptr -- pointer to starting index in file. This is incremented by the read action
   * @param[in]  _N       -- number of bytes to read in
   * @param[in]  _st_ptr  -- pointer to the ifstream, assumed to be open for read
   * @param[out] _arr     -- array of unsigned chars
   * @returns 0 if success, 1 if failed
   */
  int Mesh::readNbytes( unsigned char* _arr, std::ifstream* _st_ptr, int* _idx_ptr, int _N ){

    // sanity check
    if( !_arr || !_st_ptr || !_idx_ptr ){
      std::cout << std::string( __FUNCTION__ ) <<": invalid pointers!\n";
      return 1;
    }
    // open check
    if( !_st_ptr->is_open() ){
      std::cout << std::string( __FUNCTION__ ) <<": stream not open!\n";
      return 1;
    }
    // file length check
    _st_ptr->seekg(0, std::ios::end);
    long int f_size = _st_ptr->tellg();
    //
    if( *_idx_ptr+_N > f_size ){
      std::cout << std::string( __FUNCTION__ ) 
		<< ": file length of " << f_size << " shorter than input read length: " << *_idx_ptr+_N << std::endl;
      return 1;
    }


    // reset file pointer
    _st_ptr->clear(); // clear bad state after eof
    _st_ptr->seekg( *_idx_ptr, std::ios::beg );

    // read in N chars
    _st_ptr->read( (char*)_arr, (std::streamsize)_N);

    // reset the index and return
    *_idx_ptr += _N;
    return 0;
  }
  // -------------------------------------------------------------------------  



  /** -------------------------------------------------------------------------  
   * @brief This method reads in a vector -- a set of three points.
   * @param[in] _idx    -- pointer to stream index
   * @param[in] _in_str -- pointer to the stream
   * @return the vector. all entries are -1 if failed, although this is also a valid
   *         return. We have to return something.
   */
  Vector3d Mesh::readVector( int* _idx, std::ifstream* _in_str ){

    // create and init vector
    Vector3d vect;
    vect.x = -1;
    vect.y = -1;
    vect.z = -1;

    // some space
    double n[3];
    unsigned char four_char_arr[4];
    int i;
     
    for( i=0; i<3; i++ ){
      // read in the i-th entry as bytes and check that it didn't fail.
      if( this->readNbytes( four_char_arr, _in_str, _idx, 4) ) return vect;

      // convert these 4 bytes to a double-precision float
      n[i] = (double)this->byte2float( four_char_arr );
    }

    // save the floats in the appropriate space in the vector class.
    vect.x = n[0];
    vect.y = n[1];
    vect.z = n[2];

    return vect;
  }
  // -------------------------------------------------------------------------  



  /** -------------------------------------------------------------------------  
   * @brief load STL parser for binary STL files
   * @param[in] _in_stl --- input file name or complete path.
   * @return 0 for successful load and parsing, 1 for failure.
   */
  int Mesh::loadStl( std::string _in_stl ){

    // open file stream
    std::ifstream stl_file_stream;
    stl_file_stream.open( _in_stl.c_str(), std::ios::binary | std::ios::in |  std::ios::ate );

    // check file path for existance.
    if( !stl_file_stream.is_open() ){
      std::cout << std::string(__FUNCTION__)
		<< ": unable to open file '"
		<< _in_stl
		<< "'!\n";
      return 1;
    }

    // read the file.
    int file_idx = 0;
    int i;

    // There is suposed to be 80 chars in the header
    if( this->readNbytes( this->header_char_ptr, &stl_file_stream, &file_idx, 80) ) return 1;

    // read in the triangle count -- how many faces does this stl file have?
    unsigned char four_char_arr[4];
    unsigned char two_char_arr[2];
    if( this->readNbytes( four_char_arr, &stl_file_stream, &file_idx, 4) ) return 1;
    int face_count = this->byte2int( four_char_arr );

    // read in all these faces.
    std::vector<Triangle> triangle_vect;

    for( i=0; i<face_count; i++ ){
      //
      // First, read in the normal vector
      Vector3d normal = this->readVector( &file_idx, &stl_file_stream );
      
      // Next, read in the first vertex
      Vector3d vert1 = this->readVector( &file_idx, &stl_file_stream );
      
      // ...read in the 2nd vertex.
      Vector3d vert2 = this->readVector( &file_idx, &stl_file_stream );
      
      // ...read in the 3rd vertex.
      Vector3d vert3 = this->readVector( &file_idx, &stl_file_stream );;

      // ...read attribute byte count (whatever this is) We don't keep this as it doesn't 
      // actually seem to do anything. This is only to keep the file_idx ticking over.
      this->readNbytes( two_char_arr, &stl_file_stream, &file_idx, 2 ); 
      
      // combine these into a triangle face...
      Triangle new_triangle( vert1, vert2, vert3, normal);

      // add this to the list.
      this->coarse_stl.push_back( new_triangle );
    }
    return 0;
  }// end of loadStl()
  // -------------------------------------------------------------------------  


  /** -------------------------------------------------------------------------  
   * @brief write a vector3d class to a binary file.
   * @param[in] _file_ptr --- pointer to the ofstream
   * @param[in] _v_ptr    --- pointer to the vector3d
   * @return 0 on success, 1 on error.
   */
  int Mesh::writeVector( std::ofstream* _file_ptr, Vector3d* _v_ptr ){
    // sanity checks
    if( !_file_ptr ){
      std::cout << std::string(__FUNCTION__) << "(): output file stream invalid!\n";
      return 1;
    }
    if( !_v_ptr ){
      std::cout << std::string(__FUNCTION__) << "(): input vector invalid!\n";
      return 1;
    }

    float x = (float)_v_ptr->x;
    float y = (float)_v_ptr->y;
    float z = (float)_v_ptr->z;
    //    const char* char_x_ptr = this->type2byte( &x );
    //    float float_x = this->byte2float( (unsigned char*)char_x_ptr );
    //    std::cout << std::string(__FUNCTION__) << "(): in x = " << _v_ptr->x << ", out x = " << float_x << "\n";

    _file_ptr->write( this->type2byte( &x ), sizeof(float) );
    _file_ptr->write( this->type2byte( &y ), sizeof(float) );
    _file_ptr->write( this->type2byte( &z ), sizeof(float) );

    return 0;
  }
  // -------------------------------------------------------------------------  



  /** -------------------------------------------------------------------------  
   * @brief Write fine stl to binary file. 
   * @param[in] _fname -- output file-name.
   * @return 0 on success, 1 on failure.
   */
  int Mesh::writeFineStl( std::string _fname ){
    
    // open the file (binary stl)
    std::ofstream out_file;
    out_file.open( _fname, std::ios::out | std::ios::trunc | std::ios::binary );
    //
    // check
    if( !out_file.is_open() ){
      std::cout << std::string(__FUNCTION__) << "(): unable to open file '" 
		<< _fname << "'\n";
      return 1;
    }
    
    // write the header string to file
    out_file.write( (const char*)(this->header_char_ptr), 80 );
    
    // write the number of triangles
    int length = (int)this->fine_stl.size();
    const char* triangle_count_ptr = this->type2byte( &length );
    out_file.write( triangle_count_ptr, 4 );
    
    // now loop over the triangles and write the face data.
    std::vector<Triangle>::iterator it;
    const char attribute_count[2] = {0,0};
    int i = 1;

    for( it = this->fine_stl.begin(); it < this->fine_stl.end(); it++, i++ ){

      // ...normal vector; x,y,z
      this->writeVector( &out_file, &(it->normals));

      // ...vertex 1; x,y,z
      this->writeVector( &out_file, &(it->v1));

      // ...vertex 2; x,y,z
      this->writeVector( &out_file, &(it->v2));

      // ...vertex 3; x,y,z
      this->writeVector( &out_file, &(it->v3));

      // ...atribute byte count thing
      out_file.write( attribute_count, 2 );

    } // end of write loop

    // close file.
    out_file.close();
    return 0;
  }
  // -------------------------------------------------------------------------  
    
} // end of namespace of "kia"
