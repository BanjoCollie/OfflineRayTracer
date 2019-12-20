#pragma once

using namespace std;

struct Vector3 {
public:
	Vector3(float x_ = 0.0, float y_ = 0.0, float z_ = 0.0) : x(x_), y(y_), z(z_) {}

	float x;
	float y;
	float z;

	static Vector3 RandomDir();

	Vector3 Cross(Vector3 otherVec);
	float Dot(Vector3 otherVec);
	Vector3 operator - ();
	Vector3 operator + (Vector3 otherVec);
	void operator += (Vector3 otherVec);
	Vector3 operator - (Vector3 otherVec);
	Vector3 operator * (float scalar);
	Vector3 operator / (float scalar);
	void Normalize();
	Vector3 GetNormal();
	float Length();
	bool IsParallel(Vector3 otherVec);
};
