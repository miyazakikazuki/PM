#ifndef PLANE_HPP
#define PLANE_HPP
#include"Material.hpp"
#include"Ray.hpp"
using namespace Eigen;

struct Plane : public Material {
	Vector3d point;
	Vector3d normal;
	Vector2d area;
	Plane(Vector3d p, Vector3d n, Vector2d a);
	void calct(Ray r);
};
#endif PLANE_HPP
