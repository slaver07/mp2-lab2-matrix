#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<int> m(5);

	ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m1({ {10, 4, 8}, {5, 7, 1}, {11, 12, 13} });
	TDynamicMatrix<int> m2 = m1;

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	std::vector<vector<int>> ñ = { {1,3},{7,8} };
	TDynamicMatrix<int> m(ñ);
	TDynamicMatrix<int> m2 = m;
	m[1][1] = 50;

	EXPECT_NE(m, m2);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(6);

	EXPECT_EQ(m.size(), 6);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(6);
	m[1][1] = 15;

	EXPECT_EQ(m[1][1], 15);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(5);

	ASSERT_ANY_THROW(m.at(-1)[1] = 7);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(5);

	ASSERT_ANY_THROW(m.at(6)[2] = 144);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(4);
	m[1][1] = 200;
	m = m;

	EXPECT_EQ(m[1][1], 200);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(4);
	TDynamicMatrix<int> m2(4);
	m1[1][1] = 111;
	m2 = m1;

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(4);
	TDynamicMatrix<int> m2(5);
	m2 = m1;

	EXPECT_EQ(m2.size(), 4);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(6);
	m2 = m1;

	EXPECT_EQ(m2, m1);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(4);
	TDynamicMatrix<int> m2 = m1;

	EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(4);

	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(4);

	EXPECT_TRUE(m1 != m2);
}

TEST(TDynamicMatrix, can_multiply_matrix_and_scalar)
{
	TDynamicMatrix<int> m({ {2, 3}, {5, 7} });
	TDynamicMatrix<int> m2;
	m2 = m * 3;
	TDynamicMatrix<int> m3({ {6, 9}, {15, 21} });

	EXPECT_EQ(m3, m2);
}


TEST(TDynamicMatrix, can_multiply_matrix_and_vector) {
	TDynamicMatrix<int> m1({ {1, 0, 2}, {0, 1, 4}, {2, 1, 0} });
	TDynamicVector<int> v1( {3, 1, 2} );
	TDynamicVector<int> v2;
	v2 = m1 * v1;
	TDynamicVector<int> v3( {7, 9, 7} );

	EXPECT_EQ(v3, v2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(3);
	TDynamicMatrix<int> m(3);
	m1[0][0] = 120;
	m2[0][0] = 180;
	m[0][0] = 300;

	EXPECT_EQ(m1 + m2, m);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(4);
	TDynamicMatrix<int> m2(5);

	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(3);
	TDynamicMatrix<int> m(3);
	m1[0][0] = 300;
	m2[0][0] = 110;
	m[0][0] = 190;

	EXPECT_EQ(m1 - m2, m);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(4);

	ASSERT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, can_multiply_matrix)
{
	TDynamicMatrix<int> m1(std::vector<vector<int>>{ {1, 2}, { 3, 4 }});
	TDynamicMatrix<int> m2(std::vector<vector<int>>{ {5, 6, 7}, { 8, 9, 10 }});
	TDynamicMatrix<int> m = m1 * m2;
	TDynamicMatrix<int> m3({ {21, 24, 27}, {47, 54, 61} });

	EXPECT_EQ(m, m3);
}

TEST(TDynamicMatrix, cant_multiply_matrix_with_not_equal_sizes)
{
	TDynamicMatrix<int> m1({ {1, 6, 7}, {4, 1, 5} });
	TDynamicMatrix<int> m2({ {10, 9, 7}, {1, 1, 2} });

	ASSERT_ANY_THROW(m1 * m2);
}

TEST(TDynamicMatrix, move_constructor_work_correctly)
{
	std::vector<vector<int>> ñ = { {5, 4}, {8, 8} };
	TDynamicMatrix<int> m1(ñ);
	TDynamicMatrix<int> m2 = std::move(m1);
	TDynamicMatrix<int> m(ñ);

	EXPECT_EQ(m2, m);
	EXPECT_EQ(m1.size(), 0);
}

TEST(TDynamicMatrix, can_move_object)
{
	std::vector<vector<int>> ñ = { {1, 2}, {3, 4} };
	TDynamicMatrix<int> m1(ñ);
	TDynamicMatrix<int> m(ñ);
	TDynamicMatrix<int> m2;
	m2 = std::move(m1);

	EXPECT_EQ(m2, m);
	EXPECT_EQ(m1.size(), 0);
}

TEST(TDynamicMatrix, can_create_matrix_with_vector)
{
	std::vector<vector<int>> ñ = { {22, 21},{99, 46} };
	TDynamicMatrix<int> m1(ñ);

	EXPECT_EQ(m1[0][0], ñ[0][0]);
	EXPECT_EQ(m1[0][1], ñ[0][1]);
	EXPECT_EQ(m1[1][0], ñ[1][0]);
	EXPECT_EQ(m1[1][1], ñ[1][1]);
}
