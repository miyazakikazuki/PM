#ifndef LIGHT_HPP
#define LIGHT_HPP

#define EIGEN_NO_DEBUG 
#define EIGEN_DONT_PARALLELIZE 
#define EIGEN_MPL2_ONLY 
#include <Eigen/Core>
#include "Ray.hpp"
#include "Material.hpp"
using namespace Eigen;

struct Light{
	static int count;
	int index;
	Material emit, proj;
};
#endif LIGHT_HPP
