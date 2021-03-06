///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Idlib: A C++ utility library
// Copyright (C) 2017-2018 Michael Heilmann
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "gtest/gtest.h"
#include "idlib/math.hpp"

namespace idlib::tests {

TEST(matrix_4f_4f, determinant)
{
    using M = idlib::matrix<single, 4, 4>;
    M m;
    // a binary matrix with a checkerboard pattern of 0's and 1's
    // determinant must be zero
    m = M(0, 1, 0, 1,
          1, 0, 1, 0,
          0, 1, 0, 1,
          1, 0, 1, 0);
    ASSERT_EQ(m.det(), 0);
    // a translation matrix with a translation of 1 along the x-axis
    // determinant must be one
    m = M(1, 0, 0, 1,
          0, 1, 0, 0,
          0, 0, 1, 0,
          0, 0, 1, 1);
    ASSERT_EQ(m.det(), 1);
    // a translation matrix with a translation of 2 along the x-axis
    // determinant must be one
    m = M(1, 0, 0, 2,
          0, 1, 0, 0,
          0, 0, 1, 0,
          0, 0, 1, 1);
    ASSERT_EQ(m.det(), 1);
}

} // namespace idlib::tests
