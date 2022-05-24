#pragma once

class CameraController
{

public:


private:
	glm::vec4 toCartesian()
	{
		float x = _rho * glm::sin(_phi) * glm::sin(_theta);
		float y = _rho * glm::sin(_phi) * glm::cos(_theta);
		float z = _rho * glm::cos(_phi);

		return glm::vec4(x, y, z, 1.f);
	}

private:
	float _theta;
	float _phi;
	float _rho;
};