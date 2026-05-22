#ifndef MATRIX_H
#define MATRIX_H

#include "tuple.h"
#include "utilities.h"
#include <initializer_list>
#include <vector>

class Matrix {
public:
  unsigned int rows, columns;
  std::vector<double> M;
  Matrix(unsigned int r, unsigned int c)
      : rows(r), columns(c), M(rows * columns, 0.0) {};

  const double *operator[](unsigned int r) const;
  double *operator[](unsigned int r);

  bool operator==(const Matrix &other) const;
  bool operator!=(const Matrix &other) const;

  Matrix matrix_multiply(const Matrix &other) const;
  RayTuple tuple_multiply(const RayTuple &other) const;
  Matrix transpose() const;
  double determinant() const;
  Matrix submatrix(unsigned int i, unsigned int j) const;
  double minor(unsigned int i, unsigned int j) const;
  double cofactor(unsigned int i, unsigned int j) const;
  bool is_invertible() const;
  Matrix inverse() const;

  static Matrix identity(unsigned int size);
  static Matrix translation(double x, double y, double z);
  static Matrix scaling(double x, double y, double z);
  static Matrix rotation_x(double angle);
  static Matrix rotation_y(double angle);
  static Matrix rotation_z(double angle);
  static Matrix shearing(double xy, double xz, double yx, double yz, double zx,
                         double zy);
  RayPoint transform_point(const RayPoint &p) const;
  RayVector transform_vector(const RayVector &v) const;
  static Matrix chain_transforms(const std::initializer_list<Matrix> chain);

  void print_matrix() const;
};

#endif
