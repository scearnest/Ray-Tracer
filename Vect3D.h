#ifndef _VECT3D_H
#define _VECT3D_H

#include  "math.h"
#include <algorithm>

class Vect3D {
  double x, y, z;

public:
  Vect3D();
  Vect3D(double, double, double);

  double getVect3DX() { return x; }
  double getVect3DY() { return y; }
  double getVect3DZ() { return z; }


  Vect3D norm() {
    double mag = sqrt((x*x) + (y*y) + (z*z));
    return Vect3D (x/mag, y/mag, z/mag);
  }

  Vect3D invert () {
    double q = 0;
    double r = 0;
    double s = 0;
    if(x != 0) {q = -x;}
    if(y != 0) {r = -y;}
    if(z != 0) {s = -z;}
    return Vect3D(q,r,s);
  }

  void clamp(){
    if(x > 255) { x = 255; }
    if(y > 255) { y = 255; }
    if(z > 255) { z = 255; }
  }

  double dot(Vect3D v) {
    return((x*v.getVect3DX())+(y*v.getVect3DY())+(z*v.getVect3DZ()));
  }

  Vect3D cross(Vect3D v) {
    return Vect3D(y*v.getVect3DZ() - z*v.getVect3DY(),
                z*v.getVect3DX() - x*v.getVect3DZ(),
                x*v.getVect3DY() - y*v.getVect3DX());
  }

  Vect3D add(Vect3D v) {
    return Vect3D(x + v.getVect3DX(), y + v.getVect3DY(), z + v.getVect3DZ());
  }

  Vect3D sub(Vect3D v) {
    return Vect3D(x - v.getVect3DX(), y - v.getVect3DY(), z - v.getVect3DZ());
  }

  Vect3D mult(double s) {
    return Vect3D(x * s, y * s, z * s);
  }

  double length() {
    return sqrt(x*x + y*y + z*z);
  }

  void printValues() {
    std::cout << x << " " << y << " " << z << std::endl;
  }
};

Vect3D::Vect3D() {
  x = 1;
  y = 1;
  z = 1;
}

Vect3D::Vect3D(double i, double j, double k) {
  x = i;
  y = j;
  z = k;
}

#endif
