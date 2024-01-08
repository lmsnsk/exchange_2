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

int sum_and_sub(matrix_t *A, matrix_t *B, matrix_t *result, int is_sum) {
  int error = 0;
  if (A->columns != B->columns || A->rows != B->rows) {
    error = 2;
  } else {
    error = s21_create_matrix(A->rows, A->columns, result);
    if (!error) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          if (is_sum)
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          else
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    }
  }
  return error;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return sum_and_sub(A, B, result, 1);
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return sum_and_sub(A, B, result, 0);
}

int incorrect_matrix(matrix_t *A) {
  int res = 0;
  if (A->columns < 1 || A->rows < 1 || A == NULL || A->matrix == NULL) res = 1;
  return res;
}

// @brief функция сравнение матриц
// @param A первая матрица для сравнения
// @param B вторая матрица для сравнения
// @return результат сравнения (0 - не равны, 1 - равны)
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  double check;
  int compare = SUCCESS;
  if (A->columns == B->columns && A->rows == B->rows && !incorrect_matrix(A) &&
      !incorrect_matrix(B)) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        check = A->matrix[i][j] - B->matrix[i][j];
        if (fabs(check) > ACCURACY) {
          compare = FAILURE;
          break;
        }
      }
      if (check) break;
    }
  } else {
    compare = FAILURE;
  }
  return compare;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = 0;
  if (incorrect_matrix(A)) {
    error = 1;
  } else {
    error = s21_create_matrix(A->rows, A->columns, result);
    if (!error) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = number * A->matrix[i][j];
        }
      }
    }
  }
  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if (A->columns != B->rows || A->rows != B->columns) {
    error = 2;
  } else if (incorrect_matrix(A) || incorrect_matrix(B)) {
    error = 1;
  } else {
    error = s21_create_matrix(A->rows, B->columns, result);
    if (!error) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          result->matrix[i][j] = 0;
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    }
  }
  return error;
}