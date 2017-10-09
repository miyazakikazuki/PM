#include <iostream>
#include <random>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "Plane.hpp"
#include "Sphere.hpp"
#include "Ray.hpp"
using namespace Eigen;

MatrixXd PhotonTracing(int N, Material[] m, Light l){
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_real_distribution<double> point(0.0, 1.0);

	Ray photon;
	photon.pos = l.pos + ;
	photon.dir = l.normal;
	for (int i = 0; i < N; i++) {
	}
}
