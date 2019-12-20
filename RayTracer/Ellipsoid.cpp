
#include "Ellipsoid.h"
#include <cmath>

vector<RayCollision> Ellipsoid::RayCollisions(Ray r)
{
	vector<RayCollision> collisions;

	// Ellipsoid - x2/a2 + y2/b2 + z2/c2 = 1
	// Ray - (x,y,z) = (x0,y0,z0) + t*(xd,yd,zd)

	//(x0+t*xd)^2/a^2 + (y0+t*yd)^2/b^2 + (z0+t*zd)^2/c^2 = 1
	//(x0^2 + 2x0*t*xd + t^2*xd^2)/a^2 + (y0^2 + 2y0*t*yd + t^2*yd^2)/b^2 + (z0^2 + 2z0*t*zd + t^2*zd^2)/c^2 = 1
	// (xd^2/a^2 + yd^2/b^2 + zd^2/c^2)*t^2 + (2x0xd/a^2 + 2y0yd/b^2 + 2z0zd/c^2)*t + (x0^2/a^2 + y0^2/b^2 + z0^2/c^2 - 1) = 0


	// Collision when At^2 + Bt + C = 0
	Vector3 relPos = r.position - pos;
	float a = r.direction.x*r.direction.x/(radius.x*radius.x) + r.direction.y*r.direction.y/(radius.y*radius.y) + r.direction.z*r.direction.z/(radius.z*radius.z);
	float b = 2 * (relPos.x*r.direction.x/(radius.x*radius.x) + relPos.y*r.direction.y/(radius.y*radius.y) + relPos.z*r.direction.z/(radius.z*radius.z));
	float c = (relPos.x*relPos.x)/(radius.x*radius.x) + (relPos.y*relPos.y)/(radius.y*radius.y) + (relPos.z*relPos.z)/(radius.z*radius.z) - 1;

	float discrim = b * b - 4 * a * c;

	if (discrim == 0)
	{
		float t = -b / (2 * a);

		Vector3 colPos = r.position + (r.direction * t);
		Vector3 posDif = colPos - pos;
		Vector3 norm = Vector3(posDif.x / (radius.x * radius.x), posDif.y / (radius.y * radius.y), posDif.z / (radius.z * radius.z));

		RayCollision newCol(colPos, norm.GetNormal(), Vector2(0, 0), mat);
		collisions.push_back(newCol);

	}
	else if (discrim > 0)
	{
		float t = (-b + std::sqrt(discrim)) / (2 * a);
		Vector3 colPos = (r.position + (r.direction * t));
		Vector3 posDif = colPos - pos;
		Vector3 norm = Vector3(posDif.x / (radius.x * radius.x), posDif.y / (radius.y * radius.y), posDif.z / (radius.z * radius.z));
		RayCollision newCol(colPos, norm.GetNormal(), Vector2(0, 0), mat);
		collisions.push_back(newCol);

		t = (-b - std::sqrt(discrim)) / (2 * a);
		colPos = (r.position + (r.direction * t));
		posDif = colPos - pos;
		norm = Vector3(posDif.x / (radius.x * radius.x), posDif.y / (radius.y * radius.y), posDif.z / (radius.z * radius.z));
		RayCollision newCol2(colPos, norm.GetNormal(), Vector2(0, 0), mat);
		collisions.push_back(newCol2);
	}

	return collisions;
}