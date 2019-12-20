
#include "Camera.h"
#include "Vector3.h"
#include "Scene.h"
#include "Ray.h"

#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>

Camera::Camera(Vector3& eyePos_, Vector3& viewDir_, Vector3& upDir_, float vFOV_, Vector2& screenSize_, Color& backColor_) :
	eyePos(eyePos_), viewDir(viewDir_), upDir(upDir_), vFOV(vFOV_), screenSize(screenSize_), backColor(backColor_)
{
	u = (viewDir.Cross(upDir)).GetNormal();
	v = (u.Cross(viewDir)).GetNormal();
	viewDist = (float)0.1;

	float PI = 3.14159265;
	aspectRatio = screenSize.x / screenSize.y;
	viewHeight = 2 * viewDist * tan(vFOV/2.0f * 3.14159265 / 180.0);
	viewWidth = viewHeight * aspectRatio;

	Vector3 n = viewDir.GetNormal();

	ul = eyePos + n * viewDist - u * (viewWidth / 2) + v * (viewHeight / 2);
	ur = eyePos + n * viewDist + u * (viewWidth / 2) + v * (viewHeight / 2);
	ll = eyePos + n * viewDist - u * (viewWidth / 2) - v * (viewHeight / 2);
	lr = eyePos + n * viewDist + u * (viewWidth / 2) - v * (viewHeight / 2);

	pixelBuffer = new Color*[(int)screenSize.x];
	for (int i = 0; i < screenSize.x; i++)
		pixelBuffer[i] = new Color[(int)screenSize.y];
}

void Camera::Draw(Scene& scene, ofstream &output)
{
	// Have scene do raycasts and put results in the pixel buffer
	for (int j = 0; j < screenSize.y; j++)
	{
		for (int i = 0; i < screenSize.x; i++)
		{
			Vector3 uOff = u * viewWidth * ((float)i / screenSize.x);
			Vector3 vOff = -v * viewHeight * ((float)j / screenSize.y);
			Vector3 pixelPos = ul + uOff + vOff;
			Ray pixelRay(eyePos, pixelPos - eyePos);

			std::vector<float> baseStack;
			baseStack.push_back(1.0);
			pixelBuffer[i][j] = scene.ShadeRay(pixelRay, eyePos, backColor, baseStack);
		}
	}

	// Export the pixel buffer to the output file
	output << "P3" << std::endl
		<< "# Raytraced image" << std::endl
		<< screenSize.x << " " << screenSize.y << std::endl
		<< "255" << std::endl;

	for (int j = 0; j < screenSize.y; j++)
	{
		for (int i = 0; i < screenSize.x; i++)
		{
			Color myColor = pixelBuffer[i][j];
			output << std::roundf(myColor.r*255) <<  " " 
				<< std::roundf(myColor.g*255) << " " 
				<< std::roundf(myColor.b*255) << std::endl;
		}
	}


	return;
}