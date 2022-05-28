#pragma once
#include "Renderer/Camera/TrackBall.h"
#include "Renderer/Model/Model.h"

class CoordObject
{
	SELF(CoordObject);

public:
	CoordObject(Ref<TrackBall>& trackBall);

	void draw();

private:
	Unique<Model>  _model;
	Ref<TrackBall> _trackBall;

	glm::mat4 _m;
	glm::mat4 _p;
	glm::mat4 _v;

	int _cameraScaleRatio;
	int _viewportWidth;
	int _viewportHeight;
};