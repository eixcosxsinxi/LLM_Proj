#ifndef LINEAR_LAYER_H
#define LINEAR_LAYER_H

#include "Matrix.h"

/* Data */

typedef struct {
	Matrix* weight;
	Matrix* bias;
} LinearLayer;

/* Funtions */

LinearLayer* linear_create(int input_size, int output_size);
void linear_free(LinearLayer** l);

// Matrix* get_weight(LinearLayer* l);
// void set_weight(LinearLayer* l, Matrix* W);

// Matrix* get_bias(LinearLayer* l);
// void set_bias(LinearLayer* l, Matrix* B);

void linear_initialize_weight(LinearLayer* l);
void linear_initialize_bias(LinearLayer* l);

int linear_forward_no_bias(const Matrix* input, const LinearLayer* l, Matrix* output);
int linear_forward(const Matrix* input, const LinearLayer* l, Matrix* output);

// void linear_backward(LinearLayer* l);
// void linear_update(LinearLayer* l);

#endif