#pragma once

#include "Vector4.h"
#include "Color.h"

struct Light
{
	Vector4 pos;
	Color col;
	float baseVal, linearVal, quadVal;

	Light(Vector4 pos_, Color col_, float base = 1.0, float lin = 0.0, float quad = 0.0) : 
		pos(pos_), col(col_),
		baseVal(base), linearVal(lin), quadVal(quad) {}

	virtual float GetAttenuation(Vector3 position) 
	{
		float dist = 0;
		if (pos.w == 1)
			dist = (pos.Vec3() - position).Length()/5.0f;
		return 1.0f / (baseVal + linearVal * dist + quadVal * dist * dist); 
	}
};