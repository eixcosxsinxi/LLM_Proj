#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "linear_layer.h"

/* 
* This should create a LinearLayer that has a weight with dimension input_size x output_size
* and a bias with dimension 1 x output_size. This way, the input matrix can have a dimension of
* batch_size x input_size and the output will have a dimension of batch_size x output_size.
* It should initialize the weight matrix and the bias matrix.
*/
LinearLayer* linear_create(int input_size, int output_size){
	LinearLayer* l = calloc(1, sizeof(LinearLayer));

	if (l == NULL) {
		fprintf(stderr, "Failed to allocate LinearLayer.\n");
		free(l);
		return NULL;
	}

	l->weight = matrix_create(input_size, output_size);
	if (l->weight == NULL) {
		fprintf(stderr, "Failed to allocate LinearLayer weight.\n");
		free(l);
		return NULL;
	}

	l->bias = matrix_create(1, output_size);
	if (l->bias == NULL) {
		fprintf(stderr, "Failed to allocate LinearLayer bias.\n");
		free(l);
		return NULL;
	}

	l->d_W = matrix_create(l->weight->rows, l->weight->cols);
	if (l->d_W == NULL) {
		fprintf(stderr, "Failed to allocate LinearLayer d_W.\n");
		free(l);
		return NULL;
	}

	l->d_b = matrix_create(l->bias->rows, l->bias->cols);
	if (l->d_b == NULL) {
		fprintf(stderr, "Failed to allocate LinearLayer d_b.\n");
		free(l);
		return NULL;
	}

	linear_initialize_weight(l); // initialize weight
	linear_initialize_bias(l); // iniitialize bias

	matrix_fill(l->d_W, 0.0f); // initialize d_W
	matrix_fill(l->d_b, 0.0f); // initialize d_b

	return l;
}

/* 
* helper method to initialize the weight matrix.
* right now, it is using uniform random distribution with range [-1.0f, 1.0f)
*/
void linear_initialize_weight(LinearLayer* l) {
	matrix_fill_uniform(l->weight, -1.0f, 1.0f);
}

/*
* helper method to initialize the bias matrix.
* right now, it fills the whole bias matrix with 0.0f
*/
void linear_initialize_bias(LinearLayer* l) {
	matrix_fill_zero(l->bias);
}

/*
* does the obvious: frees the memory previously used by LinearLayer* l.
* sets what was at l to NULL so there are no leftover artifacts of l.
*/
void linear_free(LinearLayer** l) {
	matrix_free(&((*l)->weight));
	matrix_free(&((*l)->bias));
	matrix_free(&((*l)->d_W));
	matrix_free(&((*l)->d_b));
	free(*l);
	*l = NULL;
}

/* calculates the prediction matrix Y from a linear layer l. excludes adding the bias. */
int linear_forward_no_bias(const Matrix* input, const LinearLayer* l, Matrix* output) {
	return matrix_multiply(input, l->weight, output);
}

/* calculates the prediction matrix Y from a linear layer l. includes adding the bias. */
int linear_forward(const Matrix* input, const LinearLayer* l, Matrix* output) {
	int ret = linear_forward_no_bias(input, l, output);

	if (ret == -1) {
		return ret;
	} else {
		return matrix_add_broadcast_row(output, l->bias, output);
	}
}

/* sets the d_W and the d_b variables for the linear layer and finds dL/dX to pass back to previous layer */
int linear_backward(const Matrix* input, const Matrix* d_Y, LinearLayer* l, Matrix* d_X) {
	/*
	* Through the chain rule, we can determine dL/dW = dL/dY * dY/dW.
	* Through a lot of good mathematical guessing, we can show that dL/dY * dY/dW = X^T * dL/dY.
	* A similar trick can be used to find dL/dX = dL/dY * W^T.
	* Since we have the input matrix X and we can find dL/dY for a particular loss function, we can calculate dL/dW.
	* dL/dW is useful for telling us how to change the weights given a particular loss.
	* dL/dX is useful for passing the chain rule backwards to the previous layer.
	* It acts like the previous layer's dL/dY since the Y of prev becomes the X of current.
	* dL/dB is hard to explain how to find but there is a formula for it.
	*/
	Matrix* X_transpose = matrix_transpose(input);
	if (X_transpose == NULL) {
		fprintf(stderr, "X_transpose matrix is NULL\n");
		matrix_free(&X_transpose);
		return -1;
	}

	int result = matrix_multiply(X_transpose, d_Y, l->d_W);
	if (result == -1) {
		fprintf(stderr, "X_transpose * d_Y did not work\n");
		matrix_free(&X_transpose);
		return -1;
	}

	matrix_free(&X_transpose);

	if (d_X != NULL) {	
		Matrix* W_transpose = matrix_transpose(l->weight);
		if (W_transpose == NULL) {
			fprintf(stderr, "W_transpose matrix is NULL\n");
			matrix_free(&W_transpose);
			return -1;
		}

		result = matrix_multiply(d_Y, W_transpose, d_X);
		if (result == -1) {
			fprintf(stderr, "d_Y * W_transpose did not work\n");
			matrix_free(&W_transpose);
			return -1;
		}

		matrix_free(&W_transpose);
	}

	/*
	* d_b[n] = SUM(d_Y[i, n], i, 0, batch_size)
	* basically to find the nth value of dL/db, you sum all the values in the nth column of dL/dY.
	* this comes from the multivariable chain rule theorem. the math checks out. trust me...
	*/
	for (int col = 0; col < d_Y->cols; col++) {
		float val = 0.0f;

		for (int row = 0; row < d_Y->rows; row++) {
			val += matrix_get(d_Y, row, col);
		}

		result = matrix_set(l->d_b, 0, col, val);
		if (result == -1) {
			fprintf(stderr, "couldn't set d_b[n]");
			return -1;
		}
	}

	return 0;
}