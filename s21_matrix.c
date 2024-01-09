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
  if (A->columns < 1 || A->rows < 1 || !A->matrix) res = 1;
  return res;
}

// @brief функция сравнение матриц
// @param A первая матрица для сравнения
// @param B вторая матрица для сравнения
// @return результат сравнения (0 - не равны, 1 - равны)
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int compare = SUCCESS;
  if (A->columns == B->columns && A->rows == B->rows && !incorrect_matrix(A) &&
      !incorrect_matrix(B)) {
    double check;
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

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (incorrect_matrix(A)) {
    error = 1;
  } else {
    error = s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return error;
}

void minor_matrix(matrix_t *A, int row, int col, matrix_t *result) {
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      int k = i >= row ? i + 1 : i;
      int l = j >= col ? j + 1 : j;
      result->matrix[i][j] = A->matrix[k][l];
    }
  }
}

double det(matrix_t *A) {
  double result = 0;
  if (A->rows == 1) {
    result = A->matrix[0][0];
  } else {
    matrix_t temp = {0};
    s21_create_matrix(A->rows - 1, A->columns - 1, &temp);
    for (int j = 0; j < A->columns; j++) {
      minor_matrix(A, 0, j, &temp);
      result += pow(-1, j) * A->matrix[0][j] * det(&temp);
    }
    s21_remove_matrix(&temp);
  }
  return result;
}

int s21_determinant(matrix_t *A, double *result) {
  int error = 0;
  if (A->columns != A->rows) {
    error = 2;
  } else if (incorrect_matrix(A)) {
    error = 1;
  } else {
    *result = det(A);
  }
  return error;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (A->columns != A->rows) {
    error = 2;
  } else if (incorrect_matrix(A)) {
    error = 1;
  } else {
    error = s21_create_matrix(A->rows, A->columns, result);
    if (!error) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          matrix_t temp = {0};
          error = s21_create_matrix(A->rows - 1, A->columns - 1, &temp);
          if (!error) {
            minor_matrix(A, i, j, &temp);
            result->matrix[i][j] = pow(-1, i + j) * det(&temp);
            s21_remove_matrix(&temp);
          }
        }
      }
      if (error) {
        error = 2;
        s21_remove_matrix(result);
      }
    }
  }
  return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (A->columns != A->rows) {
    error = 2;
  } else if (incorrect_matrix(A)) {
    error = 1;
  } else {
    double determinant = det(A);
    if (determinant) {
      if (A->rows == 1) {
        error = s21_create_matrix(A->rows, A->columns, result);
        if (!error) result->matrix[0][0] = 1.0 / A->matrix[0][0];
      } else {
        matrix_t temp_mtx = {0};
        error = s21_calc_complements(A, &temp_mtx);
        if (!error) {
          matrix_t trans_temp_mtx = {0};
          error = s21_transpose(&temp_mtx, &trans_temp_mtx);
          if (!error) {
            error = s21_mult_number(&trans_temp_mtx, determinant, result);
            s21_remove_matrix(&trans_temp_mtx);
          }
          s21_remove_matrix(&temp_mtx);
        }
      }
    } else {
      error = 2;
    }
  }
  return error;
}
