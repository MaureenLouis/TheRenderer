#pragma once
#include "Layer.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Renderer/Camera/PerspectiveCamera.h"
#include "Renderer/Component/AxisObject.h"
#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Component/2dObject.h"
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

	glm::vec3 getArcballVector(double x, double y);

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

	Unique<Object2D> _quad;
	Unique<PerspectiveCamera> _camera;

	PointD _oldPos;
	PointD _deltaPos;

	float _theta = 0.f;
    float _phi = 0.f;
	float _rho = 5.f;

	double _sensitivity = 0.3;

	bool _rotateMode = false;

	float _up = 1.0f;

#if 0
	glm::vec3 _pos = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 _target = glm::vec3(0.f, 0.f, 1.f);
	glm::vec3 _up = glm::vec3(0.f, 1.f, 0.f);
#endif
	Unique<FpsCameraController> _controller;
	Unique<TrackBall> _trackBall;

	int _viewport[4];

	float _cameraDist;
};
