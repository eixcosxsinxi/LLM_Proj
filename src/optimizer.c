#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "optimizer.h"

/* Creation */
BatchGD_opt* BatchGD_create(float learning_rate) {
	BatchGD_opt* opt = calloc(1, sizeof(BatchGD_opt));

	if (opt == NULL) {
		fprintf(stderr, "Failed to allocate BatchGD_opt\n");
		free(opt);
		return NULL;
	}

	opt->learning_rate = learning_rate;
}

/* Anihilation */
void BatchGD_free(BatchGD_opt** opt) {
	(*opt)->learning_rate = 0.0f;
	free(*opt);
	*opt = NULL;
}

/* Update */
int BatchGD_step(const BatchGD_opt* opt, Matrix* parameter, const Matrix* gradient) {
	if (gradient->rows != parameter->rows || gradient->cols != parameter->cols) {
		fprintf(stderr, "gradient is not the same size as parameter\n");
		return -1;
	} else if (gradient == NULL) {
		fprintf(stderr, "gradient is NULL\n");
		return -1;
	} else if (parameter == NULL) {
		fprintf(stderr, "parameter is NULL\n");
		return -1;
	}

	Matrix* temp = matrix_create(gradient->rows, gradient->cols);

	int ret = matrix_scalar_multiply(gradient, opt->learning_rate, temp);
	if (ret == -1) {
		fprintf(stderr, "matrix_scalar_multiply did not work\n");
		matrix_free(&temp);
		return -1;
	}

	ret = matrix_subtract(parameter, temp, parameter);
	if (ret == -1) {
		fprintf(stderr, "matrix_subtract did not work\n");
		matrix_free(&temp);
		return -1;
	}

	matrix_free(&temp);
	return 0;
}