#include <stdio.h>
#include <stdint.h>
#include "matrix.h"
#include "linear_layer.h"

// TODO: develop your own NaN so you can remove math.h
// TODO: go through all methods that have Matrix as parameter and add check if that matrix is NULL
// TODO: reformat matrix_transpose to take in input and output matrix so that return can be int for failure
// TODO: later when tensor library is created, reformat all Matrix as Tensor

int main() {

	Matrix* m = matrix_create(3, 3);

	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			if (i == j) {
				matrix_set(m, i, j, 1);
			} else {
				matrix_set(m, i, j, 0);
			}
		}
	}

	printf("\nidentity matrix:\n");
	matrix_print(m);
	matrix_free(&m);

	return 0;
}