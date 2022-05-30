#pragma once

class Material
{
public:
	Material();

public:
	glm::vec4 _ambientColor;
	float _ambientLevel;
	glm::vec4 _diffuseColor;
	glm::vec4 _specularColor;
	float _glossiness;
	float _specularLevel;
};