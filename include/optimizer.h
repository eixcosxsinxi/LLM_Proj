#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "matrix.h"

/* Optimizer types */

typedef struct {
	float learning_rate;
} BatchGD_opt;

/* Creation */
BatchGD_opt* BatchGD_create(float learning_rate);

/* Anihilation */
void BatchGD_free(BatchGD_opt** opt);

/* Update */
int BatchGD_step(const BatchGD_opt* opt, Matrix* parameter, const Matrix* gradient);

#endif