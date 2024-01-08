#include <check.h>

#include "s21_matrix.h"

void print_matrix(matrix_t A);

double get_rand(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}

int main(void) {
  matrix_t A, B, res;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &B);
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 2.0;
  A.matrix[2][0] = 2.0;
  A.matrix[2][1] = 2.0;
  B.matrix[0][0] = 2.0;
  B.matrix[1][0] = 2.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][1] = 2.0;
  B.matrix[0][2] = 2.0;
  B.matrix[1][2] = 2.0;
  int er = s21_mult_matrix(&A, &B, &res);
  if (!er)
    print_matrix(res);
  else
    printf("%d\n", er);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
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