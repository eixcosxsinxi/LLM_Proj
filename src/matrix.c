#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

/* this gives you an instance of a Matrix struct as a pointer (because all the helper methods pass in pointers) */
Matrix* matrix_create(int rows, int cols) 
{
    Matrix* m = calloc(sizeof(Matrix));

    if (m == NULL) {
        fprintf(stderr, "Failed to allocate matrix.\n");
        free(m);
        exit(EXIT_FAILURE);
    }

    m->rows = rows;
    m->cols = cols;

    m->data = calloc(rows * cols * sizeof(float));

    if (m->data == NULL) {
        fprintf(stderr, "Failed to allocate matrix data.\n");
        free(m);
        exit(EXIT_FAILURE);
    }

    return m;
}

/* this should free the space created by a Matrix and leave the pointer not hanging by setting it to NULL */
void matrix_free(Matrix** m) {
    free((*m)->data);
    free(*m);
    *m = NULL;
}

/* this should return the value at the specified row and column in the matrix */
float matrix_get(const Matrix* m, int row, int col) { // const so you don't accidentally modify the matrix
    return m->data[row * m->cols + col];
}

/* this should set the value at the specified row and column in the matrix */
void matrix_set(Matrix* m, int row, int col, float value) {
    m->data[row * m->cols + col] = value;
}

/* this should print the matrix to the console */
void matrix_print(const Matrix* m) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("%8.3f ", matrix_get(m, i, j));
        }
        printf("\n");
    }
}