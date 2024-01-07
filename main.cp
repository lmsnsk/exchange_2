#include <check.h>

#include "s21_matrix.h"

void print_matrix(matrix_t* A);

double get_rand(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}

int main(void) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &result);
  A.matrix[0][0] = 0.67;
  A.matrix[0][1] = 1.67;
  A.matrix[1][0] = 2.67;
  A.matrix[1][1] = 3.67;
  B.matrix[0][0] = 0.67;
  B.matrix[0][1] = 1.67;
  B.matrix[1][0] = 2.67;
  B.matrix[1][1] = 3.67;
  print_matrix(&A);
  print_matrix(&B);
  int er = s21_sub_matrix(&A, &B, &result);
  if (er) {
    printf("ERROR: %d!\n", er);
  } else {
    print_matrix(&result);
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);

  return 0;
}

void print_matrix(matrix_t* A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      printf("%f ", A->matrix[i][j]);
      if (j == A->columns - 1) printf("\n");
    }
  }
  printf("\n");
}