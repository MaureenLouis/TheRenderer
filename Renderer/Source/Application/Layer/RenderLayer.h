#pragma once
#include "Layer.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Renderer/Camera/PerspectiveCamera.h"
#include "Renderer/Component/AxisObject.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Component/2dObject.h"
#include "Renderer/Component/GridObject.h"
#include "Renderer/Camera/FpsCameraController.h"
#include "Renderer/Camera/TrackBall.h"


FORWARD_DECL(MousePressEvent);
FORWARD_DECL(MouseReleaseEvent);
FORWARD_DECL(MouseScrollEvent);
FORWARD_DECL(MouseMoveEvent);


class RenderLayer : public Layer
{
	SELF(RenderLayer);
public:
	RenderLayer();

	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onUpdate(double deltaTime) override;
	virtual void onEvent(Event& event) override;

#if 0
	glm::vec3 getArcballVector(double x, double y);
#endif

private:
	bool onMousePress(MousePressEvent& event);
	bool onMouseRelease(MouseReleaseEvent& event);
	bool onMouseScroll(MouseScrollEvent& event);
	bool onMouseMove(MouseMoveEvent& event);

public:
	glm::mat4 p;
	glm::mat4 v;
	glm::mat4 m;
	glm::mat4 mvp;

	Unique<AxisObject> _xAxisObject;
	Unique<AxisObject> _yAxisObject;
	Unique<AxisObject> _zAxisObject;
	Unique<GridObject> _gridObject;

	Unique<Object2D> _quad;
	Unique<PerspectiveCamera> _camera;

	PointD _oldPos;
	PointD _deltaPos;

	bool _rotateMode = false;



	Unique<FpsCameraController> _controller;
	Unique<TrackBall> _trackBall;


	float _cameraDist;
};
