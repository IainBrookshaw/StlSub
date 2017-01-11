/**
 * KUKA INNOVATION AWARD
 * Perception -- STL Subdivision -- Unit Testing
 *
 * @file 
 * @author  Iain Brookshaw
 * @date    04 December 2016
 * @version 1.0
 *
 * @brief Unit Test for the "Mesh" Class
 *
 ******************************************************************************/
#include "all_tests.hpp"

using namespace kia;

// =============================================================================
/**
 * @class Mesh unit test fixture class
 */
class MeshTest : public ::testing::Test {

public:
  // ---------------------------------------------------------------------------

  // what is the float margin?
  double f_err = 0.01;

  // create pointer to tested mesh
  kia::Mesh* test_mesh;
  
  // generate test triangles for various methods...
  std::vector<Triangle> test_triangles;
  Triangle* unit_triangle_ptr; 
  // ---------------------------------------------------------------------------


  // ---------------------------------------------------------------------------
  virtual void SetUp(){

    // create test mesh.
    this->test_mesh = new kia::Mesh();
    if( !this->test_mesh ){
      std::cout << "unable to get test-mesh!\n";
      return;
    }
    
    // create unit triangle.
    this->unit_triangle_ptr = new Triangle( Vector3d( 0,0,0 ),
					    Vector3d( 1,0,0 ),
					    Vector3d( 1,1,0 ) );
    if( !this->unit_triangle_ptr ){
      std::cout << "unable to get unit-triangle!\n";
      return;
    }

    // add all these to the test_triangle Vector
    this->test_triangles.push_back( *this->unit_triangle_ptr );

    // add the test faces
    this->test_mesh->setCoarseStl( this->test_triangles );

  }
  // ---------------------------------------------------------------------------


  // ---------------------------------------------------------------------------
  virtual void TearDown(){
    if( this->test_mesh )         delete this->test_mesh;
    if( this->unit_triangle_ptr ) delete this->unit_triangle_ptr;
  }
  // ---------------------------------------------------------------------------
};
// =============================================================================


// =============================================================================


// ---------------------------------------------------------------------------
TEST_F( MeshTest, getFaceAreaTest ){

  // using the unit triangle, the area should be 0.5. Test this float 
  // value
  ASSERT_DOUBLE_EQ( this->test_mesh->getFaceArea( this->unit_triangle_ptr), (double)0.5 ) 
    << " test triangle not correct area.";
}
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
TEST_F( MeshTest, checkFaceAreaTest ){

  // set maximum face area.
  this->test_mesh->setMaxTriangleArea( 0.25 );
  ASSERT_FALSE( this->test_mesh->checkFaceArea(this->unit_triangle_ptr) ) 
    << "face area check failed.";
}
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
TEST_F( MeshTest, getSubFacePointsTest ){
  
  // set area so subdivision occurs
  this->test_mesh->setMaxTriangleArea( 0.49 );

  // create space for the sub-triangles
  std::vector<Triangle> sub_triangle_set(4);

  // check the sub-face method doesn't fail outright
  ASSERT_EQ( 0, this->test_mesh->getSubFacePoints( this->unit_triangle_ptr, 
						   &sub_triangle_set )) 
    << "unable to get sub-face points!";

  // check that there are four sub-triangles
  ASSERT_EQ( 4, sub_triangle_set.size() ) << "Wrong number of sub-triangles generated!";

  // check that the verticies are in the right place!
}
// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------
TEST_F( MeshTest, byte2floatTest ){

  float testf = 3.14159;
  unsigned char* testb = reinterpret_cast<unsigned char*>(&testf);

  ASSERT_FLOAT_EQ( testf, this->test_mesh->byte2float( testb ) ) << "conversion from bytes to double failed!";;
}
// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------
TEST_F( MeshTest, byte2intTest ){

  int testi = 42;
  unsigned char* testb = reinterpret_cast<unsigned char*>(&testi);

  ASSERT_EQ( testi, this->test_mesh->byte2int( testb ) ) << "conversion from bytes to integer failed!";;
}
// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------
TEST_F( MeshTest, type2byteTest ){

  float f_test = 1.0; //3.14159;
  float f_out;
  int   i_test = 42;
  int   i_out;

  // check float conversion
  const char* f_arr = this->test_mesh->type2byte( &f_test );
  f_out = this->test_mesh->byte2float( (unsigned char*)f_arr );
  std::cout << "in = " << f_test << ", out = " << f_out << "\n";

  ASSERT_FLOAT_EQ( f_out, f_test ) << "float to byte conversion fails."; 

  // check int conversion
  const char* i_arr = this->test_mesh->type2byte( &i_test );
  i_out = this->test_mesh->byte2int( (unsigned char*)i_arr );
  ASSERT_EQ( i_out, i_test ) << "int to byte conversion fails";
}
// ---------------------------------------------------------------------------

