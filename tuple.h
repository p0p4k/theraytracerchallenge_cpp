#ifndef TUPLE_H
#define TUPLE_H

#include "utilities.h"
#include <iostream>

class RayTuple {
public:
  RayTuple(double x, double y, double z, double w);
  double x;
  double y;
  double z;
  double w;

  void iswhat();

  bool operator==(const RayTuple &other) const;
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
};

#endif
