#pragma once
#include "Renderer/Camera/View.h"

FORWARD_DECL(TrackMode);
FORWARD_DECL(RenderLayer);

class Similarity
{
public:
	float     _scale;
	glm::quat _rot;
	glm::vec3 _tra;        // Move

public:
	void setIdentity()
	{
		_rot = glm::angleAxis(glm::degrees(0.f), glm::vec3(0.f, 0.f, 0.f));

		// _rot = glm::quat(0.f, 0.f, 0.f, 0.f);
		_tra = glm::vec3(0.f);
		_scale = 1.f;
	}

	glm::mat4 matrix()
	{
		// Translate * scale * rot;
		glm::mat4 rotate = glm::toMat4(_rot);
		glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(_scale, _scale, _scale));
		glm::mat4 translate = glm::translate(glm::mat4(1.f), _tra);

		return scale * rotate * translate;
	}
};

class Transform
{
protected:
	glm::vec3  _center;
	Similarity _track;
	float      _radius;
protected:
	Transform()
	{
		_track.setIdentity();
		_radius = 1.f;
		_center = glm::vec3(0.f);
	}

public:
	const glm::vec3& center() const
	{
		return _center;
	}

	const float radius() const
	{
		return _radius;
	}

	Similarity& track()
	{
		return _track;
	}

};

class TrackBall : public Transform
{
	SELF(TrackBall);
	friend class SphereMode;
public:
	TrackBall();
	~TrackBall();

	void mouseDown(const PointF& point);
	void mouseMove(const PointF& point);
	void mouseScroll(RenderLayer* layer, float yOffset);

	void draw();

	const glm::vec3 lastPoint() const
	{
		return _lastPoint;
	}



private:
	void setDefaultMapping();
	void setCurrentAction();

private:
	TrackMode* _trackMode;

	Similarity _lastTrack;

	glm::vec3 _lastPoint;

	// View      _camera;
};