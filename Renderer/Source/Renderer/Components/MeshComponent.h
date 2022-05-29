#pragma once
#include "Renderer/Camera/TrackBall.h"
#include "Fundation/Model/Model.h"

class MeshComponent 
{
	SELF(MeshComponent);
public:
	MeshComponent(Ref<TrackBall>& trackBall);

	void draw();

private:
	Unique<Model>  _model;
	Ref<TrackBall> _trackBall;
};

