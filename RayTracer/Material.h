#pragma once

#include "Color.h"
#include <iostream>

struct Material
{
	
	Color diffuseColor;
	Color specularColor;
	float kAmbient;
	float kDiffuse;
	float kSpecular;
	float n;
	float opacity;
	float refraction;

	Material(Color& dCol_, Color& sCol_, float kA_, float kD_, float kS_, float n_, float opacity_, float refraction_) :
		diffuseColor(dCol_),
		specularColor(sCol_),
		kAmbient(kA_),
		kDiffuse(kD_),
		kSpecular(kS_),
		n(n_),
		opacity(opacity_),
		refraction(refraction_) {}

};