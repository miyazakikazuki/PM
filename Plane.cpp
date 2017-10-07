#include "Plane.hpp"
using namespace Eigen;

void Plane::calct(Ray r) {
	this->t = (this->point - r.pos).dot(this->normal) / r.dir.dot(this->normal);
}