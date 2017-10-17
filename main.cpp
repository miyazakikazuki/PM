#define EIGEN_NO_DEBUG 
#define EIGEN_DONT_PARALLELIZE 
#define EIGEN_MPL2_ONLY 
#include <Eigen/Core>

#include <iostream>
#include <random>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "Material.hpp"
#include "Ray.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include "PhotonMapping.hpp"
#include "RayTracing.hpp"
using namespace Eigen;

int main() {
	Camera c;
	Light l;
	Material m[4], fb, fw1, fw2, u;
	c.eye.pos << 8.0, 8.0, 8.0;
	c.eye.normal = - c.eye.pos.normalized();
	c.eye.area << 0.1, 0.1;
	c.eye.mattype = 1;
	c.lens.pos << 7.0, 7.0, 7.0;
	c.lens.normal = - c.lens.pos.normalized();
	c.lens.area << 1.0, 1.0;
	c.lens.mattype = 1;

	l.emit.pos << 0.0, 5.0, -5.0;
	l.emit.normal = -l.emit.pos.normalized();
	l.emit.area << 0.1, 0.1;
	l.emit.mattype = 1;
	l.proj.pos << 0.0, 4.0, -4.0;
	l.proj.normal << -l.proj.pos.normalized();
	l.proj.area << 1.0, 1.0;
	l.proj.mattype = 1;

	fb.pos << 0.0, -1.0, 0.0;
	fb.normal = -fb.pos.normalized();
	fb.area << 4.0, 4.0;
	fb.mattype = 1;
	fb.reftype = 1;
	fb.grid = MatrixXd::Zero(500, 500);

	fw1.pos << -2.0, 0.0, 0.0;
	fw1.normal = - fw1.pos.normalized();
	fw1.area << 4.0, 4.0;
	fw1.mattype = 1;
	fw1.reftype = 1;
	fw1.grid = MatrixXd::Zero(500, 500);

	fw2.pos << 0.0, 0.0, -2.0;
	fw2.normal = - fw2.pos.normalized();
	fw2.area << 4.0, 4.0;
	fw2.mattype = 1;
	fw2.reftype = 1;
	fw2.grid = MatrixXd::Zero(500, 500);
	


	u.center << 0.0, 0.0, 0.0;
	u.radius = 1.0;
	u.reftype = 2;
	u.mattype = 2;
	u.n = 1.4;

	m[0] = u;
	m[1] = fb;
	//m[2] = fw1;
	//m[3] = fw2;
	PhotonTracing(m, l, 5000000);
	m[1].grid = m[1].grid / 16.0;
	//m[2].grid = m[2].grid / 16.0;
	//m[3].grid = m[3].grid / 16.0;
	RayTracing(m, c, 1);

	double* data = new double[c.eye.grid.cols() * c.eye.grid.rows()];
	cv::Mat img(c.eye.grid.cols(), c.eye.grid.rows(), CV_64FC1, data);
	for (int i = 0; i < c.eye.grid.rows(); i++) {
		for (int j = 0; j < c.eye.grid.cols(); j++) {
			data[i * c.eye.grid.cols() + j] = c.eye.grid(j,i);
		}
	}
	cv::namedWindow("image", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
	cv::imshow("image", img);
	cv::waitKey(0);
}
