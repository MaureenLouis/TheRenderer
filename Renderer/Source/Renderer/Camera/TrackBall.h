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
	void setIdentity();
	glm::mat4 matrixSRT();
	glm::mat4 matrixR();
};

class Transform
{
protected:
	glm::vec3  _center;
	glm::mat4  _model;
	glm::mat4  _project;
	glm::mat4  _view;
	Similarity _track;
	float      _radius;
	float      _cameraDist;

protected:
	Transform();

public:
	const glm::vec3& center() const
	{ return _center; }

	const float radius() const
	{ return _radius;  }

	Similarity& track()
	{ return _track; }

	glm::mat4& model()
	{ return _model; }

	glm::mat4 project()
	{ return _project; }

	glm::vec3 viewPoint()
	{ return glm::vec3(glm::inverse(_model) * glm::vec4(-4.f, -4.f, -4.f, 0.f)); }

	float cameraDist()
	{ return  _cameraDist; }

	glm::mat4 viewMatrix();
};

class TrackBall : public Transform
{
	SELF(TrackBall);
	friend class SphereMode;
public:
	TrackBall();
	~TrackBall();

	void mouseDown(const PointF& point);
	void mouseMove(const PointF& point, int trackModeId);
	void mouseScroll(RenderLayer* layer, float yOffset);

	void draw();

	void translate(const glm::vec3& pos);

	Plane3<float> getViewPlane();

	Line3<float, true> viewLineFromWindow(const glm::vec3& p);

	glm::vec3 unProject(const glm::vec3& p);

	const glm::vec3 lastPoint() const
	{
		return _lastPoint;
	}

	Similarity& lastTrack()
	{
		return _lastTrack;
	}

private:
	void setDefaultMapping();
	void setCurrentAction();

private:
	TrackMode* _trackMode[3];

	Similarity _lastTrack;

	glm::vec3 _lastPoint;

}; 