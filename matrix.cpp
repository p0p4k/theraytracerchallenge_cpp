#include "matrix.h"
#include <cassert>
#include <cmath>

void Matrix::print_matrix() const {
  for (unsigned int i = 0; i < rows; i++) {
    for (unsigned int j = 0; j < columns; j++) {
      std::cout << (*this)[i][j] << "\t";
    }
    std::cout << std::endl;
  }
}

const double *Matrix::operator[](unsigned int r) const {
  return &M[r * columns];
}

double *Matrix::operator[](unsigned int r) { return &M[r * columns]; }

bool Matrix::operator==(const Matrix &other) const {
  if ((other.rows != rows) || (other.columns != columns)) {
    return false;
  }
  for (size_t i = 0; i < M.size(); ++i) {
    if (!equal(other.M[i], M[i])) {
      return false;
    }
  }
  return true;
}

bool Matrix::operator!=(const Matrix &other) const { return !(*this == other); }

Matrix Matrix::matrix_multiply(const Matrix &other) const {
  assert(other.rows == columns);
  Matrix result(rows, other.columns);
  for (size_t r = 0; r < rows; ++r) {
    for (size_t oc = 0; oc < other.columns; ++oc) {
      for (size_t i = 0; i < columns; ++i) {
        // result[r][oc] += M[r * columns + i] * other.M[i * other.columns +
        // oc];
        result[r][oc] += (*this)[r][i] * other[i][oc];
      }
    }
  }
  return result;
}

RayTuple Matrix::tuple_multiply(const RayTuple &other) const {
  assert(columns == 4);
  RayTuple result(0, 0, 0, 0);
  result.x = other.x * (*this)[0][0] + other.y * (*this)[0][1] +
             other.z * (*this)[0][2] + other.w * (*this)[0][3];
  result.y = other.x * (*this)[1][0] + other.y * (*this)[1][1] +
             other.z * (*this)[1][2] + other.w * (*this)[1][3];
  result.z = other.x * (*this)[2][0] + other.y * (*this)[2][1] +
             other.z * (*this)[2][2] + other.w * (*this)[2][3];
  result.w = other.x * (*this)[3][0] + other.y * (*this)[3][1] +
             other.z * (*this)[3][2] + other.w * (*this)[3][3];
  return result;
}

Matrix Matrix::transpose() const {
  Matrix result(columns, rows);
  for (unsigned int r = 0; r < rows; ++r) {
    for (unsigned int c = 0; c < columns; ++c) {
      result[c][r] = (*this)[r][c];
    }
  }
  return result;
}

double Matrix::determinant() const {
  if (rows == 2 && columns == 2) {
    return (*this)[0][0] * (*this)[1][1] - (*this)[1][0] * (*this)[0][1];
  } else {
    double det = 0;
    for (unsigned int c = 0; c < columns; ++c) {
      det += (*this)[0][c] * (*this).cofactor(0, c);
    }
    return det;
  }
}

// Matrix Matrix::submatrix(int i, int j) const {
//   Matrix sm(rows - 1, columns - 1);
//   for (int r = 0; r < sm.rows; ++r) {
//     for (int c = 0; c < sm.columns; ++c) {
//       if (r < i && c < j) {
//         sm[r][c] = (*this)[r][c];
//       }
//       if (r >= i && c < j) {
//         sm[r][c] = (*this)[r + 1][c];
//       }
//       if (r < i && c >= j) {
//         sm[r][c] = (*this)[r][c + 1];
//       }
//       if (r >= i && c >= j) {
//         sm[r][c] = (*this)[r + 1][c + 1];
//       }
//     }
//   }
//   return sm;
// }

Matrix Matrix::submatrix(unsigned int i, unsigned int j) const {
  Matrix sm(rows - 1, columns - 1);
  for (unsigned int r = 0; r < sm.rows; ++r) {
    unsigned int source_r = (r < i) ? r : r + 1;
    for (unsigned int c = 0; c < sm.columns; ++c) {
      unsigned int source_c = (c < j) ? c : c + 1;
      sm[r][c] = (*this)[source_r][source_c];
    }
  }
  return sm;
}

double Matrix::minor(unsigned int i, unsigned int j) const {
  assert(rows > 2 && columns > 2);
  Matrix sm = (*this).submatrix(i, j);
  return sm.determinant();
}

double Matrix::cofactor(unsigned int i, unsigned int j) const {
  double minor = (*this).minor(i, j);
  return ((i + j) % 2 == 0) ? minor : -minor;
}

bool Matrix::is_invertible() const { return (*this).determinant() != 0.0; }

Matrix Matrix::inverse() const {
  assert((*this).is_invertible());
  double det_m = (*this).determinant();
  Matrix m2(rows, columns);
  for (unsigned int r = 0; r < rows; ++r) {
    for (unsigned int c = 0; c < columns; ++c) {
      double cf = (*this).cofactor(r, c);
      m2[c][r] = cf / det_m;
    }
  }
  return m2;
}

Matrix Matrix::identity(unsigned int size) {
  Matrix id(size, size);
  for (unsigned int i = 0; i < size; ++i) {
    id[i][i] = 1.0;
  }
  return id;
}

Matrix Matrix::translation(double x, double y, double z) {
  Matrix t = Matrix::identity(4);
  t[0][3] = x;
  t[1][3] = y;
  t[2][3] = z;
  return t;
}

Matrix Matrix::scaling(double x, double y, double z) {
  Matrix t = Matrix::identity(4);
  t[0][0] = x;
  t[1][1] = y;
  t[2][2] = z;
  return t;
}

Matrix Matrix::rotation_x(double angle) {
  Matrix t = Matrix::identity(4);
  t[1][1] = cos(angle);
  t[1][2] = -sin(angle);
  t[2][1] = -t[1][2];
  t[2][2] = t[1][1];
  return t;
}

Matrix Matrix::rotation_y(double angle) {
  Matrix t = Matrix::identity(4);
  t[0][0] = cos(angle);
  t[0][2] = sin(angle);
  t[2][0] = -t[0][2];
  t[2][2] = t[0][0];
  return t;
}

Matrix Matrix::rotation_z(double angle) {
  Matrix t = Matrix::identity(4);
  t[0][0] = cos(angle);
  t[0][1] = -sin(angle);
  t[1][0] = -t[0][1];
  t[1][1] = t[0][0];
  return t;
}

Matrix Matrix::shearing(double xy, double xz, double yx, double yz, double zx,
                        double zy) {
  Matrix t = Matrix::identity(4);
  t[0][1] = xy;
  t[0][2] = xz;
  t[1][0] = yx;
  t[1][2] = yz;
  t[2][0] = zx;
  t[2][1] = zy;
  return t;
}

RayPoint Matrix::transform_point(const RayPoint &p) const {
  return RayPoint(this->tuple_multiply(p));
}

RayVector Matrix::transform_vector(const RayVector &v) const {
  return RayVector(this->tuple_multiply(v));
}
