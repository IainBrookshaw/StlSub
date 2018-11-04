/**
 * KUKA INNOVATION AWARD
 * Perception -- STL Subdivision
 *
 * @file    triangle.hpp
 * @author  Iain Brookshaw
 * @date    02 December 2016
 * @version 1.0
 *
 * @brief Header for the "Triangle" class. This is the expression of an
 *        stl face.
 *
 ******************************************************************************/
#ifndef __TRIANGLE_HPP__
#define __TRIANGLE_HPP__

// ==========================================================================
// |                          INCLUDES AND GLOBALS                          |
// ==========================================================================

// system includes
#include<string>
#include<iostream>

// our includes
#include<vector3d.hpp>


namespace stlsub {

  // ==========================================================================
  // |                          TRIANGLE CLASS                                |
  // ==========================================================================

  /**
   * @class Triangle
   * @brief The "Triangle" class defines exactly 1 triangle as used by
   *        an STL. STL files are described as vectors of "Triangles".
   *  
   *        This is not a class the user should need to access directly,
   *        Thus everything is "public".
   */
  class Triangle {

  public:

    
    // -----------------------------------------
    // Constructors & Destructors
    Triangle();
    //
    Triangle( Vector3d _v1,
	      Vector3d _v2,
	      Vector3d _v3,
	      Vector3d _normals);
    //
    Triangle( Vector3d _v1,
	      Vector3d _v2,
	      Vector3d _v3 );
    //
    ~Triangle();
    // -----------------------------------------

    // -----------------------------------------
    // Data
    Vector3d v1; //!< the 1st vertex (a 3d point)
    Vector3d v2; //!< the 2nd vertex (a 3d point)
    Vector3d v3; //!< the 3rd vertex (a 3d point)
    Vector3d normals; //!< the face normal unit vector (usually not used).
    // -----------------------------------------
  }; // end of class "Triangle"	




  // ==========================================================================
  // |                   TRIANGLE CLASS << OVERLOAD                           |
  // ==========================================================================

  std::ostream& operator<< (std::ostream &_out, Triangle const& _data);

       
}// end of namespace "stlsub"
#endif
