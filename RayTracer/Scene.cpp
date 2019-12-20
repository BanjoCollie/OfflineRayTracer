
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Ellipsoid.h"
#include "Light.h"
#include "SpotLight.h"

#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

void Scene::AddSphere(Vector3 pos, float r, Material* material, Texture* text)
{
	shapes.push_back(new Sphere(pos, material, r, text));

	return;
}

void Scene::AddEllipsoid(Vector3 pos, Vector3 r, Material* material)
{
	shapes.push_back(new Ellipsoid(pos, material, r));

	return;
}	

void Scene::AddLight(Vector4 pos, Color col, float base, float lin, float quad)
{
	lights.push_back(new Light(pos, col, base, lin, quad));
}

void Scene::AddSpotLight(Vector4 pos_, Color col_, float theta_, Vector3 dir_, float base, float lin, float quad)
{
	lights.push_back(new SpotLight(pos_, col_, theta_, dir_, base, lin, quad));
}

void Scene::AddPoint(Vector3 pos)
{
	points.push_back(new Vector3(pos));
}

void Scene::AddNormal(Vector3 norm)
{
	normals.push_back(new Vector3(norm));
}

void Scene::AddUV(Vector2 uv)
{
	UVs.push_back(new Vector2(uv));
}

void Scene::AddTriangle(int point1, int point2, int point3, int text1, int text2, int text3, int norm1, int norm2, int norm3, Material* mat, Texture* tex)
{
	if (text1 == -1)
	{
		if (norm1 == -1)
		{
			// no normals or textures
			shapes.push_back(new Triangle(Vector3(0, 0, 0), mat, points[point1], points[point2], points[point3]));
		}
		else
		{
			// no textures
			shapes.push_back(new Triangle(Vector3(0, 0, 0), mat,
				points[point1], points[point2], points[point3],
				nullptr, nullptr, nullptr,
				normals[norm1], normals[norm2], normals[norm3]
			));
		}
	}
	else
	{
		if (norm1 == -1)
		{
			// no normals
			shapes.push_back(new Triangle(Vector3(0, 0, 0), mat,
				points[point1], points[point2], points[point3],
				UVs[text1], UVs[text2], UVs[text3],
				nullptr, nullptr, nullptr,
				tex
			));
		}
		else
		{
			// everything
			shapes.push_back(new Triangle(Vector3(0, 0, 0), mat,
				points[point1], points[point2], points[point3],
				UVs[text1], UVs[text2], UVs[text3],
				normals[norm1], normals[norm2], normals[norm3],
				tex
			));
		}
	}
}

RayCollision* Scene::CastRay(Ray r, float maxDist)
{
	std::vector<RayCollision> rayCollisions;

	for (auto& s : shapes)
	{
		std::vector<RayCollision> col = s->RayCollisions(r);
		rayCollisions.insert(rayCollisions.end(), col.begin(), col.end());
	}

	float minDist = 1e300;
	int minIndex = -1;
	for (int i = 0; i < rayCollisions.size(); i++)
	{
		float dist = (rayCollisions[i].position - r.position).Dot(r.direction);
		if (dist >= 0 && dist < minDist && dist < maxDist)
		{
			minDist = dist;
			minIndex = i;
		}
	}

	if (minIndex == -1)
		return nullptr;
	else
	{
		RayCollision* colPntr = new RayCollision(rayCollisions[minIndex]);
		return colPntr;
	}

}

Color Scene::ShadeRay(Ray r, Vector3 eyePos, Color bkColor, std::vector<float> refractionStack, int depth)
{
	
	Color shadedColor = bkColor;
	
	RayCollision* collision = CastRay(r);
	if (collision)
	{
		Vector3 colPos = collision->position;
		Material myMat = *(collision->material);
		Vector3 norm = collision->normal;
		Vector3 toViewer = (eyePos - colPos).GetNormal();

		Vector3 toLight = (-colPos).GetNormal();
		Vector3 halfVec = (toLight + toViewer).GetNormal();

		Color ambient, diffuse, specular, cast;

		Color diffuseCol = myMat.diffuseColor;
		Texture* myTex = collision->texture;
		if (myTex != nullptr)
		{
			int x = round(collision->UV.x * (myTex->width - 1));
			int y = round(collision->UV.y * (myTex->height - 1));
			diffuseCol = *(myTex->colorBuffer[y * myTex->width + x]);
		}

		ambient = diffuseCol * myMat.kAmbient;
		if (lights.size() > 0)
		{
			for (Light* l : lights)
			{
				float distToLight;
				if (round(l->pos.w) == 0)
				{
					toLight = (-l->pos - Vector4(colPos, 1)).Vec3().GetNormal();
					distToLight = 0.0f;
				}
				else
				{
					toLight = (l->pos - Vector4(colPos, 1)).Vec3().GetNormal();
					distToLight = (l->pos - Vector4(colPos, 1)).Vec3().Length();
				}

				Vector3 halfVec = (toLight + toViewer).GetNormal();
				float shadow = 1.0f;
				//*
				// Hard shadows
				Ray shadowRay(colPos, toLight);
				shadowRay.position += shadowRay.direction * 0.001f;
				if (round(l->pos.w) == 0)
				{
					if (CastRay(shadowRay))
						shadow = 0.0f;
				}
				else
				{
					float distToLight = (l->pos - Vector4(colPos, 1)).Vec3().Length();
					if (CastRay(shadowRay, distToLight))
						shadow = 0.0f;
				}
				//*/

				/*
				// Soft shadows
				int numShadowRays = 50;
				float totalShadow = 0;
				float softShadowOffset = 1.0f;
				for (int i = 0; i < numShadowRays; i++)
				{
					float thisShadow = 1.0f;

					float myOffset = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / softShadowOffset));
					Vector3 lightPos = l->pos.Vec3() + Vector3::RandomDir() * myOffset;
					Vector3 toLightPos = (lightPos - colPos).GetNormal();

					Ray shadowRay(colPos, toLightPos);
					shadowRay.position += shadowRay.direction * 0.001f;
					if (l->pos.w == 0)
					{
						if (CastRay(shadowRay))
							thisShadow = 0.0f;
					}
					else
					{
						float distToLight = (lightPos - colPos).Length();
						if (CastRay(shadowRay, distToLight))
							thisShadow = 0.0f;
					}

					totalShadow += thisShadow;
				}

				shadow = totalShadow / numShadowRays;
				//*/

				// Refraction calculations
				Vector3 n = collision->normal;

				bool entering = false;
				std::vector<float> newStack = refractionStack;
				if (r.direction.Dot(collision->normal) < 0)
				{
					// Entering into object
					newStack.push_back(collision->material->refraction);
					entering = true;
				}
				else
				{
					// Leaving object
					newStack.pop_back();
					n = -n;
				}
				float a = n.Dot(-r.direction);

				float incomingRefraction = 1.0;
				float transmittingRefraction;
				if (refractionStack.size() > 0)
				{
					incomingRefraction = refractionStack.back();
				}
				transmittingRefraction = newStack.back();
				float ratio = incomingRefraction / transmittingRefraction;

				Vector3 refractDir = -n * sqrt(1 - (pow(ratio, 2) * (1 - pow(a, 2))))
					+ (n * a + r.direction) * ratio;
				
				//Vector3 refractDir = r.direction;

				Ray refractedRay(collision->position, refractDir);
				refractedRay.position += refractedRay.direction * 0.005f;

				if (!entering && refractDir.GetNormal().Dot(collision->normal) < 0)
				{
					// TIR
					newStack.push_back(collision->material->refraction);
				}

				// Reflection calculations
				Vector3 rayDir = r.direction + n * 2 * a;
				Ray reflectedRay(collision->position, rayDir);
				reflectedRay.position += reflectedRay.direction * 0.005f;
				float F0 = (myMat.refraction - 1) / (myMat.refraction + 1);
				F0 *= F0;
				float Fr = F0 + (1 - F0) * pow(1 - a, 5);



				diffuse += l->col * shadow * l->GetAttenuation(colPos) * (diffuseCol * myMat.kDiffuse * std::max(0.0f, norm.Dot(toLight)));
				specular += l->col * shadow * l->GetAttenuation(colPos) *
					(myMat.specularColor * myMat.kSpecular * std::pow(std::max(0.0f, norm.Dot(halfVec)), myMat.n));
				
				
				if (depth < maxDepth && Fr > 0.001)
				{
					// Reflections
					cast += (ShadeRay(reflectedRay, collision->position, bkColor, refractionStack, depth + 1) * Fr);
				}
				if (depth < maxDepth && Fr < 0.99 && myMat.opacity < 0.99)
				{
					// Transparency
					cast += (ShadeRay(refractedRay, collision->position, bkColor, newStack, depth + 1) * (1 - Fr) * (1 - myMat.opacity));
				}
				if (depth > 1.0)
				{
					int x = 1;
				}
				if (depth == 1.0)
				{
					int x = 1;
				}
			}
		}
		else
		{
			diffuse = diffuseCol * myMat.kDiffuse * std::max(0.0f, norm.Dot(toLight));
			specular = myMat.specularColor * myMat.kSpecular * std::pow(std::max(0.0f, norm.Dot(halfVec)), myMat.n);
		}

		shadedColor = ambient + diffuse + specular + cast;
	}

	return shadedColor;

}
