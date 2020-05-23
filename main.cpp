#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Vect3D.h"
#include "Ray.h"
#include "Light.h"
#include "Object.h"
#include "Sphere.h"
#include "Polygon.h"



Vect3D ambient(0.1,0.1,0.1);


Vect3D computeLighting(Vect3D P, Vect3D N, Vect3D V, Vect3D matDiff, Vect3D specHL, int phong_C, Light light)
{
  Vect3D l = light.getPosition().norm();
  Vect3D finalColor(0,0,0);

  //Diffuse
  Vect3D Diffuse(0,0,0);
  double n_dot_l = N.dot(l);
  if(n_dot_l > 0) { Diffuse = matDiff.mult(n_dot_l/(N.length() * l.length()));}
  finalColor = finalColor.add(Diffuse);

  //Specular
  Vect3D Specular(0,0,0);
  Vect3D LightColor(1,1,1);
  Vect3D R = (N.mult(2 * N.dot(l))).sub(l).norm();
  double r_dot_v = R.dot(V.norm());
  if(r_dot_v > 0) {
    Specular = LightColor.mult(pow(r_dot_v/(R.length() * V.length()), phong_C));
  }
  finalColor = finalColor.add(Specular);

  //Ambient
  finalColor = finalColor.add(ambient);


  finalColor = finalColor.mult(255);
  finalColor.clamp();
  return finalColor;
}

bool checkShadow(Vect3D P, Vect3D L, vector<Object *> scene, int index) {
  Ray r = Ray(P, L);
  double t = 0;
  for(int i = 0; i < scene.size(); ++i)
  {
    if(scene[i]->findIntersection(r, t) && i!=index)
    { return true; }
  }
  return false;
}


Vect3D TraceRay(Vect3D lookFrom, Vect3D direction, int depth, vector<Object *> scene, Light light) {

  Ray primary(lookFrom, direction);

  bool hit = false;
  double t_min = 1000.0;
  int index = 0;
  double t = 0.0;

  for(unsigned int k = 0; k < scene.size(); ++ k)
  {
    if(scene[k]->findIntersection(primary, t))
    {
      hit = true;
      if(t<t_min) { index = k; t_min = t;}
    }
  }

  if(hit) {
    Vect3D p = lookFrom.add(primary.getDirection().mult(t_min));
    Vect3D p_e = lookFrom.add(primary.getDirection().mult(t_min + 0.000001));
    Vect3D n = scene[index]->getNormal();
    //Check Shadow
    if(!checkShadow(p_e, light.getPosition(), scene, index)) {
      Vect3D color = computeLighting(p, n, primary.getDirection().invert(), scene[index]->getMatDiff(), scene[index]->getSpecHighLight(), scene[index]->getPhongConstant(), light);
      //Check for reflections
      if(scene[index]->getReflectivity() > 0 && depth > 0)
      {
        Vect3D R = (n.mult(2).mult(n.dot(direction.invert()))).add(direction);
        Vect3D refelectedColor = TraceRay(p_e, R, depth - 1, scene, light);
        color = (color.mult(1-scene[index]->getReflectivity())).add(refelectedColor.mult(scene[index]->getReflectivity()));
      }
      return color;
    }
    //in shadow
    else { return Vect3D(0,0,0); }
  }
  else {return Vect3D(0.2*255,0.2*255,0.2*255);}
}



using namespace std;

int main (int argc, char *argv[]){

  cout << "rendering...." << endl;

  Vect3D black (0.0,0.0,0.0);
  Vect3D yellow(1.0,1.0,0.0);
  Vect3D blue(0.0,0.0,1.0);
  Vect3D white(1,1,1);



  // //Diffuse Scene
  // Vect3D lookFrom(0,0,1);
  // Vect3D lookAt(0,0,0);
  // double img_plane_width = 0;
  // double img_plane_height = 0;
  // double field_of_view = 28;
  // double focal_length = lookFrom.getVect3DZ();
  //
  // Light light(Vect3D(1,0,0), Vect3D(1,1,1));
  // vector<Object *> scene;
  //
  // scene.push_back(new Sphere(Vect3D(0.35,0,-0.1), 0.05, Vect3D(1,1,1), Vect3D(1,1,1), 4, 0.0));
  // scene.push_back(new Sphere(Vect3D(0.2,0,-0.1), 0.075, Vect3D(1,0,0), Vect3D(0.5,1,0.5),32, 0.0));
  // scene.push_back(new Sphere(Vect3D(-0.6,0,0), 0.3, Vect3D(0,1,0),Vect3D(0.5,1,0.5),32, 0.0));
  //
  // vector<Vect3D> tri_points_1;
  // tri_points_1.push_back(Vect3D(0.3,-0.3,-0.4));
  // tri_points_1.push_back(Vect3D(0.0,0.3,-0.1));
  // tri_points_1.push_back(Vect3D(-0.3,-0.3,0.2));
  // scene.push_back(new Polygon(tri_points_1, Vect3D(0,0,1), Vect3D(1,1,1), 32, 0));
  //
  // vector<Vect3D> tri_points_2;
  // tri_points_2.push_back(Vect3D(-0.2,0.1,0.1));
  // tri_points_2.push_back(Vect3D(-0.2,-0.5,0.2));
  // tri_points_2.push_back(Vect3D(-0.2,0.1,-0.3));
  // scene.push_back(new Polygon(tri_points_2, Vect3D(1,1,0), Vect3D(1,1,1), 4, 0));



  // //Scenell Scene
  // Light light(Vect3D(0,1,0), Vect3D(1,1,1));
  //
  // vector<Object *> scene;
  // scene.push_back(new Sphere(Vect3D(0.0,0.3,0.0), 0.2, black, black, 3200, 0.75));
  //
  // vector<Vect3D> tri_points_2;
  // tri_points_2.push_back(Vect3D(0.0,-0.5,0.5));
  // tri_points_2.push_back(Vect3D(1.0,0.5,0.0));
  // tri_points_2.push_back(Vect3D(0.0,-0.5,-0.5));
  // scene.push_back(new Polygon(tri_points_2, blue, white, 4, 0));
  //
  // vector<Vect3D> tri_points_3;
  // tri_points_3.push_back(Vect3D(0.0,-0.5,0.5));
  // tri_points_3.push_back(Vect3D(0.0,-0.5,-0.5));
  // tri_points_3.push_back(Vect3D(-1.0,0.5,0.0));
  // scene.push_back(new Polygon(tri_points_3, yellow, white, 4, 0));
  //
  // Vect3D lookFrom(0,0,1.2);
  // Vect3D lookAt(0,0,0);
  // double img_plane_width = 0;
  // double img_plane_height = 0;
  // double field_of_view = 55;
  // double focal_length = lookFrom.getVect3DZ();



  // //Personal Scene
  // Light light(Vect3D(0.5,1,0.5).norm(), Vect3D(1,1,1));
  //
  // vector<Object *> scene;
  // scene.push_back(new Sphere(Vect3D(0.0,0.2,-0.3), 0.3, Vect3D(0,1,1), white, 32, 0.25));
  // scene.push_back(new Sphere(Vect3D(-0.3,-0.1,0.5), 0.2, Vect3D(1,0,0), white, 16, 0.5));
  // scene.push_back(new Sphere(Vect3D(0.3,-0.1,0.5), 0.2, Vect3D(1,0,1), white, 4, 0.5));
  //
  // vector<Vect3D> tri_points_2;
  // tri_points_2.push_back(Vect3D(4.0,-0.2,1.0));
  // tri_points_2.push_back(Vect3D(0.0,-0.2,-5.0));
  // tri_points_2.push_back(Vect3D(0.0,-0.2,1.0));
  // scene.push_back(new Polygon(tri_points_2, Vect3D(1,0.8,0), white, 4, 0.25));
  //
  // vector<Vect3D> tri_points_3;
  // tri_points_3.push_back(Vect3D(0.0,-0.2,1.0));
  // tri_points_3.push_back(Vect3D(0.0,-0.2,-5.0));
  // tri_points_3.push_back(Vect3D(-4.0,-0.2,1.0));
  // scene.push_back(new Polygon(tri_points_3, Vect3D(0.5,1,0.5), white, 4, 0.25));
  //
  // vector<Vect3D> tri_points_4;
  // tri_points_4.push_back(Vect3D(-4.0,3,1.0));
  // tri_points_4.push_back(Vect3D(-4.0,-0.2,1.0));
  // tri_points_4.push_back(Vect3D(0.0,-0.2,-5.0));
  // scene.push_back(new Polygon(tri_points_4, Vect3D(0,0,1), white, 4, 0.25));
  //
  // vector<Vect3D> tri_points_5;
  // tri_points_5.push_back(Vect3D(4.0,-0.2,1.0));
  // tri_points_5.push_back(Vect3D(4.0,3,1.0));
  // tri_points_5.push_back(Vect3D(0.0,-0.2,-5.0));
  // scene.push_back(new Polygon(tri_points_5, Vect3D(0,1,0), white, 4, 0.25));
  //
  // Vect3D lookFrom(0,0,1);
  // Vect3D lookAt(0,0,0);
  // double img_plane_width = 0;
  // double img_plane_height = 0;
  // double field_of_view = 34;
  // double focal_length = lookFrom.getVect3DZ();


  img_plane_width = tan(field_of_view * M_PI / 180) * focal_length;
  img_plane_height = img_plane_width;

  double canvas_width = 500;
  double canvas_height = 500;

  double pixel_size = 2 * img_plane_width/canvas_width;

  //Set Up ppm
  ofstream img("file.ppm");

  img << "P3" << endl;
  img << canvas_width << " " << canvas_height << endl;
  img << "255" << endl;

  for(double j = 0; j < canvas_height; j++)
  {
    for(double i = 0; i < canvas_width; i++)
    {
      double x_pos = (-img_plane_width) + (0.5*pixel_size) + i*pixel_size;
      double y_pos = (img_plane_height) - (0.5*pixel_size) - j*pixel_size;
      Vect3D point(x_pos, y_pos, 0);
      Vect3D direction = (point.sub(lookFrom)).norm();

      Vect3D color = TraceRay(lookFrom, direction, 3, scene, light);
      img << (int)color.getVect3DX() << " " << (int)color.getVect3DY() << " " << (int)color.getVect3DZ() << " ";
    }
  }

  cout << "DONE" << endl;

  return 0;
}
