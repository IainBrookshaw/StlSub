/**
 * KUKA INNOVATION AWARD
 * Perception -- STL Subdivision
 *
 * @file    vector3d.cpp
 * @author  Iain Brookshaw
 * @date    02 December 2016
 * @version 1.0
 *
 * @brief Source for the "Vector3d" class. 
 *
 ******************************************************************************/
#include <vector3d.hpp>

namespace kia {

  // ==========================================================================
  // |                          3D VECTOR CLASS                               |
  // ==========================================================================

 
  // -----------------------------------------------
  // Constructor & Destructor
  Vector3d::Vector3d(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
  }
  Vector3d::Vector3d( double _x, double _y, double _z){
    this->x = _x;
    this->y = _y;
    this->z = _z;
  }
  Vector3d::~Vector3d(){
    // nothing for now...
  }
  // -----------------------------------------------


  // ==========================================================================
  // |                        UTILITY FUNCTIONS                               |
  // ==========================================================================


  /** ------------------------------------------------------------------------
   * @brief This function uses the Vector3D class to implement the cross
   *        product of two vectors. This is useful for finding areas.
   *        The result is the cross of v1 x v2
   * @param[in] _v1 --- vector 1
   * @param[in] _v2 --- vector 2
   * @return the cross-product of _v1 x _v2
   */
  Vector3d crossProduct( Vector3d _v1, Vector3d _v2 ){

    Vector3d cross( (_v1.y*_v2.z - _v1.z*_v2.y),
		    (_v1.z*_v2.x - _v1.x*_v2.z),
		    (_v1.x*_v2.y - _v1.y*_v2.x) );
    return cross;
  }
  // -------------------------------------------------------------------------
      

  /** ------------------------------------------------------------------------
   * @brief Get absolute magnitude of the vector.
   * @param[in] _v the vector in question
   * @return The magnitude of the vector.
   */
  double vector3dAbsolute( Vector3d _v ){
    return sqrt( _v.x*_v.x + _v.y*_v.y + _v.z*_v.z );
  }
  // -------------------------------------------------------------------------

  
}// end of namespace "kia"

