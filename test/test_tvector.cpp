#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, can_create_vector_with_std_vector)
{
	std::vector<int> ñ = {100, 54, 13};
	TDynamicVector<int> b(ñ);

	EXPECT_EQ(b[0], ñ[0]);
	EXPECT_EQ(b[1], ñ[1]);
	EXPECT_EQ(b[2], ñ[2]);

}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v1( {1, 2, 3} );
	TDynamicVector<int> v2(v1);

	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1( {17, 34, 1} );
	TDynamicVector<int> v2(v1);
	TDynamicVector<int> v3( {17, 34, 1} );
	v2[0] = 20;
	TDynamicVector<int> v4( {20, 34, 1} );

	EXPECT_NE(v1[0], v2[0]);
	EXPECT_EQ(v1, v3);
	EXPECT_EQ(v2, v4);
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(7);

	EXPECT_EQ(7, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
	TDynamicVector<int> v(5);
	v[2] = 55;

	EXPECT_EQ(55, v[2]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(5);

	ASSERT_ANY_THROW(v.at(-2) = 10);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);

	ASSERT_ANY_THROW(v.at(8) = 1);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(3);
	v[1] = 999;
	v = v;

	EXPECT_EQ(v[1], 999);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	v1[2] = 10;
	v2 = v1;

	EXPECT_EQ(v2, v1);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(4);
	v2 = v1;

	EXPECT_EQ(v2.size(), 3);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(4);
	v1[0] = 88;
	v2 = v1;

	EXPECT_EQ(v2, v1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(4);
	TDynamicVector<int> v2(4);
	v1[3] = 12;
	v2 = v1;

	EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(3);

	EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(7);

	EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v1( {11, 16, 21} );
	TDynamicVector<int> res = v1 + 5;
	TDynamicVector<int> v2( {16, 21, 26} );

	EXPECT_EQ(res, v2);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v1( {5, 6, 7} );
	TDynamicVector<int> res = v1 - 1;
	TDynamicVector<int> v2( {4, 5, 6} );

	EXPECT_EQ(res, v2);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v1( {3, 4, 1} );
	TDynamicVector<int> res = v1 * 3;
	TDynamicVector<int> v2( {9, 12, 3} );

	EXPECT_EQ(res, v2);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1( {4, 2, 4} );
	TDynamicVector<int> v2( {4, 1, 6} );
	TDynamicVector<int> res = v1 + v2;
	TDynamicVector<int> v3( {8, 3, 10} );

	EXPECT_EQ(res, v3);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(4);
	TDynamicVector<int> v2(6);

	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1( {1, 2, 3} );
	TDynamicVector<int> v2( {6, 9, 5} );
	TDynamicVector<int> res = v2 - v1;
	TDynamicVector<int> v3( {5, 7, 2} );

	EXPECT_EQ(res, v3);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(4);
	TDynamicVector<int> v2(5);

	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1( {2, 1, 1} );
	TDynamicVector<int> v2( {4, 3, 1} );
	int mul = v1 * v2;

	EXPECT_EQ(mul, 12);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(4);

	ASSERT_ANY_THROW(v1 * v2);
}

TEST(TDynamicVector, move_constructor_work_correctly)
{
	TDynamicVector<int> v1( {10, 20, 30, 40, 50} );
	TDynamicVector<int> v2 = std::move(v1);
	TDynamicVector<int> v( {10, 20, 30, 40, 50} );

	EXPECT_EQ(v2, v);
	EXPECT_EQ(v1.size(), 0);
}

TEST(TDynamicVector, can_move_object)
{
	TDynamicVector<int> v1( {5, 7, 9} );
	TDynamicVector<int> v( {5, 7, 9} );
	TDynamicVector<int> v2;
	v2 = std::move(v1);

	EXPECT_EQ(v2, v);
	EXPECT_EQ(v1.size(), 0);
}