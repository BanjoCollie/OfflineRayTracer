#pragma once

#include "Shape.h"
#include "Material.h"

struct Triangle : Shape {
public:
	Vector3* p0;
	Vector3* p1;
	Vector3* p2;
	Vector2* t0;
	Vector2* t1;
	Vector2* t2;
	Vector3* n0;
	Vector3* n1;
	Vector3* n2;

	Triangle(Vector3 pos_, Material* mat_, Vector3* p0_, Vector3* p1_, Vector3* p2_,
			Vector2* t0_ = nullptr, Vector2* t1_ = nullptr, Vector2* t2_ = nullptr, 
			Vector3* n0_ = nullptr, Vector3* n1_ = nullptr, Vector3* n2_ = nullptr,
			Texture* texture = nullptr
			) :
		Shape(pos_, mat_, texture),
		p0(p0_),
		p1(p1_),
		p2(p2_),
		t0(t0_),
		t1(t1_),
		t2(t2_),
		n0(n0_),
		n1(n1_),
		n2(n2_) {}

	vector<RayCollision> RayCollisions(Ray r);
};