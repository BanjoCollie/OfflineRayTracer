#pragma once

struct Texture
{
	Color** colorBuffer;
	int width; int height, maxVal;

	Texture(Color** buffer_, int width_, int height_, int maxVal_) :
		colorBuffer(buffer_),
		width(width_),
		height(height_),
		maxVal(maxVal_) {}
};