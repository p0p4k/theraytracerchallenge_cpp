#include "tuple.h"
#include <cmath>

// tuple
RayTuple::RayTuple(double x, double y, double z, double w)
    : x(x), y(y), z(z), w(w) {}

void RayTuple::iswhat() const {
  if (w == 1.0)
    std::cout << "is a point" << std::endl;
  if (w == 0.0)
    std::cout << "is a vector" << std::endl;
}

void RayTuple::print_tuple() const {
  std::cout << "x: " << x << " y: " << y << " z: " << z << " w: " << w
            << std::endl;
}

RayTuple RayTuple::operator-(const RayTuple &other) const {
  return RayTuple(x - other.x, y - other.y, z - other.z, w - other.w);
}
RayTuple RayTuple::operator+(const RayTuple &other) const {
  return RayTuple(x + other.x, y + other.y, z + other.z, w + other.w);
}
RayTuple RayTuple::operator-() const { return RayTuple(-x, -y, -z, -w); }
RayTuple RayTuple::operator*(const double scalar) const {
  return RayTuple(x * scalar, y * scalar, z * scalar, w * scalar);
}
RayTuple RayTuple::operator/(const double scalar) const {
  return RayTuple(x / scalar, y / scalar, z / scalar, w / scalar);
}

// point
RayPoint::RayPoint(double x, double y, double z) : RayTuple(x, y, z, 1.0) {}
RayPoint::RayPoint(const RayTuple &t) : RayTuple(t.x, t.y, t.z, 1.0) {}

// vector
RayVector::RayVector(double x, double y, double z) : RayTuple(x, y, z, 0.0) {}
RayVector::RayVector(const RayTuple &t) : RayTuple(t.x, t.y, t.z, 0.0) {}

RayVector RayVector::cross(const RayVector &other) const {
  return RayVector(y * other.z - z * other.y, z * other.x - x * other.z,
                   x * other.y - y * other.x);
}

RayVector RayVector::normalize() const {
  return RayVector(RayTuple::normalize());
}

RayVector RayVector::reflect(const RayVector &normal) const {
  return (*this) - (normal * 2.0) * (this->dot(normal));
}

// utilities
double RayTuple::magnitude() const { return std::sqrt(x * x + y * y + z * z); }

RayTuple RayTuple::normalize() const {
  double mv = this->magnitude();
  return RayTuple(x / mv, y / mv, z / mv, w);
}

double RayTuple::dot(const RayTuple &other) const {
  return x * other.x + y * other.y + z * other.z + w * other.w;
}
