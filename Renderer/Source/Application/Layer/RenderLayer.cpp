#include "stdafx.h"
#include "RenderLayer.h"
#include "Application/Application.h"
#include "Application/Window/Window.h"
#include "Application/Event/MouseEvent.h"

RenderLayer::RenderLayer()
{
	_quad = std::make_unique<Object2D>();

	_xAxisObject = std::make_unique<AxisObject>(AxisObject::AxisType::xAxis);
	_xAxisObject->setLineWidth(2.5f);
	_xAxisObject->setScaled(0.1f);
	_yAxisObject = std::make_unique<AxisObject>(AxisObject::AxisType::yAxis);
	_yAxisObject->setLineWidth(2.5f);
	_yAxisObject->setScaled(0.1f);
	_zAxisObject = std::make_unique<AxisObject>(AxisObject::AxisType::zAxis);
	_zAxisObject->setLineWidth(2.5f);
	_zAxisObject->setScaled(0.1f);


	//_camera = std::make_unique<PerspectiveCamera>(width, height, glm::vec3(2.f, 1.f, 2.f));

	_trackBall = std::make_unique<TrackBall>();
	m = _trackBall->model();

	p = _trackBall->project();

	_cameraDist = 1.75f / glm::tan(glm::radians(45.f * 0.5f));
}

void RenderLayer::onAttach()
{
	glEnable(GL_DEPTH_TEST);

	int width = Application::getPtr()->window()->width();
	int height = Application::getPtr()->window()->height();

	glViewport(0, 0, width, height);
}

void RenderLayer::onDetach()
{
	glDisable(GL_DEPTH_TEST);
}

void RenderLayer::onUpdate(double deltaTime)
{

	static double runningTime = 0.0;
	// static glm::vec3 pos = _camera->position();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// v = _controller->getViewMatrix();

	// v = _trackBall->track().matrix();


	v = glm::lookAt(
		glm::vec3(_cameraDist,  _cameraDist, _cameraDist),
		glm::vec3(0.f, 0.f, 0.f), 
		glm::vec3(0.f, 1.f, 0.f));

	v = v * _trackBall->track().matrix();

	mvp = p *  v  * m;


	// 绘制图形
	int drawId = 0;
	_quad->shader()->setUniform("mvp", mvp/* * glm::rotate(glm::mat4(1.f), (float)runningTime * 50.f, glm::vec3(0.f, 1.f, 0.f))*/);
	_quad->draw();

	// pick

	// 绘制坐标轴
	_xAxisObject->shader()->setUniform("mvp", mvp);
	_xAxisObject->draw();

	_yAxisObject->shader()->setUniform("mvp", mvp);
	_yAxisObject->draw();

	_zAxisObject->shader()->setUniform("mvp", mvp);
	_zAxisObject->draw();

#if 0
	_trackBall->draw();
#endif

	// 刷新相机位置
#if 0
	float deltaHeight = std::sin(runningTime + deltaTime) - std::sin(runningTime);
	pos += glm::vec3(0.f, deltaHeight* 5.f, 0.f);
	runningTime += deltaTime;
	_camera->setPosition(pos);
#endif
}

void RenderLayer::onEvent(Event& event)
{
	EventDispatcher d(event);

	d.dispatch<MousePressEvent>(EVENT_CALLBACK(&Self::onMousePress));
	d.dispatch<MouseReleaseEvent>(EVENT_CALLBACK(&Self::onMouseRelease));
	d.dispatch<MouseScrollEvent>(EVENT_CALLBACK (&Self::onMouseScroll));
	d.dispatch<MouseMoveEvent>(EVENT_CALLBACK(&Self::onMouseMove));
}


bool RenderLayer::onMousePress(MousePressEvent& event)
{
	int trackMode = RenderGlobal::get()._trackMode;
	//if (trackMode == 0 || trackMode == 2)
	//{
		RenderGlobal::get()._mouseDown = true;
	    _trackBall->mouseDown({(float)event.cursorPos().x(), (float)event.cursorPos().y()});
	    PointD pos = event.cursorPos();
	//}

	return true;
}

bool RenderLayer::onMouseRelease(MouseReleaseEvent& event)
{
	int trackMode = RenderGlobal::get()._trackMode;
	//if (trackMode == 0)
	//{
		RenderGlobal::get()._mouseDown = false;
	//}

	return true;
}

bool RenderLayer::onMouseMove(MouseMoveEvent& event)
{
	int trackMode = RenderGlobal::get()._trackMode;
	bool mouseDown = RenderGlobal::get()._mouseDown;

	if (mouseDown && trackMode != 3)
	{
		_trackBall->mouseMove({ (float)event.cursorPos().x(), (float)event.cursorPos().y() }, trackMode);
	}

	return true;
}

bool RenderLayer::onMouseScroll(MouseScrollEvent& event)
{
	double yOffset = event.yOffset();
	_trackBall->mouseScroll(this, yOffset);


	return true;
}