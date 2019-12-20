
#include "Vector3.h"

#include <cmath>


Vector3 Vector3::RandomDir()
{
	float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	Vector3 newVec(x, y, z);
	newVec.Normalize();
	return newVec;
}

Vector3 Vector3::Cross(Vector3 otherVec)
{
	Vector3 result(y*otherVec.z - z*otherVec.y, z*otherVec.x - x*otherVec.z, x*otherVec.y - y*otherVec.x);
	return result;
}

float Vector3::Dot(Vector3 otherVec)
{
	return x*otherVec.x + y*otherVec.y + z*otherVec.z;
}

Vector3 Vector3::operator - ()
{
	Vector3 result = Vector3(-x, -y, -z);
	return result;
}

Vector3 Vector3::operator + (Vector3 otherVec)
{
	Vector3 result(x + otherVec.x, y + otherVec.y, z + otherVec.z);
	return result;
}

void Vector3 ::operator += (Vector3 otherVec)
{
	x += otherVec.x;
	y += otherVec.y;
	z += otherVec.z;
}

Vector3 Vector3::operator - (Vector3 otherVec)
{
	Vector3 result(x - otherVec.x, y - otherVec.y, z - otherVec.z);
	return result;
}

Vector3 Vector3::operator * (float scalar)
{
	Vector3 result(x * scalar, y * scalar, z * scalar);
	return result;
}

Vector3 Vector3::operator / (float scalar)
{
	Vector3 result(x / scalar, y / scalar, z / scalar);
	return result;
}

void Vector3::Normalize()
{
	float l = Length();
	x = x / l;
	y = y / l;
	z = z / l;
}

Vector3 Vector3::GetNormal()
{
	float l = Length();
	float x_ = x / l;
	float y_ = y / l;
	float z_ = z / l;
	Vector3 result(x_, y_, z_);
	return result;
}

float Vector3::Length()
{
	return sqrtf(x*x + y*y + z*z);
}

bool Vector3::IsParallel(Vector3 otherVec)
{
	float xs = x / otherVec.x;
	float ys = y / otherVec.y;
	float zs = z / otherVec.z;

	return ((xs == ys) && (ys == zs));
}