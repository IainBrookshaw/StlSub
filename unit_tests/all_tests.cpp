/**
 * @file   all_tests.cpp
 * @author Iain Brookshaw,
 * @date   06 December 2016
 *
 * @brief This is the main program for all unit testing.
 */
#include "all_tests.hpp"

// =============================================================================
// RUN ALL TESTS
//
int main( int argc, char** argv ){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
// =============================================================================

