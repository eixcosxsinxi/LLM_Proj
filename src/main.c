#include <stdio.h>
#include <stdint.h>
#include "matrix.h"
#include "linear_layer.h"
#include "loss.h"
#include "optimizer.h"

// TODO: develop your own NaN so you can remove math.h
// TODO: go through all methods that have Matrix as parameter and add check if that matrix is NULL
// TODO: reformat matrix_transpose to take in input and output matrix so that return can be int for failure
// TODO: later when tensor library is created, reformat all Matrix as Tensor

int main() {

	Matrix* batch = matrix_create(5, 3);
	Matrix* target = matrix_create(5, 1);

	matrix_set(batch, 0, 0, 2.0f);
	matrix_set(batch, 0, 1, 5.0f);
	matrix_set(batch, 0, 2, 70.0f);
	matrix_set(batch, 1, 0, 1.6f);
	matrix_set(batch, 1, 1, 6.0f);
	matrix_set(batch, 1, 2, 72.0f);
	matrix_set(batch, 2, 0, 1.333f);
	matrix_set(batch, 2, 1, 7.0f);
	matrix_set(batch, 2, 2, 74.0f);
	matrix_set(batch, 3, 0, 1.143f);
	matrix_set(batch, 3, 1, 8.0f);
	matrix_set(batch, 3, 2, 76.0f);
	matrix_set(batch, 4, 0, 1.0f);
	matrix_set(batch, 4, 1, 9.0f);
	matrix_set(batch, 4, 2, 78.0f);

	matrix_set(target, 0, 0, 344.8f);
	matrix_set(target, 1, 0, 277.3f);
	matrix_set(target, 2, 0, 231.8f);
	matrix_set(target, 3, 0, 199.2f);
	matrix_set(target, 4, 0, 174.6f);

	Matrix* Y_pred = matrix_create(target->rows, target->cols);
	Matrix* d_Y = matrix_create(Y_pred->rows, Y_pred->cols);

	LinearLayer* layer = linear_create(3, 1);

	float learning_rate = 0.00018061f;
	BatchGD_opt* opt = BatchGD_create(learning_rate);

	int epochs = 2500000;

	for (int epoch = 0; epoch < epochs; epoch++) {
		// Forward
		linear_forward(batch, layer, Y_pred);

		// Loss
		float loss = loss_mse_forward(Y_pred, target);

		// Loss backward
		loss_mse_backward(Y_pred, target, d_Y);
		printf("loss for epoch %d is %.8f\n", epoch, loss);

		// Layer backward
		linear_backward(batch, d_Y, layer, NULL);

		// Update
		BatchGD_step(opt, layer->weight, layer->d_W);
		BatchGD_step(opt, layer->bias, layer->d_b);
	}

	printf("target matrix:\n");
	matrix_print(target);
	printf("trained matrix:\n");
	matrix_print(Y_pred);

	matrix_free(&batch);
	matrix_free(&target);
	matrix_free(&Y_pred);
	matrix_free(&d_Y);
	linear_free(&layer);
	BatchGD_free(&opt);

	return 0;
}