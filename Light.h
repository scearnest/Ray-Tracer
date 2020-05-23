#ifndef _LIGHT_H
#define _LIGHT_H

#include "Vect3D.h"

class Light {
  Vect3D position;
  Vect3D color;

public:
  Light();
  Light(Vect3D, Vect3D);

  Vect3D getPosition() { return position;}
  Vect3D getColor() { return color;}

};

Light::Light() {
  position = Vect3D(0,0,0);
  color = Vect3D(1,1,1);
}

Light::Light(Vect3D p, Vect3D c) {
  position = p;
  color = c;
}

#endif
