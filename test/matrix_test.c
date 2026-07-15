#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "matrix.h"
#include "matrix_test.h"

void test_create() {
	printf("\ntest matrix_create\n");

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

void test_free() {
	printf("\ntest matrix_free\n");
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

void test_get() {
	printf("\ntest matrix_get\n");

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

// TODO: test for out of bounds

void test_set() {
	printf("\ntest matrix_set\n");

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

// TODO: test for out of bounds

void test_print() {
	printf("\ntest matrix_print\n");

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

void test_multiply() {
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

	printf("matrix A:\n");
	matrix_print(A);

	for (int B_row = 0; B_row < B->rows; B_row++) {
		for (int B_col = 0; B_col < B->cols; B_col++) {
			matrix_set(B, B_row, B_col, (float)(B_col + (B_row * B->cols)));
		}
	}

	printf("matrix B:\n");
	matrix_print(B);

	matrix_set(expected, 0, 0, 1.0f);
	matrix_set(expected, 1, 0, 3.0f);

	printf("expected:\n");
	matrix_print(expected);

	matrix_multiply(A, B, result);

	printf("result:\n");
	matrix_print(result);

	assert((matrix_get(result, 0, 0) == matrix_get(expected, 0, 0)) &&
		   (matrix_get(result, 1, 0) == matrix_get(expected, 1, 0)));

	matrix_free(&A);
	matrix_free(&B);
	matrix_free(&result);
	matrix_free(&expected);
}

void test_multiply_AB_dimensions() {
	printf("\ntest wrong dimensions of A and B\n");

	Matrix* A = matrix_create(1, 2);
	Matrix* B = matrix_create(3, 4);
	Matrix* result = matrix_create(1, 4);

	printf("matrix A:\n");
	matrix_print(A);
	printf("matrix B:\n");
	matrix_print(B);
	printf("dimension error: matrix A cannot multiply matrix B\n");

	int success = matrix_multiply(A, B, result);
	assert(success = -1);

	matrix_free(&A);
	matrix_free(&B);
	matrix_free(&result);
}

void test_multiply_result_dimensions() {
	printf("\ntest wrong dimensions of result\n");

	Matrix* A = matrix_create(2, 2);
	Matrix* B = matrix_create(2, 1);
	Matrix* result = matrix_create(1, 4);

	printf("matrix A:\n");
	matrix_print(A);
	printf("matrix B:\n");
	matrix_print(B);
	printf("result matrix:\n");
	matrix_print(result);
	printf("dimension error: result cannot fit in provided matrix\n");

	int success = matrix_multiply(A, B, result);
	assert(success = -1);

	matrix_free(&A);
	matrix_free(&B);
	matrix_free(&result);
}

void test_multiply_add() {
	printf("\ntest matrix_multiply_add\n");
	
	Matrix* A = matrix_create(2, 2);
	Matrix* B = matrix_create(2, 1);
	Matrix* result = matrix_create(2, 1);
	Matrix* expected = matrix_create(2, 1);

	for (int A_row = 0; A_row < A->rows; A_row++) {
		for (int A_col = 0; A_col < A->cols; A_col++) {
			matrix_set(A, A_row, A_col, (float)(A_col + (A_row * A->cols)));
		}
	}

	printf("matrix A:\n");
	matrix_print(A);

	for (int B_row = 0; B_row < B->rows; B_row++) {
		for (int B_col = 0; B_col < B->cols; B_col++) {
			matrix_set(B, B_row, B_col, (float)(B_col + (B_row * B->cols)));
		}
	}

	printf("matrix B:\n");
	matrix_print(B);

	matrix_set(result, 0, 0, 3.0f);
	matrix_set(result, 1, 0, 2.0f);

	printf("result before multiply_add:\n");
	matrix_print(result);

	matrix_set(expected, 0, 0, 4.0f);
	matrix_set(expected, 1, 0, 5.0f);

	printf("expected:\n");
	matrix_print(expected);

	matrix_multiply_add(A, B, result);

	printf("result:\n");
	matrix_print(result);

	assert((matrix_get(result, 0, 0) == matrix_get(expected, 0, 0)) &&
		   (matrix_get(result, 1, 0) == matrix_get(expected, 1, 0)));

	matrix_free(&A);
	matrix_free(&B);
	matrix_free(&result);
	matrix_free(&expected);
}

void test_equals() {
	printf("\ntest matrix_equals\n");

	Matrix* A = matrix_create(2, 2);
	Matrix* B = matrix_create(2, 2);
	Matrix* C = matrix_create(2, 2);

	for (int row = 0; row < A->rows; row++) {
		for (int col = 0; col < A->cols; col++) {
			matrix_set(A, row, col, (float)(row + col));
			matrix_set(B, row, col, (float)(row + col));
			matrix_set(C, row, col, (float)(row + col + 1)); // Different values
		}
	}

	printf("matrix A:\n");
	matrix_print(A);
	printf("matrix B:\n");
	matrix_print(B);
	printf("matrix C:\n");
	matrix_print(C);

	int equal_AB = matrix_equals(A, B);
	int equal_AC = matrix_equals(A, C);

	printf("A equals B: %d\n", equal_AB);
	printf("A equals C: %d\n", equal_AC);

	assert(equal_AB == 0); // A and B are equal
	assert(equal_AC == -1); // A and C are not equal

	matrix_free(&A);
	matrix_free(&B);
	matrix_free(&C);
}

void test_copy() {
	printf("\ntest matrix_copy\n");

	Matrix* src = matrix_create(2, 2);
	Matrix* dst = matrix_create(2, 2);

	for (int row = 0; row < src->rows; row++) {
		for (int col = 0; col < src->cols; col++) {
			matrix_set(src, row, col, (float)(row + col));
		}
	}

	printf("source matrix:\n");
	matrix_print(src);

	int copy_success = matrix_copy(src, dst);
	if (copy_success == 0) {
		printf("destination matrix after copy:\n");
		matrix_print(dst);
	} else {
		printf("matrix_copy failed due to dimension mismatch.\n");
	}

	assert(copy_success == 0); // Copy should succeed

	int equal_src_dst = matrix_equals(src, dst);
	printf("src equals dst: %d\n", equal_src_dst);
	assert(equal_src_dst == 0); // src and dst should be equal

	matrix_free(&src);
	matrix_free(&dst);
}

void test_copy_dimension_mismatch() {
	printf("\ntest matrix_copy with dimension mismatch\n");

	Matrix* src = matrix_create(2, 2);
	Matrix* dst = matrix_create(3, 3); // Different dimensions

	for (int row = 0; row < src->rows; row++) {
		for (int col = 0; col < src->cols; col++) {
			matrix_set(src, row, col, (float)(row + col));
		}
	}

	printf("source matrix:\n");
	matrix_print(src);
	printf("destination matrix before copy:\n");
	matrix_print(dst);

	int copy_success = matrix_copy(src, dst);
	if (copy_success == -1) {
		printf("matrix_copy failed due to dimension mismatch as expected.\n");
	} else {
		printf("matrix_copy unexpectedly succeeded.\n");
	}

	assert(copy_success == -1); // Copy should fail due to dimension mismatch

	matrix_free(&src);
	matrix_free(&dst);
}

void test_add() {
	printf("\ntest matrix_add\n");

	Matrix* A = matrix_create(2, 2);
	Matrix* B = matrix_create(2, 2);
	Matrix* result = matrix_create(2, 2);
	Matrix* expected = matrix_create(2, 2);

	for (int row = 0; row < A->rows; row++) {
		for (int col = 0; col < A->cols; col++) {
			matrix_set(A, row, col, (float)(row + col));
			matrix_set(B, row, col, (float)(row + col + 1)); // Different values
		}
	}

	printf("matrix A:\n");
	matrix_print(A);
	printf("matrix B:\n");
	matrix_print(B);

	// Expected result of A + B
	for (int row = 0; row < expected->rows; row++) {
		for (int col = 0; col < expected->cols; col++) {
			matrix_set(expected, row, col, matrix_get(A, row, col) + matrix_get(B, row, col));
		}
	}

	int add_success = matrix_add(A, B, result);
	if (add_success == 0) {
		printf("result of A + B:\n");
		matrix_print(result);
	} else {
		printf("matrix_add failed due to dimension mismatch.\n");
	}

	assert(add_success == 0); // Addition should succeed

	int equal_result_expected = matrix_equals(result, expected);
	printf("result equals expected: %d\n", equal_result_expected);
	assert(equal_result_expected == 0); // result and expected should be equal

	matrix_free(&A);
	matrix_free(&B);
	matrix_free(&result);
	matrix_free(&expected);
}

void test_add_dimension_mismatch() {
	printf("\ntest matrix_add with dimension mismatch\n");

	Matrix* A = matrix_create(2, 2);
	Matrix* B = matrix_create(3, 3); // Different dimensions
	Matrix* result = matrix_create(2, 2);

	printf("matrix A:\n");
	matrix_print(A);
	printf("matrix B:\n");
	matrix_print(B);

	int add_success = matrix_add(A, B, result);
	if (add_success == -1) {
		printf("matrix_add failed due to dimension mismatch as expected.\n");
	} else {
		printf("matrix_add unexpectedly succeeded.\n");
	}

	assert(add_success == -1); // Addition should fail due to dimension mismatch

	matrix_free(&A);
	matrix_free(&B);
	matrix_free(&result);
}

void test_subtract() {
	printf("\ntest matrix_subtract\n");

	Matrix* A = matrix_create(2, 2);
	Matrix* B = matrix_create(2, 2);
	Matrix* result = matrix_create(2, 2);
	Matrix* expected = matrix_create(2, 2);

	for (int row = 0; row < A->rows; row++) {
		for (int col = 0; col < A->cols; col++) {
			matrix_set(A, row, col, (float)(row + col + 1));
			matrix_set(B, row, col, (float)(row + col)); // Different values
		}
	}

	printf("matrix A:\n");
	matrix_print(A);
	printf("matrix B:\n");
	matrix_print(B);

	// Expected result of A - B
	for (int row = 0; row < expected->rows; row++) {
		for (int col = 0; col < expected->cols; col++) {
			matrix_set(expected, row, col, matrix_get(A, row, col) - matrix_get(B, row, col));
		}
	}

	int subtract_success = matrix_subtract(A, B, result);
	if (subtract_success == 0) {
		printf("result of A - B:\n");
		matrix_print(result);
	} else {
		printf("matrix_subtract failed due to dimension mismatch.\n");
	}

	assert(subtract_success == 0); // Subtraction should succeed

	int equal_result_expected = matrix_equals(result, expected);
	printf("result equals expected: %d\n", equal_result_expected);
	assert(equal_result_expected == 0); // result and expected should be equal

	matrix_free(&A);
	matrix_free(&B);
	matrix_free(&result);
	matrix_free(&expected);
}

void test_subtract_dimension_mismatch() {
	printf("\ntest matrix_subtract with dimension mismatch\n");

	Matrix* A = matrix_create(2, 2);
	Matrix* B = matrix_create(3, 3); // Different dimensions
	Matrix* result = matrix_create(2, 2);

	printf("matrix A:\n");
	matrix_print(A);
	printf("matrix B:\n");
	matrix_print(B);

	int subtract_success = matrix_subtract(A, B, result);
	if (subtract_success == -1) {
		printf("matrix_subtract failed due to dimension mismatch as expected.\n");
	} else {
		printf("matrix_subtract unexpectedly succeeded.\n");
	}

	assert(subtract_success == -1); // Subtraction should fail due to dimension mismatch

	matrix_free(&A);
	matrix_free(&B);
	matrix_free(&result);
}

void test_scalar_multiply() {
	printf("\ntest matrix_scalar_multiply\n");

	float scalar = 2.0f;

	Matrix* A = matrix_create(2, 2);
	Matrix* result = matrix_create(2, 2);
	Matrix* expected = matrix_create(2, 2);

	matrix_set(A, 0, 0, 1.0f);
	matrix_set(A, 1, 1, 2.0f);
	
	printf("matrix A:\n");
	matrix_print(A);

	matrix_set(expected, 0, 0, 2.0f);
	matrix_set(expected, 1, 1, 4.0f);

	printf("expected:\n");
	matrix_print(expected);

	matrix_scalar_multiply(A, scalar, result);

	printf("result:\n");
	matrix_print(result);

	assert(matrix_equals(expected, result) == 0);

	matrix_free(&A);
	matrix_free(&result);
	matrix_free(&expected);
}

void test_scalar_dimension_mismatch() {
	printf("\ntest matrix_scalar_multiply for dimension mismatch\n");

	float scalar = 2.0f;

	Matrix* A = matrix_create(2, 2);
	Matrix* result = matrix_create(3, 3);

	printf("matrix A:\n");
	matrix_print(A);

	printf("scalar is: %f\n", scalar);
	
	printf("result matrix:\n");
	matrix_print(result);

	printf("this should produce a dimension error\n");

	int pass = matrix_scalar_multiply(A, scalar, result);

	assert(pass == -1);

	matrix_free(&A);
	matrix_free(&result);
}

void test_fill() {
	printf("\ntest matrix_fill\n");

	float val = 3.14f;

	Matrix* A = matrix_create(2, 2);
	Matrix* expected = matrix_create(2, 2);

	matrix_set(expected, 0, 0, val);
	matrix_set(expected, 0, 1, val);
	matrix_set(expected, 1, 0, val);
	matrix_set(expected, 1, 1, val);

	printf("matrix A:\n");
	matrix_print(A);

	printf("fill val: %f\n", val);

	printf("expected matrix:\n");
	matrix_print(expected);

	matrix_fill(A, val);

	printf("A after fill:\n");
	matrix_print(A);

	assert(matrix_equals(A, expected) == 0);

	matrix_free(&expected);
	matrix_free(&A);
}

void test_hadamard() {
	printf("\ntest matrix_hadamard\n");

	Matrix* A = matrix_create(2, 2);
	Matrix* B = matrix_create(2, 2);
	Matrix* result = matrix_create(2, 2);
	Matrix* expected = matrix_create(2, 2);

	matrix_fill(A, -1.0f);
	matrix_fill(B, 2.0f);
	matrix_fill(expected, -2.0f);

	printf("matrix A:\n");
	matrix_print(A);

	printf("matrix B:\n");
	matrix_print(B);

	printf("expected matrix:\n");
	matrix_print(expected);

	matrix_hadamard(A, B, result);
	printf("result matrix:\n");
	matrix_print(result);

	assert(matrix_equals(expected, result) == 0);

	matrix_free(&A);
	matrix_free(&B);
	matrix_free(&result);
	matrix_free(&expected);
}

void test_hadamard_AB_dimensions() {
	printf("\ntest matrix_hadamard A and B dimension mismatch\n");

	Matrix* A = matrix_create(2, 2);
	Matrix* B = matrix_create(3, 3);
	Matrix* result = matrix_create(2, 3);

	printf("matrix A:\n");
	matrix_print(A);

	printf("matrix B:\n");
	matrix_print(B);

	printf("should get a dimension error\n");

	int ret = matrix_hadamard(A, B, result);
	assert(ret == -1);

	matrix_free(&A);
	matrix_free(&B);
	matrix_free(&result);
}

void test_hadamard_result_dimension() {
	printf("\ntest matrix_hadamard result dimension mismatch\n");

	Matrix* A = matrix_create(2, 2);
	Matrix* B = matrix_create(2, 2);
	Matrix* result = matrix_create(3, 3);

	printf("matrix A:\n");
	matrix_print(A);

	printf("matrix B:\n");
	matrix_print(B);

	printf("should get a dimension error\n");
	int ret = matrix_hadamard(A, B, result);

	assert(ret == -1);

	matrix_free(&A);
	matrix_free(&B);
	matrix_free(&result);
}

void test_transpose() {
	printf("\ntest matrix_transpose\n");

	Matrix* A = matrix_create(2, 3);
	Matrix* expected = matrix_create(3, 2);
	Matrix* result;

	matrix_set(A, 0, 0, 1.0f);
	matrix_set(A, 0, 1, 1.0f);
	matrix_set(A, 0, 2, 1.0f);

	matrix_set(A, 1, 0, 2.0f);
	matrix_set(A, 1, 1, 2.0f);
	matrix_set(A, 1, 2, 2.0f);

	printf("matrix A:\n");
	matrix_print(A);

	matrix_set(expected, 0, 0, 1.0f);
	matrix_set(expected, 0, 1, 2.0f);

	matrix_set(expected, 1, 0, 1.0f);
	matrix_set(expected, 1, 1, 2.0f);

	matrix_set(expected, 2, 0, 1.0f);
	matrix_set(expected, 2, 1, 2.0f);

	printf("expected matrix:\n");
	matrix_print(expected);

	result = matrix_transpose(A);

	printf("result matrix:\n");
	matrix_print(result);

	assert(matrix_equals(expected, result) == 0);

	matrix_free(&A);
	matrix_free(&expected);
	matrix_free(&result);
}

int run_matrix_tests() {
	test_create();
	test_free();
	test_get();
	test_set();
	test_print();
	test_multiply();
	test_multiply_AB_dimensions();
	test_multiply_result_dimensions();
	test_multiply_add();
	test_equals();
	test_copy();
	test_copy_dimension_mismatch();
	test_add();
	test_add_dimension_mismatch();
	test_subtract();
	test_subtract_dimension_mismatch();
	test_scalar_multiply();
	test_scalar_dimension_mismatch();
	test_fill();
	test_hadamard();
	test_hadamard_AB_dimensions();
	test_hadamard_result_dimension();
	test_transpose();

	return 0;
}