#ifndef PLANE_HPP
#define PLANE_HPP
#include"Material.hpp"
#include"Ray.hpp"
using namespace Eigen;

struct Plane : public Material {
	Vector3d pos;
	Vector3d normal;
	Vector2d area;
	int type = 1;
	void calct(Ray r);
};
#endif PLANE_HPP
