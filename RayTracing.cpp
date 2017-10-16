#include <iostream>
#include <random>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "RayTracing.hpp"
using namespace Eigen;

void RayTracing(Material m[4], Camera &c, int sampleN) {
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_real_distribution<double> rand(0.0, 1.0);
	double alpha = 1.0, t = 10000.0;
	int mattype = 0, matnum = 0;
	Vector3d x, wo, normal, wi;
	Ray r;
	int count = 0;
	for (int sample = 0; sample < sampleN; sample++) {
		for (int i = 0; i < c.eye.grid.rows(); i++, alpha = 1.0, t = 10000.0) {
			for (int j = 0; j < c.eye.grid.cols(); j++, alpha = 1.0, t = 10000.0) {
				r.pos = c.eye.pos - ((i + rand(mt)) / c.eye.grid.rows() - 0.5) * c.eye.area.x() * c.eye.tangent()
					+ ((j + rand(mt)) / c.eye.grid.cols() - 0.5) * c.eye.area.y() * c.eye.binormal();
				r.dir = (c.lens.pos - ((i + rand(mt)) / c.lens.grid.rows() - 0.5) * c.lens.area.x() * c.lens.tangent()
					+ ((j + rand(mt)) / c.lens.grid.cols() - 0.5) * c.lens.area.y() * c.lens.binormal() - r.pos).normalized();
				do {
					for (int k = 0; k < 4; k++) {
						if (m[k].t(r) > 0 && m[k].t(r) < t) {
							t = m[k].t(r);
							mattype = m[k].mattype;
							matnum = k;
						}
					}
					if (t <= 0.0 || t == 10000) {
						break;
					}
					x = r.pos + r.dir * t;
					wi = -r.dir;

					switch (mattype)
					{
					case 1:
						normal = m[matnum].normal;
						break;
					case 2:
						normal = (x - m[matnum].center).normalized();
						if (m[matnum].inmat) normal = -normal;
					default:
						break;
					}

					if (m[matnum].reftype == 1) {//diffuse
						wo << rand(mt), rand(mt), rand(mt);
						if (wo.dot(normal) < 0) {
							wo = -wo;
						}
					}
					else if (r.dir.dot(normal) < 0
						&& m[matnum].reftype == 2) { //refraction
						double a, b;
						Vector3d tmp;
						a = -sqrt(1 - (1 - pow(-r.dir.dot(normal), 2))
							/ pow(m[matnum].n, 2));
						b = 1 / m[matnum].n;
						tmp = a * normal + b * r.dir;
						if (m[matnum].inmat) {
							if (tmp.dot(normal) > 0) {
								wo << rand(mt), rand(mt), rand(mt);
								if (wo.dot(normal) < 0) {
									wo = -wo;
								}
							}
							else {
								wo = tmp;
								m[matnum].inmat = false;
							}
						}
						else {
							wo = tmp;
							m[matnum].inmat = true;
						}//end refraction
					}
					wo = wo.normalized();

					if (mattype == 1) {//Plane
						c.eye.grid(j, i) += CalcRadiance(m[matnum], x);
						break;
					}
					r.pos = x;
					r.dir = wo;
					t = 10000;
				} while (true);
			}
		}
		std::cout << "Loading..." << (double)sample / (double) sampleN * 100.0 << "%" << std::endl;
	}
	c.eye.grid = c.eye.grid / (double) sampleN;
}

double CalcRadiance(Material mat, Vector3d hit) {
	int n, m;
	Vector3d u, v, x0;
	double det;
	u = mat.area.x() / mat.grid.cols() * mat.tangent();
	v = -mat.area.y() / mat.grid.rows() * mat.binormal();
	det = u.x() * v.z() - u.z() * v.x();
	x0 = mat.pos - mat.area.x() / 2.0 * mat.tangent()
		+ mat.area.y() / 2.0 * mat.binormal();
	n = (v.z() * (hit.x() - x0.x()) - v.x() * (hit.z() - x0.z())) / det;
	m = (-u.z() * (hit.x() - x0.x()) + u.x() * (hit.z() - x0.z())) / det;
	return mat.grid(n, m);
}