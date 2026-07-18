#ifndef MATRIX_TEST_H
#define MATRIX_TEST_H

void test_create();
void test_free();
void test_get();
void test_set();
void test_print();
void test_multiply();
void test_multiply_AB_dimensions();
void test_multiply_result_dimensions();
void test_multiply_add();
void test_equals();
void test_copy();
void test_copy_dimension_mismatch();
void test_add();
void test_add_dimension_mismatch();
void test_subtract();
void test_subtract_dimension_mismatch();
void test_scalar_multiply();
void test_scalar_dimension_mismatch();
void test_fill();	
void test_hadamard();
void test_hadamard_AB_dimensions();
void test_hadamard_result_dimension();
void test_transpose();
void test_broadcast();
void test_broadcast_AB_dimensions();
void test_broadcast_result_dimensions();
void test_matrix_fill_uniform();

int run_matrix_tests();

#endif