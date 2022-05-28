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
#include "Renderer/Component/CoordObject.h"
#include "Renderer/Model/Model.h"

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

#if 0
	Unique<AxisObject> _xAxisObject;
	Unique<AxisObject> _yAxisObject;
	Unique<AxisObject> _zAxisObject;
#endif
	Unique<GridObject> _gridObject;

	Unique<Object2D> _quad;
	Unique<PerspectiveCamera> _camera;

	PointD _oldPos;
	PointD _deltaPos;

	bool _rotateMode = false;

	
	Unique<Model> _model;

	Unique<FpsCameraController> _controller;
	Ref<TrackBall> _trackBall;
	Ref<CoordObject> _coordObject;

	float _cameraDist;
};
