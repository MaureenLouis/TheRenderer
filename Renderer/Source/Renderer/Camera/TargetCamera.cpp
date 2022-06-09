#include "stdafx.h"
#include "TargetCamera.h"

const float TargetCamera::YAW         = -90.f;
const float TargetCamera::PITCH       = 0.f;

TargetCamera::TargetCamera(const glm::vec3& pos, float fovy, float aspectRatio, float zNear, float zFar)
{
	_front            = glm::vec3(0.f, 0.f, -1.f);

	_up = glm::vec3(0.f, 1.f, 0.f);

	_fovy = fovy;
	_aspectRatio = aspectRatio;
	_zNear = zNear;
	_zFar  = zFar;

	_perspective = glm::perspective(_fovy, _aspectRatio, _zNear, _zFar);


	_position = pos;
	_worldUp = _up;
	_yaw = Self::YAW;
	_pitch = Self::PITCH;

	Self::updateCameraVectors();
}

void TargetCamera::updateDirection(const float deltaX, const float deltaY)
{
	_yaw += deltaX;
	_pitch += deltaY;

	if (_pitch > 89.f)
	{
		_pitch = 89.f;
	}
	if (_pitch < -89.f)
	{
		_pitch = -89.f;
	}

	Self::updateCameraVectors();
}


void TargetCamera::updatePos(const glm::vec3& deltaPosition)
{
	_position += deltaPosition;

	Self::updateCameraVectors();
}

void TargetCamera::updateCameraVectors()
{
    // Calculate front vector
	glm::vec3 front;
	front.x = glm::cos(glm::radians(_yaw)) * glm::cos(glm::radians(_pitch));
	front.y = glm::sin(glm::radians(_pitch));
	front.z = glm::sin(glm::radians(_yaw)) * glm::cos(glm::radians(_pitch));
	_front  = glm::normalize(front);

	// Recalculate right and up vector
	_right = glm::normalize(glm::cross(_front, _worldUp));
	_up = glm::normalize(glm::cross(_right, _right));

	// Recalculate look at matrix
	_lookAt = glm::lookAt(_position, _position + _front, _up);
}   

glm::mat4& TargetCamera::lookAtMatrix()
{
	return _lookAt;
}

glm::mat4& TargetCamera::perspectiveMatrix()
{
	return _perspective;
}
