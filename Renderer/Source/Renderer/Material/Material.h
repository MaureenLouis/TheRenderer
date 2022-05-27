#pragma once
#include "Fundation/Type/Enumerate.h"

class Material
{
public:
	Enumerate(Type, uint16_t, 
		DiffuseColor = 1);

	void setMaterialColor(Material::Type type, const aiColor4D& color);
	glm::vec4 materialColor(Material::Type type);

private:
	glm::vec4 _diffuseColor;
};