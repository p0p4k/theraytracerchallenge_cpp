#ifndef RAY_H
#define RAY_H
#include "matrix.h"
#include "tuple.h"

class Ray {
public:
  RayPoint origin;
  RayVector direction;
  Ray(RayPoint o, RayVector d);

  RayPoint position(const double &t) const;

  Ray transform(const Matrix &transformation) const;
};

#endif
