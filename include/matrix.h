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

Matrix* matrix_create(int rows, int cols);
void matrix_free(Matrix** m);
float matrix_get(const Matrix* m, int row, int col);
void matrix_set(Matrix* m, int row, int col, float value);
void matrix_print(const Matrix* m);

void matrix_multiply(const Matrix* A, const Matrix* B, Matrix* result);
Matrix* matrix_multiply_new(const Matrix*A, const Matrix* B);

#endif