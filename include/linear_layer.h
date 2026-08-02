#ifndef LINEAR_LAYER_H
#define LINEAR_LAYER_H

#include "matrix.h"

/* Data */

typedef struct {
	Matrix* weight;
	Matrix* bias;

	Matrix* d_W;
	Matrix* d_b;
} LinearLayer;

/* Funtions */

LinearLayer* linear_create(int input_size, int output_size);
void linear_free(LinearLayer** l);

void linear_initialize_weight(LinearLayer* l);
void linear_initialize_bias(LinearLayer* l);

int linear_forward_no_bias(const Matrix* input, const LinearLayer* l, Matrix* output);
int linear_forward(const Matrix* input, const LinearLayer* l, Matrix* output);
int linear_backward(const Matrix* input, const Matrix* d_Y, LinearLayer* l, Matrix* d_X);

#endif