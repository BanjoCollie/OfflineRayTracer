#pragma once

#include "Material.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Texture.h"

struct RayCollision
{
	Vector3 position;
	Vector3 normal;
	Vector2 UV;
	Material* material;
	Texture* texture;

	RayCollision(Vector3 pos, Vector3 norm, Vector2 uv, Material* mat, Texture* text = nullptr) :
		position(pos),
		UV(uv),
		material(mat),
		texture(text) { normal = norm.GetNormal(); }
};