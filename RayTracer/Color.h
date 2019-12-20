#pragma once

#include "Vector3.h"

#include <algorithm>

using namespace std;

struct Color {
public:
	Color(float r_ = 0.0f, float g_ = 0.0f, float b_ = 0.0f)
		{ r = min(1.0f, r_); g = min(1.0f, g_); b = min(1.0f, b_); }
	Color(int r_, int g_, int b_) 
		{ r = min(1.0f, r_ / 255.0f); min(1.0f, g = g_ / 255.0f); b = min(1.0f, b_ / 255.0f); }
	Color(const Color& col)
		{ r = min(1.0f, col.r); g = min(1.0f, col.g); b = min(1.0f, col.b); }
	Color(Vector3 v)
		{ r = min(1.0f, v.x); g = min(1.0f, v.y); b = min(1.0f, v.z); }
	Color(float f)
		{ r = min(1.0f, f); g = r; b = r; }


	Color operator + (Color otherCol) { return Color(r + otherCol.r, g + otherCol.g, b + otherCol.b); }
	void operator += (Color otherCol) { r = min(1.0f, r + otherCol.r); g = min(1.0f, g + otherCol.g); b = min(1.0f, b + otherCol.b); }
	Color operator * (Color otherCol) { return Color(r * otherCol.r, g * otherCol.g, b * otherCol.b); }
	Color operator * (float scalar) { return Color(r * scalar, g * scalar, b * scalar); }

	float r;
	float g;
	float b;
};