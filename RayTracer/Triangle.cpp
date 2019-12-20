
#include "Triangle.h"
#include "Vector3.h"

vector<RayCollision> Triangle::RayCollisions(Ray r) 
{
	vector<RayCollision> collisions;

	// First get plane normal
	Vector3 e1 = *p1 - *p0;
	Vector3 e2 = *p2 - *p0;
	Vector3 cross = e1.Cross(e2);
	float area = cross.Length() / 2.0f;
	Vector3 normal = cross.GetNormal();
	// nx*p0x + ny*p0y + nz*p0z + D = 0
	float d = -(normal.Dot(*p0));

	// t = –(A*x0 + B*y0 + C*z0 + D)/(A*xd+ B*yd+ C*zd)
	float denom = normal.Dot(r.direction);
	if (denom == 0)
	{
		// Ray doesnt hit plane triangle lies on
		return collisions;
	}
	
	float t = -(normal.Dot(r.position) + d) / denom;

	if (t > 0)
	{
		// there is a collision with the plane in the positive direction
		Vector3 onPlane = r.position + r.direction * t;
		
		Vector3 e3 = onPlane - *p1;
		Vector3 e4 = onPlane - *p2;
		
		// Area of triangle opposite of p0
		float a = e3.Cross(e4).Length()/2;
		// Area of triangle opposite of p1
		float b = e4.Cross(e2).Length() / 2;
		// Area of triangle opposite of p2
		float c = e1.Cross(e3).Length() / 2;

		float alpha = a / area;
		float beta = b / area;
		float gamma = c / area;

		float epsilon = 0.0001f;
		if (
			alpha > -epsilon && alpha < 1.0f+epsilon &&
			beta > -epsilon && beta < 1.0f+epsilon &&
			gamma > -epsilon && gamma < 1.0f+epsilon &&
			alpha + beta + gamma - 1.0f < epsilon)
		{
			Vector3 norm = normal;
			if (n0 != nullptr)
			{
				norm = (*n0 * alpha + *n1 * beta + *n2 * gamma).GetNormal();
			}

			Vector2 tex = Vector2(0, 0);
			if (t0 != nullptr)
			{
				tex.x = t0->x * alpha + t1->x * beta + t2->x * gamma;
				tex.y = t0->y * alpha + t1->y * beta + t2->y * gamma;
			}

			// point is in triangle

			RayCollision newCol(onPlane, norm, tex, mat, texture);
			collisions.push_back(newCol);
		}
	}

	return collisions;
}