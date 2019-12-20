#pragma once

#include "Vector3.h"

using namespace std;

struct Vector4 {
public:
	Vector4(float x_ = 0.0, float y_ = 0.0, float z_ = 0.0, float w_ = 0.0) : 
		x(x_), y(y_), z(z_), w(w_) {}
	Vector4(Vector3 vec3, float w_) :
		x(vec3.x), y(vec3.y), z(vec3.z), w(w_) {}

	float x;
	float y;
	float z;
	float w;

	Vector3 Vec3() { return Vector3(x, y, z); }
	Vector4 operator - ();
	Vector4 operator + (Vector4 otherVec);
	Vector4 operator - (Vector4 otherVec);
};
