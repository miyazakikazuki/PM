#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#define EIGEN_NO_DEBUG // �R�[�h����assert�𖳌����D
#define EIGEN_DONT_PARALLELIZE // ����𖳌����D
#define EIGEN_MPL2_ONLY // LGPL���C�Z���X�̃R�[�h���g��Ȃ��D
#include <Eigen/Core>
#include "Ray.hpp"
using namespace Eigen;

struct Material {
	static int count;
	int index;//�}�e���A���ԍ�
	int type;//�}�e���A���̎��
	double t;
	Material();
	void calct(Ray r);
};
#endif MATERIAL_HPP