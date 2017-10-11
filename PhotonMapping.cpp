#include <iostream>
#include <random>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "PhotonMapping.hpp"
using namespace Eigen;

void PhotonTracing(Material (&m)[2], Light l, int sampleN) {
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_real_distribution<double> rand(0.0, 1.0);
	double alpha = 1.0, t = 10000.0;
	int mattype = 0, matnum = 0;
	Vector3d x, wo, normal, wi;
	Ray photon;
	int count = 0;
	for (int i = 0; i < sampleN; i++, alpha = 1.0, t = 10000.0) {
		photon.pos = l.emit.pos + (rand(mt) - 0.5) * l.emit.area.x() * l.emit.tangent()
			+ (rand(mt) - 0.5) * l.emit.area.y() * l.emit.binormal();
		photon.dir = (l.proj.pos + (rand(mt) - 0.5) * l.proj.area.x() * l.proj.tangent()
			+ (rand(mt) - 0.5) * l.proj.area.y() * l.proj.binormal() - photon.pos).normalized();
		do{
			for (int j = 0; j < 2; j++) {
				if ((1.0 / m[j].t(photon)) > (1.0 / t)) {
					t = m[j].t(photon);
					mattype = m[j].mattype;
					matnum = j;
				}
			}
			if (t <= 0.0 || t == 10000) {
				break;
			}
			x = photon.pos + photon.dir * t;
			wi = - photon.dir;
			
			switch (mattype)
			{
			case 1:
				normal = m[matnum].normal;
				break;
			case 2:
				normal = (x - m[matnum].center).normalized();
			default:
				break;
			}

			wo << rand(mt), rand(mt), rand(mt);
			if (wo.dot(normal) < 0 && m[matnum].reftype == 1) {
				wo = - wo;
			}
			wo = wo.normalized();
			double prr = 0.5;

			if (rand(mt) > prr) {
				if (mattype == 1) {
					PhotonMapping(m[matnum], x, alpha);
				}
				break;
			}
			photon.pos = x;
			photon.dir = wo;

			alpha = alpha / prr;
		} while (true);
	}
}

void PhotonMapping(Material &mat, Vector3d hit, double alpha) {
	int n, m;
	Vector3d u, v, x0;
	double det;
	u = mat.area.x() / mat.grid.rows() * mat.tangent();
	v = mat.area.y() / mat.grid.cols() * mat.binormal();
	det = u.x() * v.z() - u.z() * v.x();
	x0 = mat.pos - mat.area.x() / 2.0 * mat.tangent()
				 - mat.area.y() / 2.0 * mat.binormal();
	n = (v.z() * (hit.x() - x0.x()) - v.x() * (hit.z() - x0.z())) / det;
	m = (-u.z() * (hit.x() - x0.x()) + u.x() * (hit.z() - x0.z())) / det;
	mat.grid(n,m) = mat.grid(n,m) + alpha;
}