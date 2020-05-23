#ifndef _RAY_H
#define _RAY_H

#include  "Vect3D.h"

class Ray {
  Vect3D origin, direction;

public:
  Ray();
  Ray(Vect3D, Vect3D);

  Vect3D getOrigin() { return origin;}
  Vect3D getDirection() { return direction;}
  Vect3D getPrimary() { return origin.add(direction.sub(origin)).norm();}

};

Ray::Ray() {
  origin = Vect3D(0,0,0);
  direction = Vect3D(1,0,0);
}

Ray::Ray(Vect3D o, Vect3D d) {
  origin = o;
  direction = d;
}

#endif
