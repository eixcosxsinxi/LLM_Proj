#include <stdio.h>
#include <stdint.h>
#include <assert.h>
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

int run_linear_layer_tests() {
	printf("\nthis is a test of linear layers\n");

	test_linear_create();
	test_linear_free();

	return 0;
}