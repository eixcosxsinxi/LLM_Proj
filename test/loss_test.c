#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "matrix.h"
#include "loss.h"
#include "loss_test.h"

void test_mean_squared_error() {
	printf("\ntest loss_mean_squared_error\n");

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

	float loss = loss_mean_squared_error(prediction, target);
	printf("actual loss: %f\n", loss);

	assert(expected == loss);

	matrix_free(&prediction);
	matrix_free(&target);
}

void run_loss_tests() {
	printf("\nthis is a test of loss functions\n");
	
	test_mean_squared_error();
}