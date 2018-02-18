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
#include "idlib/idlib.hpp"

namespace idlib::tests {

TEST(matrix_4s_4s_test, inverse)
{
	matrix<single, 4, 4> a;
	// inverse of identity matrix must be the identity matrix
	a = identity<matrix<single, 4, 4>>();
	ASSERT_EQ(a.inverse(), a);
	// a translation matrix with a translation of 1 along the x-axis
	a = matrix<single, 4, 4>
			(
				1, 0, 0, 1,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
			);
	ASSERT_EQ((a.inverse() * a), (identity<matrix<single, 4, 4>>()));
	//
	a = rotation_x(angle<single, degrees>(0.0f));
	ASSERT_EQ((a.inverse() * a), (identity<matrix<single, 4, 4>>()));
	//
	a = rotation_x(angle<single, degrees>(90.0f));
	ASSERT_EQ((a.inverse() * a), (identity<matrix<single, 4, 4>>()));
	//
	a = rotation_x(angle<single, degrees>(180.0f));
	ASSERT_EQ((a.inverse() * a), (identity<matrix<single, 4, 4>>()));
	//
	a = rotation_x(angle<single, degrees>(270.0f));
	ASSERT_EQ((a.inverse() * a), (identity<matrix<single, 4, 4>>()));
	//
	a = rotation_y(angle<single, degrees>(0.0f));
	ASSERT_EQ((a.inverse() * a), (identity<matrix<single, 4, 4>>()));
	//
	a = rotation_y(angle<single, degrees>(90.0f));
	ASSERT_EQ((a.inverse() * a), (identity<matrix<single, 4, 4>>()));
	//
	a = rotation_y(angle<single, degrees>(180.0f));
	ASSERT_EQ((a.inverse() * a), (identity<matrix<single, 4, 4>>()));
	//
	a = rotation_y(angle<single, degrees>(270.0f));
	ASSERT_EQ((a.inverse() * a), (identity<matrix<single, 4, 4>>()));
	//
	a = rotation_z(angle<single, degrees>(0.0f));
	ASSERT_EQ((a.inverse() * a), (identity<matrix<single, 4, 4>>()));
	//
	a = rotation_z(angle<single, degrees>(90.0f));
	ASSERT_EQ((a.inverse() * a), (identity<matrix<single, 4, 4>>()));
	//
	a = rotation_z(angle<single, degrees>(180.0f));
	ASSERT_EQ((a.inverse() * a), (identity<matrix<single, 4, 4>>()));
	//
	a = rotation_z(angle<single, degrees>(270.0f));
	ASSERT_EQ((a.inverse() * a), (identity<matrix<single, 4, 4>>()));
	// a translation matrix with a translation of 2 along the x-axis
	a = translation({1.0f, 0.0f, 0.0f});
	ASSERT_EQ((a.inverse() * a), (identity<matrix<single, 4, 4>>()));
	a = translation({0.0f, 1.0f, 0.0f});
	ASSERT_EQ((a.inverse() * a), (identity<matrix<single, 4, 4>>()));
	a = translation({0.0f, 0.0f, 1.0f});
	ASSERT_EQ((a.inverse() * a), (identity<matrix<single, 4, 4>>()));
	a = translation({1.0f, 0.0f, 1.0f});
	ASSERT_EQ((a.inverse() * a), (identity<matrix<single, 4, 4>>()));
	a = translation({0.0f, 1.0f, 1.0f});
	ASSERT_EQ((a.inverse() * a), (identity<matrix<single, 4, 4>>()));
}

} // namespace idlib::tests
