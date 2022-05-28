#pragma once
#include "Renderer/Camera/TrackBall.h"
#include "Renderer/Model/Model.h"


class Teapot 
{
	SELF(Teapot);

public:
	Teapot(Ref<TrackBall>& trackBall);

	void draw();

private:
	Unique<Model>  _model;
	Ref<TrackBall> _trackBall;
};

