#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "matrix.h"

void test_matrix_create() {
    printf("\ntest_matrix_create\n");

    int rows = 3;
    int cols = 3;
    float data = 0;

    Matrix* m = matrix_create(rows, cols);
    m->data[0] = data;

    printf("rows = %d, m.rows = %d\n", rows, m->rows);
    assert(m->rows == rows);
    printf("cols = %d, m.cols = %d\n", cols, m->cols);
    assert(m->cols == cols);
    printf("data = %.6f, m.data = %.6f\n", data, *(m->data));
    assert(*(m->data) == data);
}

void test_matrix_free() {
    printf("\ntest_matrix_free\n");
    int rows = 3;
    int cols = 3;
    float data = 0;

    Matrix* m = matrix_create(rows, cols);
    m->data[0] = data;

    printf("rows before = %d\n", m->rows);
    printf("cols before = %d\n", m->cols);
    printf("data before = %.6f\n", m->data[0]);

    matrix_free(&m);

    printf("rows after = %d\n", m->rows);
    printf("cols after = %d\n", m->cols);
    printf("data after = %.6f\n", m->data[0]);

    assert(m->rows == 0);
    assert(m->cols == 0);
    assert(m->data == NULL);
}

int main() {
    test_matrix_create();
    test_matrix_free();
    return 0;
}