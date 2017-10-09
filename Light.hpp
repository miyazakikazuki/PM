#ifndef CAMERA_HPP
#define CAMERA_HPP

#define EIGEN_NO_DEBUG // �R�[�h����assert�𖳌����D
#define EIGEN_DONT_PARALLELIZE // �����𖳌����D
#define EIGEN_MPL2_ONLY // LGPL���C�Z���X�̃R�[�h���g���Ȃ��D
#include <Eigen/Core>
#include "Ray.hpp"
#include "Plane.hpp"
using namespace Eigen;

struct Light {
	static int count;
	int index;//�}�e���A���ԍ�
	Plane emit, proj;
};
#endif CAMERA_HPP
