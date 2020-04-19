#include <cassert>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>

const double M_PI = 3.14159265358979323846;

class vector3d {
private:
	double x, y, z;
public:
	vector3d();
	vector3d(double x, double y, double z);
	vector3d operator+(const vector3d& vec);
	vector3d operator-(const vector3d& vec);
	vector3d& operator-=(const vector3d& vec);
	vector3d operator*(double value);
	double operator*(vector3d vec);
	vector3d& operator*=(double value);
	vector3d& operator/=(double value);
	double magnitude();
	vector3d normalization();
	double square();
	double distance(vector3d& vec);
	double showX() const;
	double showY() const;
	double showZ() const;
};

class Sphere {
private:
	vector3d center, color;
	double radius, diffuse;
public:
	Sphere(const vector3d& center, const double radius, const vector3d& color, const double duffuse);
	~Sphere() {};
	vector3d showCenter() const;
	vector3d showColor() const;
	double showR() const;
	double showDiffuse() const;
	double distance(vector3d& point);
	vector3d point(vector3d& cCent, vector3d& dist, vector3d& dir, double fi);
};

class Light {
private:
	vector3d center;
	double intensity;
public:
	Light(const vector3d& center, double intensity);
	~Light() {};
	vector3d showCenter() const;
	double showIntensity() const;
};

class Camera {
private:
	vector3d center;
	double fov;
public:
	Camera(const vector3d& center, double fov);
	~Camera() {};
	vector3d showCenter() const;
	double showFov() const;
};

class DrawPicture {
public:
	void draw(const vector3d& background, std::vector<Sphere>& spheres, Light& light, Camera& cam);
	double reflection(vector3d& pnt, vector3d& cCent, vector3d& norm, vector3d& ray, Sphere& sphere, double coef);
	void illumination(vector3d& pnt, vector3d& pix, Light& light, Sphere& sphere, vector3d& cCent);
};