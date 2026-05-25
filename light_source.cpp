#include "light_source.h"
#include "tuple.h"
#include <cmath>

Color LightSource::lighting(const Material &m, const RayPoint &p,
                            const RayVector &eyev, const RayVector &normalv,
                            const bool in_shadow) const {

  Color ambient = Color(0, 0, 0);
  Color diffuse = Color(0, 0, 0);
  Color specular = Color(0, 0, 0);

  Color effective_color = m.color * this->intensity;

  RayVector lightv = (this->position - p).normalize();

  ambient = effective_color * m.ambient;

  if (in_shadow) {
    return ambient;
  }

  double light_dot_normal = lightv.dot(normalv);
  if (light_dot_normal < 0.0) {
    diffuse = Color(0, 0, 0);
    specular = Color(0, 0, 0);
  } else {
    diffuse = effective_color * m.diffuse * light_dot_normal;

    RayVector reflectv = (-lightv).reflect(normalv);
    double reflect_dot_eye = reflectv.dot(eyev);

    if (reflect_dot_eye <= 0.0) {
      specular = Color(0, 0, 0);
    } else {
      double factor = std::pow(reflect_dot_eye, m.shininess);
      specular = this->intensity * m.specular * factor;
    }
  }

  return ambient + diffuse + specular;
}

bool LightSource::operator==(const LightSource &other) const {
  return this->intensity == other.intensity && this->position == other.position;
}
