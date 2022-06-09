#include "stdafx.h"
#include "CameraController.h"

CameraController::CameraController(Unique<TargetCamera> camera)
{
	_camera = std::move(camera);
}

void CameraController::mouseMove(const PointF& point)
{
	PointF deltaPos = point - _oldPoint;
	_oldPoint = point;

	float deltaX = deltaPos.x();
	float deltaY = deltaPos.y();

	_camera->updateDirection(deltaX, deltaY);
}
