/**
 * KUKA INNOVATION AWARD
 * Perception -- STL Subdivision
 *
 * @file    vector3d.hpp
 * @author  Iain Brookshaw
 * @date    02 December 2016
 * @version 1.0
 *
 * @brief Header for the "Vector3d" class.
 *
 ******************************************************************************/
#ifndef __VECTOR3D_HPP__
#define __VECTOR3D_HPP__
#include <math.h>

namespace kia {
  
  // ==========================================================================
  // |                          3D VECTOR CLASS                               |
  // ==========================================================================

  /**
   * @class Vector3d 
   * @brief The "Vector3d" class defines a simple 3d vector. 
   *        This is really a glorified structure.
   */
  class Vector3d {

  public:
    
    // -----------------------------------------------
    // Constructor & Destructor
    Vector3d();
    Vector3d( double _x, double _y, double _z);
    ~Vector3d();
    // -----------------------------------------------
    
    // -----------------------------------------------
    // Data
    double x;
    double y;
    double z;
    // -----------------------------------------------

  }; // end of class "Vector3d"



  // ==========================================================================
  // |                        UTILITY FUNCTIONS                               |
  // ==========================================================================

  // Note: These are FUNCTIONS, not MEMBERS and are NOT members of the class "Vector3d", 
  // but it is convenient to declare them here.
  Vector3d crossProduct( Vector3d _v1, Vector3d _v2 );
  double vector3dAbsolute( Vector3d _v );
}// end of namespace "kia"

#endif
