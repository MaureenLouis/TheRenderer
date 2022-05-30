#pragma once


class LightComponent
{
public:
	LightComponent();

	void setPosition(const glm::vec3& position)
	{ _position = position; }

	void setColor(const glm::vec3& color)
	{ _lightColor = color; }

	glm::vec3& position()
	{ return _position; }

	const glm::vec3& color() const
	{ return _lightColor; }

	float& lightPower()
	{ return _lightPower; }

private:
	glm::vec3 _position;
	glm::vec3 _lightColor;
	float     _lightPower;
};

