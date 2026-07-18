#include <stdlib.h>
#include <time.h>

#include "matrix_test.h"
#include "linear_layer_test.h"

int main() {
	srand(time(NULL)); // initialize seed for random generation

	run_matrix_tests();
	run_linear_layer_tests();

	return 0;
}