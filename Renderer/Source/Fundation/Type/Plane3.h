#pragma once
#include "glm/glm.hpp"

template <typename T, bool NORM = false>
class Plane3
{
	using ScalarType = T;
	using PointType = glm::vec3;
	using Self = Plane3<T, NORM>;

public:
	Plane3() = default;

	Plane3(const ScalarType dist, const PointType& dir)
	{
		Self::set(dist, dir);
	}

	void set(const ScalarType off, const PointType& dir)
	{
		if (NORM)
		{
			_dir = glm::normalize(dir);
			const ScalarType normFactor	= glm::length(glm::normalize(dir));
			_offset = off / normFactor;

		}
		else
		{
			_offset = off;
			_dir = dir;
		}
	}

	const PointType direction() const
	{
		return _dir;
	}

	const ScalarType offset() const
	{
		return _offset;
	}

private:
	ScalarType _offset;
	PointType _dir;
};