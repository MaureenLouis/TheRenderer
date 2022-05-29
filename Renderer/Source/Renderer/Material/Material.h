#pragma once
#include "Fundation/Type/Enumerate.h"

class Material
{
public:
	Enumerate(Type, uint16_t, 
		DiffuseColor = 1,
		SpecularColor,
		Glossiness, SpecularLevel);

	void setMaterialColor(Material::Type type, const aiColor4D& color);
	glm::vec4 materialColor(Material::Type type);


	void setMaterialStrength(Material::Type type, float value);
	float materialStrength(Material::Type type);

private:
	glm::vec4 _diffuseColor;
	glm::vec4 _specularColor;
	float _glossiness;
	float _specularLevel;
};