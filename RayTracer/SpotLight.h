#pragma once

#include "Vector4.h"
#include "Color.h"
#include "Light.h"

#include <cmath>

struct SpotLight : Light
{
	float theta;
	Vector3 dir;

	SpotLight(Vector4 pos_, Color col_, float theta_, Vector3 dir_, float base = 1.0, float lin = 0.0, float quad = 0.0) :
		Light(pos_, col_, base, lin, quad)
	{
		theta = theta_;
		dir = -dir_.GetNormal();
	}

	float GetAttenuation(Vector3 position)
	{
		float dist = 0;
		if (pos.w == 1)
			dist = (pos.Vec3() - position).Length()/5.0f;

		if (dir.Dot((pos.Vec3() - position).GetNormal()) >= cos(theta * 3.14159265/ 180.0))
			return 1.0f / (baseVal + linearVal * dist + quadVal * dist * dist);
		else
			return 0.0;
	}
};