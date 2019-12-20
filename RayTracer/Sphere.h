#pragma once

#include "Shape.h"
#include "Material.h"

struct Sphere : Shape{
public:
	float radius;

	Sphere(Vector3 pos_, Material* mat_, float radius_, Texture* texture = nullptr) : Shape(pos_, mat_, texture), radius(radius_) {}

	vector<RayCollision> RayCollisions(Ray r);
};