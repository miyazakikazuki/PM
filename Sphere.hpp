#ifndef SPHERE_HPP
#define SPHERE_HPP
#include"Material.hpp"
#include"Ray.hpp"
using namespace Eigen;

struct Sphere : public Material {
	Vector3d center;
	double radius;
	Sphere(Vector3d c, double r);
	void calct(Ray r);
};
#endif SPHERE_HPP
