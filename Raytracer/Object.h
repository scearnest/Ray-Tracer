#ifndef _OBJECT_H
#define _OBJECT_H

#include "Ray.h"

class Object {

public:

  Vect3D normal;
  Vect3D matDiff;
  Vect3D specHighLight;
  int phongConstant;
  double reflectivity;

  Object();

  virtual bool findIntersection(Ray ray, double &t){return 0;}
  Vect3D getNormal(){return normal;}
  Vect3D getMatDiff() {return matDiff;}
  Vect3D getSpecHighLight() { return specHighLight;}
  int getPhongConstant() { return phongConstant;}
  double getReflectivity() { return reflectivity;}

};

Object::Object(){}


#endif
