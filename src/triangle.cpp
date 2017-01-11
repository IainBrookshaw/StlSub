/**
 * KUKA INNOVATION AWARD
 * Perception -- STL Subdivision
 *
 * @file    triangle.cpp
 * @author  Iain Brookshaw
 * @date    02 December 2016
 * @version 1.0
 *
 * @brief Method Source for the "Triangle" Class
 *
 ******************************************************************************/
#include <triangle.hpp>

namespace kia { 

  // ==========================================================================
  // |                     CONSTRUCTORS & DESTRUCTORS                         |
  // ==========================================================================

  /** -----------------------------------------------------------------------  
   * @brief Default Constructor
   */
  Triangle::Triangle(){
    // Nothing here for now.
  }
  //------------------------------------------------------------------------  


  
  /** -----------------------------------------------------------------------  
   * @brief 1st Constructor. This requires all the triangle verticies and 
   *        the normal vectors.
   * @param[in] _v1 -- vertex 1
   * @param[in] _v2 -- vertex 3
   * @param[in] _v3 -- vertex 3
   * @param[in] _normals -- vertex normals
   */
  Triangle::Triangle( Vector3d _v1,
		      Vector3d _v2,
		      Vector3d _v3,
		      Vector3d _normals ){
    this->v1 = _v1;
    this->v2 = _v2;
    this->v3 = _v3;
    this->normals = _normals;
  }
  //------------------------------------------------------------------------  


  
  /** -----------------------------------------------------------------------  
   * @brief 2nd Constructor. This requires just the triangle verticies
   *
   * @param[in] _v1 -- vertex 1
   * @param[in] _v2 -- vertex 3
   * @param[in] _v3 -- vertex 3
   */
  Triangle::Triangle( Vector3d _v1,
		      Vector3d _v2,
		      Vector3d _v3 ){
    this->v1 = _v1;
    this->v2 = _v2;
    this->v3 = _v3;
  }
  //------------------------------------------------------------------------  

  

  /** ------------------------------------------------------------------------  
   * @brief Default Destructor
   */
  Triangle::~Triangle(){
    // nothing here for now
  }
  //------------------------------------------------------------------------  




  // ==========================================================================
  // |                   TRIANGLE CLASS << OVERLOAD                           |
  // ==========================================================================

  std::ostream& operator<< (std::ostream &_out, Triangle const& _data) {
    _out << "[("
	 << _data.normals.x << "," << _data.normals.y << "," << _data.normals.z << "), ("
	 << _data.v1.x << "," << _data.v1.y << "," << _data.v1.z << "), ("
	 << _data.v2.x << "," << _data.v2.y << "," << _data.v2.z << "), ("
	 << _data.v3.x << "," << _data.v3.y << "," << _data.v3.z << ")]";
      return _out ;
  }



} // end of namespace of "kia"
