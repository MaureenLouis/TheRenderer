#include "stdafx.h"
#include "RenderLayer.h"
#include "Application/Application.h"
#include "Application/Window/Window.h"
#include "Application/Event/MouseEvent.h"
#include "Renderer/Scene/Scene.h"
#include "Application/Global/RenderGlobal.h"

static void constructCallBack()
{
	APP_INFO("Hi!");
}

RenderLayer::RenderLayer()
{
	_trackBall = Scene::get().trackBall();

	_gridObject = std::make_unique<GridObject>();
	_coordObject = std::make_shared<CoordObject>(_trackBall);
	// _teapot = std::make_shared<MeshComponent>(_trackBall);
    
	// Scene::get().registerEntity<MeshComponent>(_teapotEntity);

	 _teapotEntity = Scene::get().createEntity();
	 RenderGlobal::get()._currentEntity = _teapotEntity;
	//Scene::get().registry().on_construct<MeshComponent>().connect<&constructCallBack>();
	Scene::get().registry().emplace<MeshComponent>(_teapotEntity, _trackBall);

}

void RenderLayer::onAttach()
{
	glEnable(GL_DEPTH_TEST);

    // Enable alpha channel
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#if 0
	_gridObject->shader()->setUniform("m", m);
	_gridObject->shader()->setUniform("v", v);
	_gridObject->shader()->setUniform("p", p);
	_gridObject->draw();
#endif


	// _quad->draw();
#if 0
	MeshComponent& meshComponent = Scene::get().registry().get<MeshComponent>(_teapotEntity);
	meshComponent.draw();
#endif

	entt::basic_view view = Scene::get().registry().view<MeshComponent>();
	for (auto entity : view)
	{
		MeshComponent& meshComponent = Scene::get().registry().get<MeshComponent>(entity);
		meshComponent.draw();
	}

	_coordObject->draw();

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