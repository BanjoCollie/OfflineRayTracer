#pragma once

#include <string>
#include <vector>

#include "Vector3.h"
#include "Color.h"
#include "Shape.h"
#include "Ray.h"
#include "Light.h"
#include "Triangle.h"

class Scene {
public:
	void AddSphere(Vector3 pos, float r, Material* material, Texture* text = nullptr);
	void AddEllipsoid(Vector3 pos, Vector3 r, Material* material);
	void AddLight(Vector4 pos, Color col, float base = 1.0, float lin =	0.0, float quad = 0.0);
	void AddSpotLight(Vector4 pos_, Color col_, float theta_, Vector3 dir_, float base = 1.0, float lin = 0.0, float quad = 0.0);
	void AddPoint(Vector3 pos);
	void AddNormal(Vector3 norm);
	void AddUV(Vector2 uv);
	void AddTriangle(int point1, int point2, int point3, int text1, int text2, int text3, int norm1, int norm2, int norm3, Material* mat, Texture* tex);

	Color ShadeRay(Ray r, Vector3 eyePos, Color bkColor, std::vector<float> refractionStack, int depth = 0);

private:
	int maxDepth = 5;

	std::vector<Shape*> shapes;
	std::vector<Light*> lights;
	std::vector<Vector3*> points;
	std::vector<Vector3*> normals;
	std::vector<Vector2*> UVs;
	std::vector<Color**> textures;

	RayCollision* CastRay(Ray r, float maxDist = 1e300);
};