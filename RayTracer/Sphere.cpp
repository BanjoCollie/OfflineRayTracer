
#include "Sphere.h"
#include <cmath>

vector<RayCollision> Sphere::RayCollisions(Ray r)
{
	vector<RayCollision> collisions;


	// Collision when At^2 + Bt + C = 0
	float a = 1;
	float b = 2 * (r.direction.x * (r.position.x-pos.x)  +  r.direction.y * (r.position.y-pos.y)  +  r.direction.z * (r.position.z-pos.z));
	float c = std::pow(r.position.x-pos.x, 2) + std::pow(r.position.y-pos.y, 2) + std::pow(r.position.z-pos.z, 2) - radius*radius;

	float discrim = b * b - 4 * a * c;

	if (discrim == 0)
	{
		float t = -b / (2 * a);
		Vector3 colPos = r.position + (r.direction * t);
		Vector3 norm = (colPos - pos).GetNormal();
		float phi = acos(norm.z);
		float theta = atan2(norm.y, norm.x);
		if (theta < 0)
			theta = theta + 6.2831853;
		Vector2 uv(theta / 6.2831853, phi / 3.14159265);
		RayCollision newCol(colPos, norm, uv, mat, texture);
		collisions.push_back(newCol);
	}
	else if (discrim > 0)
	{
		float t = (-b + std::sqrt(discrim)) / (2 * a);
		Vector3 colPos = (r.position + (r.direction * t));
		Vector3 norm = (colPos - pos).GetNormal();
		float phi = acos(norm.z);
		float theta = atan2(norm.y, norm.x);
		if (theta < 0)
			theta = theta + 6.2831853;
		Vector2 uv(theta / 6.2831853, phi / 3.14159265);
		RayCollision newCol(colPos, norm, uv, mat, texture);
		collisions.push_back(newCol);

		t = (-b - std::sqrt(discrim)) / (2 * a);
		Vector3 colPos2 = (r.position + (r.direction * t));
		Vector3 norm2 = (colPos2 - pos).GetNormal();
		phi= acos(norm2.z);
		theta = atan2(norm2.y, norm2.x);
		if (theta < 0)
			theta = theta + 6.2831853;
		Vector2 uv2(theta / 6.2831853, phi / 3.14159265);
		RayCollision newCol2(colPos2, norm2, uv2, mat, texture);
		collisions.push_back(newCol2);
	}

	return collisions;
}