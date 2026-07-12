#ifndef MATRIX_H
#define MATRIX_H

/* data */

typedef struct
{
	int rows;
	int cols;
	float* data;
} Matrix;

/* function declarations */

/* Creation */
Matrix* matrix_create(int rows, int cols);
void matrix_free(Matrix** m);
int matrix_copy(const Matrix* src, Matrix* dst);
// reshape
// resize
// view

/* Utilities */
float matrix_get(const Matrix* m, int row, int col);
int matrix_set(Matrix* m, int row, int col, float value);
void matrix_print(const Matrix* m);
int matrix_equals(const Matrix* A, const Matrix* B);
// save
// load
Matrix* matrix_multiply_new(const Matrix*A, const Matrix* B);

/* Initialization */
// TODO: fill
// zeroes
// ones
// identitiy
// uniform
// normal
// xavier
// he

/* Arithmetic */
int matrix_add(const Matrix* A, const Matrix* B, Matrix* result);
int matrix_subtract(const Matrix* A, const Matrix* B, Matrix* result);
// TODO: scale
int matrix_multiply(const Matrix* A, const Matrix* B, Matrix* result);
int matrix_multiply_add(const Matrix* A, const Matrix* B, Matrix* result);
// TODO: hadamard

/* Statistics */
// sum
// mean
// variance
// stddev
// max
// min
// argmax

/* Transformations */
// TODO: transpose
// slice
// concatenate
// flatten

#endif