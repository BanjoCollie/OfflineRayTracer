#pragma once

#include "Vector3.h"

struct Ray {
	Vector3 position;
	Vector3 direction;

	Ray(Vector3 pos, Vector3 dir) : position(pos) { direction = dir.GetNormal(); }

};