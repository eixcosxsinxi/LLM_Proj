#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "matrix.h"

/* Optimizer types */

typedef struct {
	float learning_rate;
} SGD_opt;

/* Creation */
SGD_opt* sgd_create(float learning_rate);

/* Anihilation */
void sgd_free(SGD_opt** opt);

/* Update */
int sgd_step(const SGD_opt* opt, Matrix* parameter, const Matrix* gradient);

#endif