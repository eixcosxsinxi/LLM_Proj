#ifndef LOSS_H
#define LOSS_H

#include "matrix.h"

float loss_mse_forward(const Matrix* prediction, const Matrix* target);
int loss_mse_backward(const Matrix* prediction, const Matrix* target, Matrix* gradient);

#endif