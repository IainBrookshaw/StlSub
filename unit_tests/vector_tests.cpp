/**
 * KUKA INNOVATION AWARD
 * Perception -- STL Subdivision -- Unit Testing
 *
 * @file    vector_tests.cpp
 * @author  Iain Brookshaw
 * @date    29 December 2016
 * @version 1.0
 *
 * @brief Unit Test for the "Mesh" Class
 *
 ******************************************************************************/
#include "all_tests.hpp"

using namespace kia;



// ==========================================================================
// |                   NON-METHOD UTILITY FUNCTIONS                         |
// ==========================================================================


// ---------------------------------------------------------------------------
TEST( VectorTest, crossProductTest ){

  // we will do the unit vector cross products as a test
  // i x j = k
  // j x k = i
  // k x i = j

  Vector3d i(1,0,0);
  Vector3d j(0,1,0);
  Vector3d k(0,0,1);

  Vector3d ixj = crossProduct(i,j);
  Vector3d jxk = crossProduct(j,k);
  Vector3d kxi = crossProduct(k,i);

  ASSERT_DOUBLE_EQ( ixj.z, 1 ) << "i cross j fails";
  ASSERT_DOUBLE_EQ( jxk.x, 1 ) << "j cross k fails";
  ASSERT_DOUBLE_EQ( kxi.y, 1 ) << "k cross i fails";
}
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
TEST( VectorTest, vector3dAbsoluteTest ){

  Vector3d v(1,1,1);
  double length = sqrt(3);

  ASSERT_DOUBLE_EQ( length, vector3dAbsolute(v) ) << "vector length wrong!";
}
// ---------------------------------------------------------------------------
