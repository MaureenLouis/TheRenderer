#pragma once
#include "Core/Compiler/Inline.h"

class PerspectiveCamera
{
public:
	PerspectiveCamera(const int width, const int height, const glm::vec3 position, const glm::vec3 target = glm::vec3(0.f), const float fov = 45.f, float zNear = 0.1f, float zFar = 100.f)
	{
		_data._w = width;
		_data._h = height;
		_data._position = position;
		_data._target = target;
		_data._fov = fov;
		_data._zNear = zNear;
		_data._zFar = zFar;

		calculatePV();
	}

	const glm::mat4& setPosition(const glm::vec3& position)
	{
		_data._position = position;
		calculatePV();
		return getPV();
	}

	const glm::vec3& position() const
	{
		return _data._position;
	}

	const glm::mat4& setTarget(const glm::vec3& target)
	{
		_data._target = target;
		calculatePV();
		return getPV();
	}

	ALWAYS_INLINE const glm::mat4& getPV() const
	{
		return _data._pv;
	}

	ALWAYS_INLINE const glm::mat4& P() const
	{
		return _data._p;
	}

private:
	void calculatePV() 
	{
		_data._v = glm::lookAt(_data._position, _data._target, glm::vec3(0.f, 1.f, 0.f));
		_data._p = glm::perspective(_data._fov, (float)_data._w / (float)_data._h, _data._zNear, _data._zFar);
		_data._pv = _data._p * _data._v;
	}

private:
	struct PerspectiveCameraData
	{
		int _w, _h;
		float _fov;
		float _zNear, _zFar;
		glm::vec3 _position;
		glm::vec3 _target;
		glm::mat4 _v;
		glm::mat4 _p;
		glm::mat4 _pv;
	} _data;
};

