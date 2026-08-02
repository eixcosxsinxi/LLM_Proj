#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "matrix.h"
#include "optimizer.h"
#include "optimizer_test.h"

void test_BatchGD_step() {
	printf("\ntest BatchGD_step\n");

	BatchGD_opt* opt = BatchGD_create(0.1f);

	Matrix* parameter = matrix_create(2, 2);
	Matrix* gradient = matrix_create(2, 2);
	Matrix* expected = matrix_create(2, 2);

	matrix_fill(parameter, 1.0f);
	matrix_fill(gradient, 0.5f);
	matrix_fill(expected, 0.95f);

	printf("parameter matrix:\n");
	matrix_print(parameter);

	printf("gradient matrix:\n");
	matrix_print(gradient);

	printf("expected result:\n");
	matrix_print(expected);

	BatchGD_step(opt, parameter, gradient);

	printf("result matrix:\n");
	matrix_print(parameter);

	assert(matrix_equals(expected, parameter) == 0);

	BatchGD_free(&opt);
	matrix_free(&parameter);
	matrix_free(&gradient);
	matrix_free(&expected);
}

int run_optimizer_tests() {
	printf("\nthis is a test of optimizers\n");

	test_BatchGD_step();

	return 0;
}