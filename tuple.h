#ifndef TUPLE_H
#define TUPLE_H

#include "utilities.h"
#include <iostream>

class RayTuple;
class RayPoint;
class RayVector;

class RayTuple {
public:
  RayTuple(double x, double y, double z, double w);
  double x;
  double y;
  double z;
  double w;

  void iswhat() const;
  void print_tuple() const;

  RayTuple operator-(const RayTuple &other) const;
  RayTuple operator+(const RayTuple &other) const;
  RayTuple operator-() const;
  RayTuple operator*(const double scalar) const;
  RayTuple operator/(const double scalar) const;

  double magnitude() const;
  RayTuple normalize() const;

  double dot(const RayTuple &other) const;
};

class RayPoint : public RayTuple {
public:
  RayPoint(double x, double y, double z);
  RayPoint(const RayTuple &t);
};

class RayVector : public RayTuple {
public:
  RayVector(double x, double y, double z);
  RayVector(const RayTuple &t);
  RayVector cross(const RayVector &other) const;
  RayVector normalize() const;
  RayVector reflect(const RayVector &normal) const;
};

inline bool operator==(const RayTuple &t1, const RayTuple &t2) {
  return equal(t1.x, t2.x) && equal(t1.y, t2.y) && equal(t1.z, t2.z) &&
         equal(t1.w, t2.w);
}

inline bool operator!=(const RayTuple &t1, const RayTuple &t2) {
  return !(t1 == t2);
}

inline RayVector operator+(const RayVector &v1, const RayVector &v2) {
  return RayVector(v1.x + v2.x, v1.y + v2.y, v1.y + v2.y);
}

inline RayPoint operator+(const RayPoint &p, const RayVector &v) {
  return RayPoint(p.x + v.x, p.y + v.y, p.z + v.z);
}

inline RayPoint operator+(const RayVector &v, const RayPoint &p) {
  return RayPoint(p.x + v.x, p.y + v.y, p.z + v.z);
}

inline bool operator==(const RayPoint &p1, const RayPoint &p2) {
  return equal(p1.x, p2.x) && equal(p1.y, p2.y) && equal(p1.z, p2.z);
}

inline bool operator==(const RayVector &v1, const RayVector &v2) {
  return equal(v1.x, v2.x) && equal(v1.y, v2.y) && equal(v1.z, v2.z);
}

inline bool operator!=(const RayPoint &p1, const RayPoint &p2) {
  return !(p1 == p2);
}

inline bool operator!=(const RayVector &v1, const RayVector &v2) {
  return !(v1 == v2);
}

inline RayVector operator-(const RayPoint &p1, const RayPoint &p2) {
  return RayVector(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}

inline RayPoint operator-(const RayPoint &p, const RayVector &v) {
  return RayPoint(p.x - v.x, p.y - v.y, p.z - v.z);
}

inline RayVector operator-(const RayVector &v1, const RayVector &v2) {
  return RayVector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline RayVector operator-(const RayVector &v) {
  return RayVector(-v.x, -v.y, -v.z);
}

inline RayVector operator*(const RayVector &v, const double scalar) {
  return RayVector(v.x * scalar, v.y * scalar, v.z * scalar);
}

inline RayVector operator*(const double scalar, const RayVector &v) {
  return RayVector(v.x * scalar, v.y * scalar, v.z * scalar);
}

inline RayVector operator/(const RayVector &v, const double scalar) {
  return RayVector(v.x / scalar, v.y / scalar, v.z / scalar);
}

#endif
