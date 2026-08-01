#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"
#include "loss.h"

/* given a prediction matrix and a target matrix, use MSE (mean squared error) to provide a loss scalar. */
float loss_mse_forward(const Matrix* prediction, const Matrix* target) {
	if (prediction->rows != target->rows || prediction->cols != target->cols) {
		return NAN;
	} else {
		/*
		* The mean squared error (MSE) is the average (mean) of all the squared errors.
		* The formula is then (1/N) * Σ[(Y_i - T_i)^2] where T is the target matrix and Y is the prediction matrix (output of forward pass of layer)
		*/
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

/* given a prediction matrix and a target matrix, calculate and store MSE gradient dL/dY */
int loss_mse_backward(const Matrix* prediction, const Matrix* target, Matrix* gradient) {
	if (prediction->rows != target->rows || prediction->cols != target->cols) {
		fprintf(stderr, "size of target and prediction matrices do not match\n");
		return -1;
	} else if (gradient->rows != prediction->rows || gradient->cols != prediction->cols) {
		fprintf(stderr, "size of gradient does not match\n");
		return -1;
	} else {
		int N = target->rows * target->cols;
		for (int i = 0; i < N; i++) {
			/* 
			* This comes from the derivative of the MSE Loss function.
			* The Loss function can be represented as L(Y, T) where Y is the prediction matrix and T is the target matrix.
			* The MSE Loss function L(Y, T) = (1/N) * Σ[(Y_i - T_i)^2].
			* The derivative is then (2/N) * (Y - T).
			* This is calculated for every index of Y and T making this the "list of all partials" which is why it is called a gradient.
			*/
			gradient->data[i] = (2.0f/N) * (prediction->data[i] - target->data[i]);
		}
		return 0;
	}
}