#pragma once
#include "Renderer/Camera/Camera.h"

class TargetCamera : public Camera
{
	SELF(TargetCamera);
	SUPER(Camera);
public:
	TargetCamera(const glm::vec3& pos, float fovy, float aspectRatio, float zNear = 0.1f, float zFar = 1000.f);

	void updatePos(const glm::vec3& deltaPosition);
	void updateDirection(const float deltaX, const float deltaY);

	glm::mat4& lookAtMatrix();
	glm::mat4& perspectiveMatrix();

private:
	void updateCameraVectors();

private:
	// Camera attributes
	glm::vec3 _position;
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _right;
	glm::vec3 _worldUp;
	glm::mat4 _lookAt;
	glm::mat4 _perspective;
	float     _fovy;
	float     _aspectRatio;
	float     _zNear;
	float     _zFar;

	// Eular angles
	float _yaw;
	float _pitch;

	// Constants
	static const float YAW;
	static const float PITCH;

};