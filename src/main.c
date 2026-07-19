#include <stdio.h>
#include <stdint.h>
#include "matrix.h"
#include "linear_layer.h"

// TODO: develop your own NaN so you can remove math.h

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