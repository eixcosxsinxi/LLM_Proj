#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "matrix.h"
#include "loss.h"
#include "loss_test.h"

void test_mse_forward() {
	printf("\ntest loss_mse_forward\n");

	Matrix* prediction = matrix_create(2, 2);
	Matrix* target = matrix_create(2, 2);

	matrix_set(prediction, 0, 0, 3.0f);
	matrix_set(prediction, 0, 1, -1.0f);
	matrix_set(prediction, 1, 0, 5.0f);
	matrix_set(prediction, 1, 1, -3.0f);

	printf("prediction matrix:\n");
	matrix_print(prediction);

	matrix_set(target, 0, 0, 1.0f);
	matrix_set(target, 0, 1, 1.0f);
	matrix_set(target, 1, 0, 3.0f);
	matrix_set(target, 1, 1, -1.0f);

	printf("target matrix:\n");
	matrix_print(target);

	float expected = 4.0f;
	printf("expected loss: %f\n", expected);

	float loss = loss_mse_forward(prediction, target);
	printf("actual loss: %f\n", loss);

	assert(expected == loss);

	matrix_free(&prediction);
	matrix_free(&target);
}

void test_mse_backward() {
	printf("\ntest loss_mse_backward\n");

	Matrix* prediction = matrix_create(2, 2);
	Matrix* target = matrix_create(2, 2);
	Matrix* gradient = matrix_create(2, 2);
	Matrix* expected = matrix_create(2, 2);

	matrix_set(prediction, 0, 0, 3.0f);
	matrix_set(prediction, 0, 1, -1.0f);
	matrix_set(prediction, 1, 0, 5.0f);
	matrix_set(prediction, 1, 1, -3.0f);

	printf("prediction matrix:\n");
	matrix_print(prediction);

	matrix_set(target, 0, 0, 1.0f);
	matrix_set(target, 0, 1, 1.0f);
	matrix_set(target, 1, 0, 3.0f);
	matrix_set(target, 1, 1, -1.0f);

	printf("target matrix:\n");
	matrix_print(target);

	matrix_set(expected, 0, 0, 1.0f);
	matrix_set(expected, 0, 1, -1.0f);
	matrix_set(expected, 1, 0, 1.0f);
	matrix_set(expected, 1, 1, -1.0f);

	printf("expected matrix:\n");
	matrix_print(expected);

	loss_mse_backward(prediction, target, gradient);

	printf("actual gradient matrix:\n");
	matrix_print(gradient);

	assert(matrix_equals(expected, gradient) == 0);

	matrix_free(&prediction);
	matrix_free(&target);
	matrix_free(&gradient);
	matrix_free(&expected);
}

void run_loss_tests() {
	printf("\nthis is a test of loss functions\n");
	
	test_mse_forward();
	test_mse_backward();
}