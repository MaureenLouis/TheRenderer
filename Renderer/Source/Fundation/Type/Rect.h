#pragma once

template <typename T = int>
class Rect
{
	using ValueType = T;
	using SelfType = Rect<T>;
public:
	Rect(ValueType x, ValueType y, ValueType width, ValueType height)
		: _x(x), y(y), _width(width), _height(height)
	{

	}

	Rect(const int* viewport)
	{
		if (viewport != nullptr)
		{
			_x = viewport[0];
			_y = viewport[1];
			_width = viewport[2];
			_height = viewport[3];
		}
	}

	std::string toString()
	{
		std::stringstream ss;
		ss << "[" << _x << "," << _y << "," << _width << "," << _height << "]\n";
		return ss.str();
	}

	const ValueType x() const
	{
		return _x;
	}

	const ValueType y() const
	{
		return _y;
	}

	const ValueType w() const
	{
		return _width;
	}

	const ValueType h() const
	{
		return _height;
	}

private:
	ValueType _x, _y, _width, _height;
};