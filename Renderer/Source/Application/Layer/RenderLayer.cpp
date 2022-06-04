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

#if 1
	// FBO
	unsigned int& _fbo = RenderGlobal::get()._fbo;
	glGenFramebuffers(1, &_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

	// Texture attachment
	unsigned int& renderTexture = RenderGlobal::get()._renderTexture;
	glGenTextures(1, &renderTexture);
	glBindTexture(GL_TEXTURE_2D, renderTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTexture, 0);

	// Depth buffer attachment
	glGenTextures(1, &_depthTexture);
	glBindTexture(GL_TEXTURE_2D, _depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthTexture, 0);

	// Render buffer attachment
	glGenRenderbuffers(1, &_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		APP_INFO("FBO complete!");
	}
#endif
}

void RenderLayer::onDetach()
{
#if 1
	glDisable(GL_DEPTH_TEST);

	unsigned int& fbo = RenderGlobal::get()._fbo;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &fbo);
#endif
}

void RenderLayer::onUpdate(double deltaTime)
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, RenderGlobal::get()._fbo);
	entt::basic_view view = Scene::get().registry().view<MeshComponent>();
	for (auto entity : view)
	{
		MeshComponent& meshComponent = Scene::get().registry().get<MeshComponent>(entity);
		meshComponent.draw();
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	glDisable(GL_DEPTH_TEST);
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);



	_screenObject->_program->use();
	glActiveTexture(GL_TEXTURE0);
	_screenObject->_program->setUniform("screenTexture", 0);

	_screenObject->_vertexArray->bind();
	glBindTexture(GL_TEXTURE_2D, RenderGlobal::get()._renderTexture);
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