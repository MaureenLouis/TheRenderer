#include "stdafx.h"
#include "TrackBall.h"
#include "TrackMode.h"
#include "Application/Layer/RenderLayer.h"
#include "Application/Application.h"

TrackBall::TrackBall()
{
	Self::setDefaultMapping();
}

TrackBall::~TrackBall()
{
	if ( _trackMode[0] != nullptr)
	{
		delete _trackMode[0];
	}

	if (_trackMode[2] != nullptr)
	{
		delete _trackMode[2];
	}
}

void TrackBall::mouseDown(const PointF& point)
{
	_lastPoint = glm::vec3(point.x(), point.y(), 0.f);
	_lastTrack = track();
}

void TrackBall::mouseMove(const PointF& point, int trackModeId)
{
	glm::vec3 curPoint = glm::vec3(point.x(), point.y(), 0.f);
	_trackMode[trackModeId]->apply(this, curPoint);

	_lastPoint = curPoint;
	_lastTrack = track();
}

void TrackBall::mouseScroll(RenderLayer* layer, float yOffset)
{
	_track._scale = _track._scale * glm::pow(1.5f, -yOffset / 10.f);

	_lastPoint = glm::vec3(0.f, 0.f, -1.f);
	_lastTrack = track();
}

void TrackBall::draw()
{
	// _trackMode[0]->draw();
}

void TrackBall::translate(const glm::vec3& pos)
{
	glm::quat irot = _track._rot;
	irot = glm::inverse(irot);
	_track._tra = _lastTrack._tra + glm::rotate(irot, pos) / _track._scale;
}

Plane3<float> TrackBall::getViewPlane()
{
	glm::vec3 vp = viewPoint();


	Plane3<float> pl;
	glm::vec3 plNorm = vp - _center;
	if (plNorm != glm::vec3(0.f, 0.f, 0.f))
	{
	    plNorm = glm::normalize(plNorm);
	}

	pl.set(glm::dot(plNorm, _center), plNorm);

	return pl;
}
Line3<float, true> TrackBall::viewLineFromWindow(const glm::vec3& p)
{
	Line3<float> ln;

	glm::vec3 vp = viewPoint();
	glm::vec3 pp = unProject(glm::vec3(p.x, p.y, 0));



	ln.setOrigin(vp);
	ln.setDirection(pp - vp);

	return ln.normalize();
}
glm::vec3 TrackBall::unProject(const glm::vec3& p)
{
	glm::vec3 s = TrackUtil::mouseCoordToNormalDevCoord(p);
	glm::vec4 s4 = glm::inverse(_project * _model) * glm::vec4(s.x, s.y, s.z, 0);

	s = glm::vec3(s4.x, s4.y, s4.z);

	return s;
}

void TrackBall::setDefaultMapping()
{
	_trackMode[0] = new SphereMode;
	_trackMode[0]->_tb = this;

	_trackMode[2] = new PanMode;
	_trackMode[2]->_tb = this;
}

void TrackBall::setCurrentAction()
{
}

Transform::Transform()
{
	_track.setIdentity();
	_radius = 1.f;
	_center = glm::vec3(0.f);

	int width = Application::getPtr()->window()->width();
	int height = Application::getPtr()->window()->height();
	_project = glm::perspective(45.f, (float)width / (float)height, 0.1f, 100.f);

	_cameraDist = 1.75f / glm::tan(glm::radians(45.f * 0.5f));

}

glm::mat4 Transform::viewMatrix()
{
	glm::mat4 lookAt = glm::lookAt(
		glm::vec3(_cameraDist, _cameraDist, _cameraDist),
		glm::vec3(0.f, 0.f, 0.f),
		glm::vec3(0.f, 1.f, 0.f)
	);

	return lookAt * _track.matrixSRT();
}

void Similarity::setIdentity()
{
	_rot = glm::angleAxis(glm::degrees(0.f), glm::vec3(0.f, 0.f, 0.f));

	// _rot = glm::quat(0.f, 0.f, 0.f, 0.f);
	_tra = glm::vec3(0.f);
	_scale = 1.f;
}

glm::mat4 Similarity::matrixSRT()
{
	// Translate * scale * rot;
	glm::mat4 rotate = glm::toMat4(_rot);
	glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(_scale, _scale, _scale));
	glm::mat4 translate = glm::translate(glm::mat4(1.f), _tra);

	return scale * rotate * translate;
}

glm::mat4 Similarity::matrixR()
{
	glm::mat4 rotate = glm::toMat4(_rot);
	return rotate;
}
