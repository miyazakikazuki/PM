#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#define EIGEN_NO_DEBUG
#define EIGEN_DONT_PARALLELIZE 
#define EIGEN_MPL2_ONLY 
#include <Eigen/Core>
#include<Eigen/Geometry>
#include "Ray.hpp"
using namespace Eigen;

struct Material {
	static int count;
	int index;
	int mattype = 0;
	int reftype = 0;
	double t(Ray r);
	MatrixXd grid = MatrixXd::Zero(500, 500);
	//for plane
	Vector3d normal;
	Vector3d pos;
	Vector2d area;
	Vector3d tangent();
	Vector3d binormal();
	//for sphere
	Vector3d center;
	double radius;
};
#endif MATERIAL_HPP
