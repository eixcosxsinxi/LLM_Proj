#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

/* this gives you an instance of a Matrix struct as a pointer (because all the helper methods pass in pointers) */
Matrix* matrix_create(int rows, int cols) 
{
    Matrix* m = malloc(sizeof(Matrix));

    if (m == NULL) {
        fprintf(stderr, "Failed to allocate matrix.\n");
        free(m);
        exit(EXIT_FAILURE);
    }

    m->rows = rows;
    m->cols = cols;

    m->data = malloc(rows * cols * sizeof(float));

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

float matrix_get(const Matrix* m, int row, int col) {

}