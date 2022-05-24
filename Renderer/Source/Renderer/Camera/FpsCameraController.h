#pragma once


// FPS camera implemented by Eular angle
class FpsCameraController
{
	SELF(FpsCameraController);

public:
	FpsCameraController()
	{
		_position = glm::vec3(-2.f, 0.f, 2.f);
		_worldUp  = glm::vec3(0.f, 1.f, 0.f);

		_mouseSensitivity = 0.1f;

		_yaw   = -45.f;
		_pitch = 0.f;


		Self::recalculateCameraVectors();
	}

	/**
	 * @brief: Recalculate Front, Right, Up vectors for LookUp matrix
	 *         refer to Yaw and Pitch
	 * 
	 * 
	 */
	void recalculateCameraVectors()
	{
		glm::vec3 front = Self::eularToCartesian(_yaw, _pitch);

		_front = glm::normalize(front);
		_right = glm::normalize(glm::cross(_front, _worldUp));
		_up    = glm::normalize(glm::cross(_right, _front));
	}

	/**
	 * @brief: Transfer eular angles into Cartesian coordinates.
	 * 
	 * @param: yaw 
	 * @param: pitch
	 */
	glm::vec3 eularToCartesian(float yaw, float pitch)
	{
		glm::vec3 vec;

		vec.x = glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw));
		vec.y = glm::sin(glm::radians(pitch));
		vec.z = glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(yaw));

		return vec;
	}

	/**
	 * @brief: Calculate View matrix.
	 * 
	 */
	glm::mat4 getViewMatrix()
	{
		return glm::lookAt(_position, _position + _front, _up);
	}

	void updateDirection(float deltaYaw, float deltaPitch)
	{
		_yaw += deltaYaw * 0.1f;
		_pitch += deltaPitch * 0.1f;

		Self::recalculateCameraVectors();
	}

private:
	glm::vec3 _position;
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _right;
	glm::vec3 _worldUp;

	float _yaw, _pitch;
	float _movementSpeed;
	float _mouseSensitivity;
	float _zoom;
};