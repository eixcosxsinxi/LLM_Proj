#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "matrix.h"
#include "linear_layer.h"
#include "linear_layer_test.h"

void test_linear_create() {
	printf("\ntest linear_create\n");

	int input_size = 3;
	int output_size = 2;

	LinearLayer* l = linear_create(input_size, output_size);

	printf("weight dimensions should be %d x %d\n", input_size, output_size);
	printf("bias dimensions should be %d x %d\n", 1, output_size);

	printf("weight matrix:\n");
	matrix_print(l->weight);

	printf("bias matrix:\n");
	matrix_print(l->bias);

	assert(l->weight->rows == input_size && l->weight->cols == output_size);
	assert(l->bias->rows == 1 && l->bias->cols == output_size);

	linear_free(&l);
}

void test_linear_free() {
	printf("\ntest linear_free\n");

	LinearLayer* l = linear_create(3, 4);

	printf("weight dimensions are %d x %d\n", l->weight->rows, l->weight->cols);
	printf("bias dimensions are %d x %d\n", l->bias->rows, l->bias->cols);

	linear_free(&l);
	printf("l after free = %p\n", (void*)l);

	assert(l == NULL);
}

void test_linear_forward_no_bias() {
	printf("\ntest linear_forward_no_bias\n");

	LinearLayer* l = linear_create(3, 2);
	
	Matrix* input = matrix_create(4, 3);
	Matrix* output = matrix_create(4, 2);
	Matrix* expected = matrix_create(4, 2);

	matrix_fill(input, 2.0f);
	matrix_fill(l->weight, 3.0f);
	matrix_fill(expected, 18.0f);

	printf("input matrix:\n");
	matrix_print(input);

	printf("weight matrix:\n");
	matrix_print(l->weight);

	printf("expected result:\n");
	matrix_print(expected);

	linear_forward_no_bias(input, l, output);
	
	printf("result matrix:\n");
	matrix_print(output);

	assert(matrix_equals(expected, output) == 0);

	linear_free(&l);
	matrix_free(&input);
	matrix_free(&output);
	matrix_free(&expected);
}

void test_linear_forward() {
	printf("\ntest linear_forward\n");

	LinearLayer* l = linear_create(3, 2);

	Matrix* input = matrix_create(4, 3);
	Matrix* output = matrix_create(4, 2);
	Matrix* expected = matrix_create(4, 2);

	matrix_fill(input, 2.0f);
	matrix_fill(l->weight, 3.0f);
	matrix_fill(l->bias, 1.0f);
	matrix_fill(expected, 19.0f);

	printf("input matrix:\n");
	matrix_print(input);

	printf("weight matrix:\n");
	matrix_print(l->weight);

	printf("bias matrix:\n");
	matrix_print(l->bias);

	printf("expected matrix:\n");
	matrix_print(expected);

	linear_forward(input, l, output);

	printf("output matrix:\n");
	matrix_print(output);

	assert(matrix_equals(expected, output) == 0);

	linear_free(&l);
	matrix_free(&input);
	matrix_free(&output);
	matrix_free(&expected);
}

int run_linear_layer_tests() {
	printf("\nthis is a test of linear layers\n");

	test_linear_create();
	test_linear_free();
	test_linear_forward_no_bias();
	test_linear_forward();

	return 0;
}