#include "Sphere.hpp"
using namespace Eigen;

void Sphere::calct(Ray r) {
	double A, B, C, D;
	A = pow(r.dir.norm(), 2);
	B = r.dir.dot(r.pos - this->center);
	C = pow((r.pos - this->center).norm(), 2) - pow(this->radius, 2);
	D = B * B - A * C;
	if (D < 0) {
		this->t = -1.0;
	}
	else {
		this->t = (-B - sqrt(D)) / A;
	}
}