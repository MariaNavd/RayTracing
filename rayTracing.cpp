#include "rayTracing.h"

double DrawPicture::reflection(vector3d& pnt, vector3d& cCent, vector3d& norm, vector3d& ray, Sphere& sphere, double coef) {
	ray *= -1;
	vector3d reflRay = (norm * 2 * (ray * norm) - ray).normalization();
	vector3d vision = (cCent - pnt).normalization();
	double reflCoef = ((reflRay * vision) / 2 + 1) * sphere.showDiffuse() * pow(coef, 2);
	return reflCoef;
}

void DrawPicture::illumination(vector3d& pnt, vector3d& pix, Light& light, Sphere& sphere, vector3d& cCent) {
	vector3d ray = (pnt - light.showCenter()).normalization(), norm = (pnt - sphere.showCenter()).normalization();
	double coef = (light.showCenter() - pnt).magnitude() / ((light.showCenter() - sphere.showCenter()).magnitude() + sphere.showR());
	double pointIllum = light.showIntensity() * ((norm * ray) / 2 + 1) * pow(coef, 2);
	pix *= pointIllum * reflection(pnt, cCent, norm, ray, sphere, coef);
}

void DrawPicture::draw(const vector3d& background, std::vector<Sphere>& spheres, Light& light, Camera& cam) {
	int height = 780, width = 1080;
	std::vector<vector3d> pixels(height * width);
	for (size_t j = 0; j < height; j++) {
		for (size_t i = 0; i < width; i++) {
			pixels[i + j * width] = background;
		}
	}

	vector3d cCent = cam.showCenter();
	for (size_t j = 0; j < height; j++) {
		for (size_t i = 0; i < width; i++) {
			vector3d dir((i + 1.) - width / 2., - (j + 1.) + height / 2., - height / (2. * tan(cam.showFov() / 2.)));
			dir -= cCent;
			for (size_t p = 0; p < spheres.size(); p++) {
				vector3d dist = spheres[p].showCenter() - cCent;
				double fi = acos(dist * dir / dist.magnitude() / dir.magnitude());
				if (sin(fi) <= spheres[p].showR() / dist.magnitude()) {
					pixels[i + j * width] = spheres[p].showColor();
					vector3d pnt = spheres[p].point(cCent, dist, dir, fi);
					illumination(pnt, pixels[i + j * width], light, spheres[p], cCent);
				}
			}
		}
	}

	std::ofstream ofs;
	ofs.open("./out.ppm");
	ofs << "P6\n" << width << " " << height << "\n255\n";
	for (size_t j = 0; j < height * width; j++) {
		ofs << (char)(255 * fmax(0., fmin(1., pixels[j].showX()))) << (char)(255 * fmax(0., fmin(1., pixels[j].showY()))) << (char)(255 * fmax(0., fmin(1., pixels[j].showZ())));
	}
	ofs.close();
}

int main(void) {
	Sphere s1(vector3d(-3, 4.5, -16), 5, vector3d(0, 0.9, 0.2), 1);
	Sphere s2(vector3d(1, -1, -13), 6.5, vector3d(0, 0.3, 0.5), 2.4);
	Sphere s3(vector3d(7, -2.5, -10), 3.5, vector3d(0.5, 0.1, 0.2), 4.7);
	std::vector<Sphere> spheres = { s1, s2, s3 };
	
	Camera cam(vector3d(2.5, 0.5, 5), M_PI / 3.);
	Light light(vector3d(-70, -90, 110), 0.8);
	vector3d background(0.85, 0.7, 0.99);

	DrawPicture img;
	img.draw(background, spheres, light, cam);

	return 0;
}