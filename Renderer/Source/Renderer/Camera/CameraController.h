#pragma once
#include "TargetCamera.h"

class CameraController
{
public:
	CameraController(Unique<TargetCamera> camera);

	void mouseMove(const PointF& point);

private:
	Unique<TargetCamera> _camera;
	PointF         _oldPoint;
};