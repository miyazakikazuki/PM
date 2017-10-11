#ifndef CAMERA_HPP
#define CAMERA_HPP

#define EIGEN_NO_DEBUG 
#define EIGEN_DONT_PARALLELIZE 
#define EIGEN_MPL2_ONLY 
#include <Eigen/Core>
#include "Ray.hpp"

using namespace Eigen;

struct Camera {
	static int count;
	int index;
	Material eye, lens;
};
#endif CAMERA_HPP
