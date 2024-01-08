#include <check.h>

#include "s21_matrix.h"

void print_matrix(matrix_t A);

double get_rand(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}

int main(void) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = -5.0;
  A.matrix[0][1] = -4.0;
  A.matrix[1][0] = -2.0;
  A.matrix[1][1] = -3.0;
  double b;
  int er = s21_determinant(&A, &b);
  if (!er)
    printf("%f\n", b);
  else
    printf("Error: %d\n", er);

  s21_remove_matrix(&A);
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