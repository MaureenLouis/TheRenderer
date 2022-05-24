#pragma once



template <typename ScalarType, bool Normal = false>
class Line3
{
	using ValueType = ScalarType;
	using PointType = Point3D<ScalarType>;
	using SelfType = Line3<ScalarType>;


private:
	PointType _ori;
	PointType _dir;
};