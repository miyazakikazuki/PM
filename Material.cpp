#include "Material.hpp"
using namespace Eigen;

int Material::count;

double Material::t(Ray r) {
	if (this->mattype == 1) {
		double n, m;
		double det;
		Vector3d u, v, pos;
		pos = r.pos + (this->pos - r.pos).dot(this->normal) / r.dir.dot(this->normal) * r.dir;
		u = this->area.x() / 2.0 * this->tangent();
		v = this->area.y() / 2.0 * this->binormal();
		det = u.x() * v.z() - u.z() * v.x();
		n = (v.z() * (pos.x() - this->pos.x())
			- v.x() * (pos.z() - this->pos.z())) / det;
		m = (-u.z() * (pos.x() - this->pos.x())
			+ u.x() * (pos.z() - this->pos.z())) / det;
		if (abs(n) < 1.0 && abs(m) < 1.0) {
			return (this->pos - r.pos).dot(this->normal) / r.dir.dot(this->normal);
		}else {
			return -1.0;
		}
	}else if (this->mattype == 2) {
		double A, B, C, D;
		A = pow(r.dir.norm(), 2);
		B = r.dir.dot(r.pos - this->center);
		C = pow((r.pos - this->center).norm(), 2) - pow(this->radius, 2);
		D = B * B - A * C;
		if (D < 0) {
			return -1.0;
		}else {
			return (- B - sqrt(D)) / A;
		}
	}else {
		return 0.0;
	}
}

Vector3d Material::tangent() {
	Vector3d result;
	if (this->normal.x() == 0 && this->normal.z() == 0) {
		result << 1.0, 0.0, 0.0;
	}else {
		result.x() = this->normal.z() / sqrt(this->normal.x() * this->normal.x() + this->normal.z() * this->normal.z());
		result.y() = 0;
		result.z() = this->normal.x() / sqrt(this->normal.x() * this->normal.x() + this->normal.z() * this->normal.z());
	}
	return result.normalized();
}
Vector3d Material::binormal() {
	return this->normal.cross(this->tangent());
}

