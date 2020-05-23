#ifndef _POLYGON_H
#define _POLYGON_H

#include "math.h"
#include "Object.h"
#include "Vect3D.h"
#include <vector>

using namespace std;

class Polygon : public Object {
  vector<Vect3D> points;


public:
  Polygon();
  Polygon(vector<Vect3D>, Vect3D, Vect3D, int, double);

  bool findIntersection(Ray ray, double &t);
};

Polygon::Polygon() {
  normal = Vect3D(0,1,0);
}

Polygon::Polygon(vector<Vect3D> p, Vect3D md, Vect3D sh, int pc, double r) {
  points = p;
  matDiff = md;
  specHighLight = sh;
  phongConstant = pc;
  normal = (points[1].sub(points[0]).cross(points[2].sub(points[1]))).norm();
  reflectivity = r;
}

bool Polygon::findIntersection(Ray ray, double &t) {

  Vect3D orig = ray.getOrigin();
  Vect3D dir = ray.getDirection().norm();

  double v_d = normal.dot(dir);
  //Check parallel or close to parallel
  if(abs(v_d) < 0.001) { return false;}
  
  double d = -(normal.getVect3DX() * points[0].getVect3DX() + normal.getVect3DY() * points[0].getVect3DY() + normal.getVect3DZ() * points[0].getVect3DZ());

  double v_o = -((normal.dot(orig)) + d);
  t = v_o/v_d;

  //Check if poly is behind
  if(t < 0) { return false; }
  if(v_d > 0) { normal = normal.invert();}

  //intersection point defined
  Vect3D P = orig.add(dir.mult(t));
  Vect3D C(0,0,0);

  //edge 0
  Vect3D edge0 = points[1].sub(points[0]);
  Vect3D vp0 = P.sub(points[0]);
  C = edge0.cross(vp0);
  if(normal.dot(C) < 0) { return false; }

  //edge 1
  Vect3D edge1 = points[2].sub(points[1]);
  Vect3D vp1 = P.sub(points[1]);
  C = edge1.cross(vp1);
  if(normal.dot(C) < 0) { return false; }

  //edge 2
  Vect3D edge2 = points[0].sub(points[2]);
  Vect3D vp2 = P.sub(points[2]);
  C = edge2.cross(vp2);
  if(normal.dot(C) < 0) { return false; }


  return true;
}

#endif
