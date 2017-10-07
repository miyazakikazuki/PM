#ifndef RAY_HPP
#define RAY_HPP

#define EIGEN_NO_DEBUG 
#define EIGEN_DONT_PARALLELIZE 
#define EIGEN_MPL2_ONLY 
#define PI 3.141592653589793;

#include <iostream>
#include "Eigen/Core"
using namespace Eigen;

struct Ray {
	Vector3d pos;
	Vector3d dir;
	int count = 0;
	int index;
	Ray(Vector3d p, Vector3d d);
};
#endif RAY_HPP
