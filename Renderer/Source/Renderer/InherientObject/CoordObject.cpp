#include "stdafx.h"
#include "CoordObject.h"
#include "Application/Application.h"

CoordObject::CoordObject(Ref<TrackBall>& trackBall)
{
	_trackBall = trackBall;
	_cameraScaleRatio = 10;

	const TCHAR* appRootDir = Application::get().applicationDir();


	_model = std::make_unique<Model>("D:\\Projects\\TheRenderer\\Asset\\Model\\Inherient\\arrow3d.obj");

	_m = _trackBall->model();

	int _viewportWidth = Application::getPtr()->window()->width();
	int _viewportHeight = Application::getPtr()->window()->height();

	_p = glm::perspective(45.f, ((float)_viewportWidth / 8 ) / ((float)_viewportHeight / 8), 0.1f, 100.f);

	float cameraDist = trackBall->cameraDist() - 2.f;

	_v = glm::lookAt(
		glm::vec3(cameraDist, cameraDist, cameraDist),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 1.f, 0.f));
}

void CoordObject::draw()
{
	// glViewport(0, 0, 150, 150);
	int viewportData[4] = { 0 };

	glGetIntegeri_v(GL_VIEWPORT,
		0u,
		viewportData);

	int x = viewportData[0];
	int y = viewportData[1];
	int w = viewportData[2];
	int h = viewportData[3];

	glViewport(x, y, w / 8, h / 8);

	_model->draw(_m, _v * _trackBall->track().matrixR(), _p);

	glViewport(x, y, w, h);
}
