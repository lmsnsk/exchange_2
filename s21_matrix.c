#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = 0;

  if (rows < 1 || columns < 1) {
    error = 1;
  } else {
    result->columns = columns;
    result->rows = rows;
    result->matrix = (double **)calloc(rows, sizeof(double *));
  }
  if (!error && result->matrix) {
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      if (!result->matrix[i]) {
        for (int j = 0; j < i; j++) free(result->matrix[j]);
        free(result->matrix);
        error = 1;
        break;
      }
    }
  }
  return error;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i]) free(A->matrix[i]);
    }
    free(A->matrix);
  }
  A->rows = 0;
  A->columns = 0;
  A->matrix = NULL;
}