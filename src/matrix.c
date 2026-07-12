#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

/* this gives you an instance of a Matrix struct as a pointer (because all the helper methods pass in pointers) */
Matrix* matrix_create(int rows, int cols) 
{
	Matrix* m = calloc(1, sizeof(Matrix));

	if (m == NULL) {
		fprintf(stderr, "Failed to allocate matrix.\n");
		free(m);
		exit(EXIT_FAILURE);
	}

	m->rows = rows;
	m->cols = cols;

	m->data = calloc(rows * cols, sizeof(float));

	if (m->data == NULL) {
		fprintf(stderr, "Failed to allocate matrix data.\n");
		free(m);
		exit(EXIT_FAILURE);
	}

	return m;
}

/* this should free the space created by a Matrix and leave the pointer not hanging by setting it to NULL */
void matrix_free(Matrix** m) {
	free((*m)->data);
	free(*m);
	*m = NULL;
}

/* this should return the value at the specified row and column in the matrix */
float matrix_get(const Matrix* m, int row, int col) { // const so you don't accidentally modify the matrix
	// TODO: make sure you put check for out of bounds
	return m->data[row * m->cols + col];
}

/* this should set the value at the specified row and column in the matrix */
int matrix_set(Matrix* m, int row, int col, float value) {
	if (row < 0 || row >= m->rows || col < 0 || col >= m->cols) {
		fprintf(stderr, "Index out of bounds.\n");
		return -1;
	}
	m->data[row * m->cols + col] = value;
	return 0;
}

/* this should print the matrix to the console */
void matrix_print(const Matrix* m) {
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			printf("%8.3f ", matrix_get(m, i, j));
		}
		printf("\n");
	}
}

/* this should multiply two matrices and store in result. returns 0 on success, -1 on failure */
int matrix_multiply(const Matrix* A, const Matrix* B, Matrix* result) {
	/*
	*	Matrix multiplication follows from the dot product.
	*	For two matrices A and B, the cols of A must be equal to the rows of B.
	*	This is so that when you set the two matrices up like this,
	*	A = [[1, 2, 3],  and B = [[1, 2],
	*		 [4, 5, 6]]			  [3, 4],
	*							  [5, 6]]
	* 
	*	the result of the multiplication between A and B is a series of dot products.
	*	for resultant matrix C, C should have the same rows as A and the same cols as B.
	*	spot m by n of C is calculated as the dot product of row m of A and col n of B.
	*	that is why it is important that A needs to have the same cols as B has rows so the dot product works.
	*/
	if (A->cols != B->rows) {
		fprintf(stderr, "could not multiply these matrices: A.cols != B.rows (inner dimensions do not match!)");
		return -1;
	} else if (result->rows != A->rows || result->cols != B->cols) {
		fprintf(stderr, "could not store result in provided matrix: result.rows != A.rows or result.cols != B.cols");
		return -1;
	} else {

		for (int row = 0; row < result->rows; row++) {
			for (int col = 0; col < result->cols; col++) {

				float sum = 0.0f;

				for (int index = 0; index < A->cols; index++) {

					sum += 
						matrix_get(A, row, index) *
						matrix_get(B, index, col);
				}
				matrix_set(result, row, col, sum);
			}
		}
		return 0;
	}
}

/* (for experimentation purposes...) returns NULL on failure */
Matrix* matrix_multiply_new(const Matrix* A, const Matrix* B) {
	if (A->cols != B->rows) {
		fprintf(stderr, "could not multiply these matrices: A.cols != B.rows (inner dimensions do not match!)");
		return NULL;
	} else {
		Matrix* result = matrix_create(A->rows, B->cols);
		matrix_multiply(A, B, result);

		return result;
	}
}

int matrix_multiply_add(const Matrix* A, const Matrix* B, Matrix* result) {

	if (A->cols != B->rows) {
		fprintf(stderr, "could not multiply these matrices: A.cols != B.rows (inner dimensions do not match!)");
		return -1;
	} else if (result->rows != A->rows || result->cols != B->cols) {
		fprintf(stderr, "could not store result in provided matrix: result.rows != A.rows or result.cols != B.cols");
		return -1;
	} else {

		for (int row = 0; row < result->rows; row++) {
			for (int col = 0; col < result->cols; col++) {

				float sum = 0.0f;

				for (int index = 0; index < A->cols; index++) {

					sum += 
						matrix_get(A, row, index) *
						matrix_get(B, index, col);
				}
				matrix_set(result,
						   row,
						   col,
						   matrix_get(result, row, col) + sum);
			}
		}
		return 0;
	}
}

int matrix_copy(const Matrix* src, Matrix* dst) {
	if (src->rows != dst->rows || src->cols != dst->cols) {
		fprintf(stderr, "could not copy these matrices: src.rows != dst.rows or src.cols != dst.cols");
		return -1;
	} else {
		for (int row = 0; row < src->rows; row++) {
			for (int col = 0; col < src->cols; col++) {
				matrix_set(dst, row, col, matrix_get(src, row, col));
			}
		}
		return 0;
	}
}

int matrix_equals(const Matrix* A, const Matrix* B) {
	if (A->rows != B->rows || A->cols != B->cols) {
		return -1; // not equal
	} else {
		for (int row = 0; row < A->rows; row++) {
			for (int col = 0; col < A->cols; col++) {
				if (matrix_get(A, row, col) != matrix_get(B, row, col)) {
					return -1; // not equal
				}
			}
		}
		return 0; // equal
	}
}

int matrix_add(const Matrix* A, const Matrix* B, Matrix* result) {
	if (A->rows != B->rows || A->cols != B->cols) {
		fprintf(stderr, "could not add these matrices: A.rows != B.rows or A.cols != B.cols");
		return -1;
	} else if (result->rows != A->rows || result->cols != A->cols) {
		fprintf(stderr, "could not store result in provided matrix: result.rows != A.rows or result.cols != A.cols");
		return -1;
	} else {
		for (int row = 0; row < A->rows; row++) {
			for (int col = 0; col < A->cols; col++) {
				matrix_set(result, row, col, matrix_get(A, row, col) + matrix_get(B, row, col));
			}
		}
		return 0;
	}
}

int matrix_subtract(const Matrix* A, const Matrix* B, Matrix* result) {
	if (A->rows != B->rows || A->cols != B->cols) {
		fprintf(stderr, "could not subtract these matrices: A.rows != B.rows or A.cols != B.cols");
		return -1;
	} else if (result->rows != A->rows || result->cols != A->cols) {
		fprintf(stderr, "could not store result in provided matrix: result.rows != A.rows or result.cols != A.cols");
		return -1;
	} else {
		for (int row = 0; row < A->rows; row++) {
			for (int col = 0; col < A->cols; col++) {
				matrix_set(result, row, col, matrix_get(A, row, col) - matrix_get(B, row, col));
			}
		}
		return 0;
	}
}