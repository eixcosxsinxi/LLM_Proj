#ifndef LOSS_H
#define LOSS_H

#include "matrix.h"

float loss_mean_squared_error(const Matrix* prediction, const Matrix* target);

#endif