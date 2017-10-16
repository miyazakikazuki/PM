#ifndef RAYTRACING_HPP
#define RAYTRACING_HPP

#define EIGEN_NO_DEBUG
#define EIGEN_DONT_PARALLELIZE 
#define EIGEN_MPL2_ONLY 
#include <Eigen/Core>
#include "Material.hpp"
#include "Ray.hpp"
#include "Camera.hpp"
using namespace Eigen;

void RayTracing(Material m[4], Camera &c, int sampleN);
double CalcRadiance(Material mat, Vector3d hit);

#endif RAYTRACING_HPP
