
#include "Vector4.h"

Vector4 Vector4::operator - ()
{
	Vector4 result = Vector4(-x, -y, -z, w);
	return result;
}

Vector4 Vector4::operator + (Vector4 otherVec)
{
	Vector4 result;
	if (w == 1)
	{
		result = Vector4(Vec3() + (otherVec.Vec3() * otherVec.w), w * otherVec.w);
	}
	else
		result = *this;
	
	return result;
}

Vector4 Vector4::operator - (Vector4 otherVec)
{
	Vector4 result;
	if (w != 0 || otherVec.w != 1)
	{
		Vector3 v3part = Vec3() - otherVec.Vec3();
		float wpart = 0;
		if (w == 1 && otherVec.w == 0)
			wpart = 1;
		result = Vector4(v3part, wpart);
	}
	else
		result = *this;

	return result;
}