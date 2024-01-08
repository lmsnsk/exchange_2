#include <check.h>

#include "s21_matrix.h"

void print_matrix(matrix_t A);

double get_rand(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}

int main(void) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(rows, cols, &mtx);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double rand_val = get_rand(DBL_MIN, DBL_MAX);
      m.matrix[i][j] = rand_val;
      mtx.matrix[i][j] = rand_val;
    }
  }
  int res = s21_eq_matrix(&m, &mtx);
  printf("%d %d\n", m.rows, m.columns);
  printf("%d %d\n", mtx.rows, mtx.columns);
  printf("%e %e\n", m.matrix[0][0], mtx.matrix[0][0]);
  printf("%d\n", res);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);

  return 0;
}

void print_matrix(matrix_t A) {
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      printf("%f ", A.matrix[i][j]);
      if (j == A.columns - 1) printf("\n");
    }
  }
  printf("\n");
}