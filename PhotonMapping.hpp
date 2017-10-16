#ifndef PHOTONMAPPING_HPP
#define PHOTONMAPPING_HPP

#define EIGEN_NO_DEBUG
#define EIGEN_DONT_PARALLELIZE 
#define EIGEN_MPL2_ONLY 
#include <Eigen/Core>
#include "Material.hpp"
#include "Ray.hpp"
#include "Light.hpp"
using namespace Eigen;

void PhotonTracing(Material (&m)[4], Light l, int sampleN);
void PhotonMapping(Material &mat, Vector3d hit, double alpha);

#endif PHOTONMAPPING_HPP
