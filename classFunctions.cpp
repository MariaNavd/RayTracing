#include "rayTracing.h"

vector3d::vector3d() {
	x = 0;
	y = 0;
	z = 0;
}
vector3d::vector3d(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
vector3d vector3d ::operator+(const vector3d& vec) {
	return vector3d(x + vec.x, y + vec.y, z + vec.z);
}
vector3d vector3d ::operator-(const vector3d& vec) {
	return vector3d(x - vec.x, y - vec.y, z - vec.z);
}
vector3d& vector3d::operator-=(const vector3d& vec) {
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}
vector3d vector3d ::operator*(double value) {
	return vector3d(x * value, y * value, z * value);
}
double vector3d ::operator*(vector3d vec) {
	return x * vec.x + y * vec.y + z * vec.z;
}
vector3d& vector3d::operator*=(double value) {
	x *= value;
	y *= value;
	z *= value;
	return *this;
}
vector3d& vector3d ::operator/=(double value) {
	assert(value != 0);
	x /= value;
	y /= value;
	z /= value;
	return *this;
}
double vector3d::square() {
	return x * x + y * y + z * z;
}
double vector3d::magnitude() {
	return sqrt(square());
}
vector3d vector3d::normalization() {
	assert(magnitude() != 0);
	*this /= magnitude();
	return *this;
}
double vector3d::distance(vector3d& vec) {
	vector3d dist = *this - vec;
	return dist.magnitude();
}
double vector3d::showX() const {
	return x;
}
double vector3d::showY() const {
	return y;
}
double vector3d::showZ() const {
	return z;
}

Sphere::Sphere(const vector3d& center, const double radius, const vector3d& color, const double diffuse) {
	this->center = center;
	this->radius = radius;
	this->color = color;
	this->diffuse = diffuse;
}
double Sphere::distance(vector3d& point) {
	return point.distance(center);
}
vector3d Sphere::showCenter() const {
	return center;
}
vector3d Sphere::showColor() const {
	return color;
}
double Sphere::showR() const {
	return radius;
}
double Sphere::showDiffuse() const {
	return diffuse;
}
vector3d Sphere::point(vector3d& cCent, vector3d& dist, vector3d& dir, double fi) {
	double length = dist.magnitude() * cos(fi) + sqrt(dist.square() * (pow(cos(fi), 2) - 1) + pow(radius, 2));
	vector3d point = dir.normalization() * length + cCent;
	return point;
}

Light::Light(const vector3d& center, double intensity) {
	this->center = center;
	this->intensity = intensity;
}
vector3d Light::showCenter() const {
	return center;
}
double Light::showIntensity() const {
	return intensity;
}

Camera::Camera(const vector3d& center, double fov) {
	this->center = center;
	this->fov = fov;
}
vector3d Camera::showCenter() const {
	return center;
}
double Camera::showFov() const {
	return fov;
}