#include "s21_matrix.h"

void print_matrix(matrix_t* A);

int main(void) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 0.67;
  A.matrix[0][1] = 1.67;
  A.matrix[1][0] = 2.67;
  A.matrix[1][1] = 3.67;
  print_matrix(&A);
  s21_remove_matrix(&A);
  return 0;
}

void print_matrix(matrix_t* A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      printf("%f ", A->matrix[i][j]);
      if (j == A->columns - 1) printf("\n");
    }
  }
}