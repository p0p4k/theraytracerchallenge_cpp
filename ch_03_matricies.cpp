#include "matrix.h"
#include "tuple.h"

int main() {

  Matrix id = Matrix::identity(4);
  Matrix id_inv = id.inverse();

  id_inv.print_matrix();

  Matrix product = id.matrix_multiply(id_inv);
  product.print_matrix();

  Matrix A(4, 4);
  A[0][0] = -5.0;
  A[0][1] = 2.0;
  A[0][2] = 6.0;
  A[0][3] = -8.0;
  A[1][0] = 1.0;
  A[1][1] = -5.0;
  A[1][2] = 1.0;
  A[1][3] = 8.0;
  A[2][0] = 7.0;
  A[2][1] = 7.0;
  A[2][2] = -6.0;
  A[2][3] = -7.0;
  A[3][0] = 1.0;
  A[3][1] = -3.0;
  A[3][2] = 7.0;
  A[3][3] = 4.0;

  Matrix B = A.inverse();
  Matrix transpose_of_inv = B.transpose();
  std::cout << "Transpose of inverse" << std::endl;
  transpose_of_inv.print_matrix();

  Matrix C = A.transpose();
  Matrix inv_of_transpose = C.inverse();
  std::cout << "Inverse of transpose" << std::endl;
  inv_of_transpose.print_matrix();

  RayTuple t(1, 2, 3, 1);
  RayTuple tuple_product = id.tuple_multiply(t);
  tuple_product.print_tuple();

  id[0][1] = 2.0;
  RayTuple tuple_product_changed = id.tuple_multiply(t);
  tuple_product_changed.print_tuple();

  return 0;
}
