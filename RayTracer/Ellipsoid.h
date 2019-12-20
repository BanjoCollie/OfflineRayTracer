#pragma once

#include "Shape.h"
#include "Material.h"

struct Ellipsoid : Shape {
public:
	Vector3 radius;

	Ellipsoid(Vector3 pos_, Material* mat_, Vector3 radius_) : Shape(pos_, mat_), radius(radius_) {}

	vector<RayCollision> RayCollisions(Ray r);
};