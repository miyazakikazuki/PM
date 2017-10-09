#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#define EIGEN_NO_DEBUG // �R�[�h����assert�𖳌����D
#define EIGEN_DONT_PARALLELIZE // �����𖳌����D
#define EIGEN_MPL2_ONLY // LGPL���C�Z���X�̃R�[�h���g���Ȃ��D
#include <Eigen/Core>

#include <iostream>
#include <random>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "Plane.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
#include "Light.hpp"
#include "Camera.hpp"
using namespace Eigen;

int main() {
	Camera c;
	Light l;
	Plane f;
	Sphere u;
	Material m[3];
	c.eye.pos << 0.0, 1.0, 5.0;
	c.eye.normal << 0.0, 0.0, -1.0;
	c.eye.area << 0.1, 0.1;
	c.lens.pos << 0.0, 1.0, 3.0;
	c.lens.normal << 0.0, 0.0, -1.0;
	c.lens.area << 1.0, 1.0;

	l.emit.pos << 4.0, 4.0, 1.0;
	l.emit.normal = -l.emit.pos.normalized();
	l.emit.area << 1.0, 1.0;
	l.proj.pos << 3.0, 3.0, 0.75;
	l.proj.normal << -l.proj.pos.normalized();
	l.proj.area << 1.0, 1.0;

	f.pos << 0.0, 0.0, 0.0;
	f.normal << 0.0, 1.0, 0.0;
	f.area << 5.0, 5.0;
	u.center << 0.0, 1.0, 0.0;
	u.radius = 1.0;

	m[0] = f;
	m[1] = u;
	MatrixXd input = MatrixXd::Zero(200, 200);



	double* data = new double[input.cols()*input.rows()];
	cv::Mat img(input.cols(), input.rows(), CV_64FC1, data);
	for (int i = 0; i < input.rows(); i++) {
		for (int j = 0; j < input.cols(); j++) {
			data[i * input.cols() + j] = input(input.cols() - i - 1, input.rows() - j - 1);
		}
	}
	cv::namedWindow("image", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
	cv::imshow("image", img);
	cv::waitKey(0);
}
