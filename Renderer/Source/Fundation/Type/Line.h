#pragma once
#include "glm/glm.hpp"


template <typename ScalarType, bool Normal = false>
class Line3
{
	using ValueType = ScalarType;
	using PointType = glm::vec3;
	using SelfType = Line3<ScalarType>;

public:
	void setOrigin(const PointType& ori)
	{
		_ori = ori;
	}

	void setDirection(const glm::vec3& dir)
	{
		if (Normal)
		{
			_dir = glm::normalize(_dir);
		}
		else
		{
			_dir = dir;
		}
	}

	const glm::vec3 direction() const 
	{
		return _dir;
	}

	Line3<ScalarType, true> normalize()
	{
		if (!Normal)
		{
			_dir = glm::normalize(_dir);
			return *(Line3<ScalarType, true>*)this;
		}
	}

	const PointType origin() const
	{
		return _ori;
	}

private:
	PointType _ori;
	PointType _dir;
};