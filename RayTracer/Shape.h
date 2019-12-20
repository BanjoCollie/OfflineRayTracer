#pragma once

#include "Vector3.h"
#include "Material.h"
#include "Ray.h"
#include "RayCollision.h"

#include <vector>

struct Shape
{
	Vector3 pos;
	Material* mat;
	Texture* texture;

	Shape(Vector3 pos_, Material* mat_, Texture* tex_ = nullptr) : pos(pos_), mat(mat_), texture(tex_) {}

	virtual vector<RayCollision> RayCollisions(Ray r) = 0;
};