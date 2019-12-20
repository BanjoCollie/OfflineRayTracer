#pragma once

using namespace std;

#include "Vector3.h"
#include "Vector2.h"
#include "Color.h"

#include "Scene.h"

#include <iostream>

class Camera {
public:
	Camera(Vector3& eyePos_, Vector3& viewDir_, Vector3& upDir_, float vFOV_, Vector2& screenSize_, Color& backColor_);

	Vector3 eyePos;
	Vector3 viewDir;
	Vector3 upDir;
	float vFOV;
	Vector2 screenSize;
	Color backColor;

	void Draw(Scene& scene, ofstream &output);

protected:
	Color ** pixelBuffer;

	Vector3 u;
	Vector3 v;
	float viewDist;
	float viewHeight;
	float viewWidth;
	float aspectRatio;
	Vector3 ul;
	Vector3 ur;
	Vector3 ll;
	Vector3 lr;

};