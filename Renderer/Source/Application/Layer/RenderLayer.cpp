#include "stdafx.h"
#include "RenderLayer.h"
#include "Application/Application.h"
#include "Application/Window/Window.h"
#include "Application/Event/MouseEvent.h"
#include "Renderer/Scene/Scene.h"
#include "Application/Global/RenderGlobal.h"
#include "Renderer/Buffer/FrameBuffer.h"
#include "Renderer/InherientObject/RenderObject.h"

RenderLayer::RenderLayer()
{
	_trackBall = Scene::get().trackBall();

	_gridObject = std::make_unique<GridObject>();
	_coordObject = std::make_shared<CoordObject>(_trackBall);
	_screenObject = std::make_shared<ScreenObject>();
	_screenObject->initialize();

	_terrain = std::make_unique<TerrainBase>(32, 32, _trackBall);
	_terrain->initialize();

	_teapotEntity = Scene::get().createEntity();
	RenderGlobal::get()._currentEntity = _teapotEntity;
	Scene::get().registry().emplace<MeshComponent>(_teapotEntity, _trackBall, "D:\\Projects\\TheRenderer\\Asset\\Model\\Inherient\\normalplane.fbx");
}

void RenderLayer::onAttach()
{
	// Enable alpha channel
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int width = Application::getPtr()->window()->width();
	int height = Application::getPtr()->window()->height();

	glViewport(0, 0, width, height);
	_frameBuffer = std::make_unique<FrameBuffer>(width, height);
}

void RenderLayer::onDetach()
{

}

void RenderLayer::onUpdate(double deltaTime)
{
    // frame->begin();
	_frameBuffer->bind();
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// frame->render();
	/*
	entt::basic_view view = Scene::get().registry().view<MeshComponent>();
	for (auto entity : view)
	{
		MeshComponent& meshComponent = Scene::get().registry().get<MeshComponent>(entity);
		meshComponent.draw();
	}
	*/
	
	_terrain->draw();

	// frame->end();
	_frameBuffer->unbind();

	glDisable(GL_DEPTH_TEST);
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	_screenObject->_program->use();
	glActiveTexture(GL_TEXTURE0);
	_screenObject->_program->setUniform("screenTexture", 0);
	_screenObject->_program->setUniform("hdrExposure", 1.f);
	_screenObject->_vertexArray->bind();
	glBindTexture(GL_TEXTURE_2D, _frameBuffer->frameTextureHandle());
	glDrawArrays(GL_TRIANGLES, 0, 6);
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
		RenderGlobal::get()._mouseDown = true;
	    _trackBall->mouseDown({(float)event.cursorPos().x(), (float)event.cursorPos().y()});
	    PointD pos = event.cursorPos();

	return true;
}

bool RenderLayer::onMouseRelease(MouseReleaseEvent& event)
{
	int trackMode = RenderGlobal::get()._trackMode;
		RenderGlobal::get()._mouseDown = false;

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