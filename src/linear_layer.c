#include <stdio.h>
#include <stdlib.h>

#include "linear_layer.h"

/* 
* This should create a LinearLayer that has a weight with dimension input_size x output_size
* and a bias with dimension 1 x output_size. This way, the input matrix can have a dimension of
* batch_size x input_size and the output will have a dimension of batch_size x output_size.
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

	return l;
}

void linear_free(LinearLayer** l) {
	matrix_free(&((*l)->weight));
	matrix_free(&((*l)->bias));
	free(*l);
	*l = NULL;
}