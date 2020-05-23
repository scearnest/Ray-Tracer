#ifndef _SPHERE_H
#define _SPHERE_H

#include "math.h"
#include <algorithm>
#include "Object.h"
#include "Vect3D.h"


class Sphere : public Object {
  Vect3D position;
  double radius;


public:
  Sphere();
  Sphere(Vect3D, double, Vect3D, Vect3D, int, double);

  Vect3D getPosition() { return position;}
  double getRadius() { return radius; }

  bool findIntersection(Ray ray, double &t);
  void calcNormal(Vect3D p) {normal = (p.sub(position)).mult(1/radius).norm();}
  Vect3D calcPoint(Vect3D o, Vect3D d, double t) { return o.add(d.mult(t));}

};

Sphere::Sphere() {
  position = Vect3D(0,0,0);
  radius = 1.0;
  normal = Vect3D(0,1,0);
}

Sphere::Sphere(Vect3D p, double r,  Vect3D md, Vect3D sh, int pc, double rf) {
  position = p;
  radius = r;
  matDiff = md;
  specHighLight = sh;
  phongConstant = pc;
  normal = Vect3D(0,1,0);
  reflectivity = rf;
}

bool Sphere::findIntersection(Ray ray, double &t) {

  Vect3D oc = ray.getOrigin().sub(position);
  double a = ray.getDirection().dot(ray.getDirection());
  double b = 2.0 * (oc.dot(ray.getDirection()));
  double c = oc.dot(oc) - radius*radius;

  double discriminant = b*b - 4*a*c;
  if(discriminant < 0) { return false; }

  double t0 = (-b + sqrt(discriminant))/(2*a);
  double t1 = (-b - sqrt(discriminant))/(2*a);

  if(t0 == t1) { t = t1;}
  else if(t0 > t1 && t1 > 0) { t = t1;}
  else if(t1 > t0 && t0 > 0) { t = t0;}
  else {return false;}

  calcNormal(calcPoint(ray.getOrigin(), ray.getDirection(), t));
  return true;
}

#endif
