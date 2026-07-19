#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"
#include "loss.h"

float loss_mean_squared_error(const Matrix* prediction, const Matrix* target) {
	if (prediction->rows != target->rows || prediction->cols != target->cols) {
		return NAN;
	} else {
		float error = 0.0f;
		int i;

		for (i = 0; i < target->rows * target->cols; i++) {
			float diff = (prediction->data[i] - target->data[i]);
			diff *= diff;
			error += diff;
		}

		error /= (float)i;
		return error;
	}
}