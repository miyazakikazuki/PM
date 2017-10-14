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
using namespace Eigen;

int main() {
	Camera c;
	Light l;
	Material m[2], f, u;
	c.eye.pos << 0.0, 1.0, 5.0;
	c.eye.normal << 0.0, 0.0, -1.0;
	c.eye.area << 0.1, 0.1;
	c.eye.mattype = 1;
	c.lens.pos << 0.0, 1.0, 3.0;
	c.lens.normal << 0.0, 0.0, -1.0;
	c.lens.area << 1.0, 1.0;
	c.lens.mattype = 1;

	l.emit.pos << 0.0, 10.0, 10.0;
	l.emit.normal = -l.emit.pos.normalized();
	l.emit.area << 0.1, 0.1;
	l.emit.mattype = 1;
	l.proj.pos << 0.0, 9.0, 9.0;
	l.proj.normal << -l.proj.pos.normalized();
	l.proj.area << 1.0, 1.0;
	l.proj.mattype = 1;

	f.pos << 0.0, 0.0, 0.0;
	f.normal << 0.0, 1.0, 0.0;
	f.area << 5.0, 5.0;
	f.mattype = 1;
	f.reftype = 1;
	u.center << 0.0, 1.0, 0.0;
	u.radius = 1.0;
	u.reftype = 1;
	u.mattype = 2;

	m[0] = u;
	m[1] = f;
	PhotonTracing(m, l, 10000000);
	f.grid = m[1].grid;
	f.grid = f.grid / 4.0;
	

	double* data = new double[f.grid.cols() * f.grid.rows()];
	cv::Mat img(f.grid.cols(), f.grid.rows(), CV_64FC1, data);
	for (int i = 0; i < f.grid.rows(); i++) {
		for (int j = 0; j < f.grid.cols(); j++) {
			data[i * f.grid.cols() + j] =f.grid(i,j);
		}
	}
	cv::namedWindow("image", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
	cv::imshow("image", img);
	cv::waitKey(0);
}
