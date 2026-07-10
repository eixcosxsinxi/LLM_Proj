#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "matrix.h"

void test_matrix_create() {
	printf("\ntest_matrix_create\n");

	int rows = 3;
	int cols = 3;
	float data = 0;

	Matrix* m = matrix_create(rows, cols);
	m->data[0] = data;

	printf("rows = %d, m.rows = %d\n", rows, m->rows);
	assert(m->rows == rows);
	printf("cols = %d, m.cols = %d\n", cols, m->cols);
	assert(m->cols == cols);
	printf("data = %.6f, m.data = %.6f\n", data, *(m->data));
	assert(*(m->data) == data);
}

void test_matrix_free() {
	printf("\ntest_matrix_free\n");
	int rows = 3;
	int cols = 3;
	float data = 0;

	Matrix* m = matrix_create(rows, cols);
	m->data[0] = data;

	printf("rows before = %d\n", m->rows);
	printf("cols before = %d\n", m->cols);
	printf("data before = %.6f\n", m->data[0]);

	matrix_free(&m);

	printf("m after free = %p\n", (void*)m);

	assert(m == NULL);
}

void test_matrix_get() {
	printf("\ntest_matrix_get\n");

	int rows = 3;
	int cols = 3;

	int row = 0;
	int col = 0;
	float data = 1.23f;

	Matrix* m = matrix_create(rows, cols);
	m->data[0] = data;

	printf("row = %d\n", row);
	printf("col = %d\n", col);
	printf("data = %.6f\n", data);

	float value = matrix_get(m, row, col);
	printf("value at (%d, %d) = %.6f\n", row, col, value);
	assert(value == data);

	matrix_free(&m);
}

void test_matrix_set() {
	printf("\ntest_matrix_set\n");

	int rows = 3;
	int cols = 3;

	int row = 0;
	int col = 0;
	float data = 4.56f;

	Matrix* m = matrix_create(rows, cols);
	matrix_set(m, row, col, data);

	printf("row = %d\n", row);
	printf("col = %d\n", col);
	printf("data set to = %.6f\n", data);

	float value = matrix_get(m, row, col);
	printf("value at (%d, %d) after set = %.6f\n", row, col, value);
	assert(value == data);

	matrix_free(&m);
}

void test_matrix_print() {
	printf("\ntest_matrix_print\n");

	int rows = 3;
	int cols = 3;

	Matrix* m = matrix_create(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix_set(m, i, j, (float)(i * cols + j));
		}
	}

	printf("Matrix contents:\n");
	matrix_print(m);
	printf("does it look like it a 3x3 matrix with values from 0 to 8?\n");

	matrix_free(&m);
}

void test_matrix_multiply() {
	printf("\ntest matrix_multiply\n");
	
	Matrix* A = matrix_create(2, 2);
	Matrix* B = matrix_create(2, 1);
	Matrix* result = matrix_create(2, 1);
	Matrix* expected = matrix_create(2, 1);

	for (int A_row = 0; A_row < A->rows; A_row++) {
		for (int A_col = 0; A_col < A->cols; A_col++) {
			matrix_set(A, A_row, A_col, (float)(A_col + (A_row * A->cols)));
		}
	}

	printf("\nmatrix A:\n");
	matrix_print(A);

	for (int B_row = 0; B_row < B->rows; B_row++) {
		for (int B_col = 0; B_col < B->cols; B_col++) {
			matrix_set(B, B_row, B_col, (float)(B_col + (B_row * B->cols)));
		}
	}

	printf("\nmatrix B:\n");
	matrix_print(B);

	matrix_set(expected, 0, 0, 1.0f);
	matrix_set(expected, 1, 0, 3.0f);

	printf("\nexpected:\n");
	matrix_print(expected);

	matrix_multiply(A, B, result);

	printf("\nresult:\n");
	matrix_print(result);

	assert((matrix_get(result, 0, 0) == matrix_get(expected, 0, 0)) &&
		   (matrix_get(result, 1, 0) == matrix_get(expected, 1, 0)));

	matrix_free(&A);
	matrix_free(&B);
	matrix_free(&result);
	matrix_free(&expected);
}

int main() {
	test_matrix_create();
	test_matrix_free();
	test_matrix_get();
	test_matrix_set();
	test_matrix_print();
	test_matrix_multiply();
	return 0;
}