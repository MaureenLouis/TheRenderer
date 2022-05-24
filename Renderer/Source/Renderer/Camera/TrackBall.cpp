#include "stdafx.h"
#include "TrackBall.h"
#include "TrackMode.h"
#include "Application/Layer/RenderLayer.h"

TrackBall::TrackBall()
{
	Self::setDefaultMapping();
	_trackMode->_tb = this;

}

TrackBall::~TrackBall()
{
	delete _trackMode;
}

void TrackBall::mouseDown(const PointF& point)
{

	_lastPoint = glm::vec3(point.x(), point.y(), 0.f);
	_lastTrack = track();
}

void TrackBall::mouseMove(const PointF& point)
{
	glm::vec3 curPoint = glm::vec3(point.x(), point.y(), 0.f);
	_trackMode->apply(this, curPoint);
	_lastPoint = curPoint;
	_lastTrack = track();
}

void TrackBall::mouseScroll(RenderLayer* layer, float yOffset)
{
	_track._scale = _track._scale * glm::pow(1.5f, -yOffset / 10.f);
	printf("%lf\n", _track._scale);
#if 0
	glm::vec4 vp = glm::inverse(layer->m) * glm::vec4(0.f, 0.f, 0.f, 0.f);
	glm::vec3 glNorm = glm::vec3(vp.x, vp.y, vp.z) - center();
	glNorm = glm::normalize(glNorm);

	glm::vec3 dir = glNorm * yOffset / 12.f * (-1.f);

	glm::quat irot = _track._rot;
	irot = glm::inverse(irot);
	_track._tra = _lastTrack._tra + glm::rotate(irot, dir) / _track._scale;

#endif
	_lastPoint = glm::vec3(0.f, 0.f, -1.f);
	_lastTrack = track();
}

void TrackBall::draw()
{
	_trackMode->draw();
}

void TrackBall::setDefaultMapping()
{
	_trackMode = new SphereMode;
}

void TrackBall::setCurrentAction()
{
}
