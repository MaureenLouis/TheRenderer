#pragma once
#include "Fundation/Type/Enumerate.h"

class Material
{
public:

	glm::vec4 _ambientColor;
	glm::vec4 _diffuseColor;
	glm::vec4 _specularColor;
	float _glossiness;
	float _specularLevel;
};