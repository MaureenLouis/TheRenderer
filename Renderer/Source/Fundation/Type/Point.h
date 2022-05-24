#pragma once
#include "Fundation/Basics/Selector.h"

template <typename T>
class Point2D
{
	using SelfType = Point2D<T>;
	using ValueType = T;

public:
	constexpr Point2D()
		: _x((ValueType)0), _y((ValueType)0)
	{}

	constexpr Point2D(const T x, const T y)
		: _x(x), _y(y)
	{}

	constexpr Point2D(const SelfType& another)
	{
		_x = another.x();
		_y = another.y();
	}

	constexpr friend SelfType operator-(const SelfType& one, const SelfType& another)
	{
		return SelfType(one.x() - another.x(), one.y() - another.y());
	}

	constexpr friend SelfType operator+(const SelfType& one, const SelfType& another)
	{
		return SelfType(one.x() + another.x(), one.y() + another.y());

	}

	constexpr const T& x() const { return _x; }
	constexpr const T& y() const { return _y; }



private:
	T _x, _y;
};

using PointD = Point2D<double>;
using PointF = Point2D<float>;
using Point  = Point2D<int>;


template <typename ScalarType>
class Point3D
{
	using ValueType = ScalarType;
	using SelfType = Point3D<ScalarType>;

public:
	Point3D()
	{
		SELECT(_data, 0) = 0;
		SELECT(_data, 1) = 0;
		SELECT(_data, 2) = 0;
		SELECT(_padding, 0) = 0;
	}
	Point3D(const Point2D<ValueType>& p2d)
	{
		SELECT(_data, 0) = p2d.x();
		SELECT(_data, 1) = p2d.y();
		SELECT(_data, 2) = 0.f;
		SELECT(_padding, 0) = 0.f;
	}

	Point3D(const ValueType x, const ValueType y, const ValueType z)
	{
		SELECT(_data, 0) = x;
		SELECT(_data, 1) = y;
		SELECT(_data, 2) = z;
		SELECT(_padding, 0) = 0.f;
	}

	SelfType normalized()
	{
		ValueType& x = SELECT(_data, 0);
		ValueType& y = SELECT(_data, 1);
		ValueType& z = SELECT(_data, 2);

		ValueType n = (ValueType)glm::sqrt(SQ(x) +SQ(y) + SQ(z));
		if (n > (ValueType)0)
		{
			x = x / n;
			y = y / n;
			z = z / n;
		}

		return *this;
	}

	ValueType& operator[](unsigned int index)
	{
		assert(index >= 0 && index <= 2);

		return _data[index];
	}

	const ValueType x() const
	{
		return SELECT(_data, 0);
	}

	const ValueType y() const
	{
		return SELECT(_data, 1);
	}

	const ValueType z() const
	{
		return SELECT(_data, 2);
	}

	std::string toString()
	{
		std::stringstream ss;
		ss << "[" << SELECT(_data, 0) << "," << SELECT(_data, 1) << "," << SELECT(_data, 2) << "]\n";
		return ss.str();
	}

private:
	ValueType _data[3];
	ValueType _padding[1];
};

