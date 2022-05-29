#pragma once
#include "RenderObject.h"
#include "Fundation/Type/Enumerate.h"
#include "Renderer/Shader/ShaderProgram.h"

class AxisObject : public InherientObject
{
public:
	Enumerate(AxisType, uint8_t, 
		xAxis = 0, 
		yAxis, 
		zAxis);

	AxisObject(AxisType axisType = AxisType::xAxis);
	~AxisObject();

	bool antialiasing() const { return _antialiasing; }
	void setAntialiasing(bool enable);

	void setLineWidth(float width);
	void setScaled(float scaled);

	virtual void draw() override;
	virtual Unique<ShaderProgram>& shader() override
	{
		return _program;
	}

private:
	AxisType  _axisType;
	glm::vec4 _axisColor;
	bool      _antialiasing;
	float     _scaled;
	glm::mat4 _scaledMatrix;

	std::array<glm::vec3, 2> _vertex;
	std::array<unsigned int, 2> _index;
	unsigned int _VAO, _VBO, _EBO;

	Unique<ShaderProgram> _program;
};
