#pragma once

FORWARD_DECL(TrackBall);

struct TrackUtil
{
	static glm::vec3 mouseCoordToNormalDevCoord(const glm::vec3& p);
	static float distance(const glm::vec3& p1, const glm::vec3& p2);
	static glm::vec3 hitSphere(TrackBall* trackBall, const glm::vec3& p);
	static glm::vec3 hitViewPlane(TrackBall* TrackBall, const glm::vec3& p);
	static bool intersectionPlaneLine(const Plane3<float>& pl, const Line3<float, true>& li, glm::vec3& pt);
};

class TrackMode
{
public:
	virtual void apply(TrackBall* trackBall, const glm::vec3& point) = 0;
	virtual void draw() = 0;
	virtual ~TrackMode() { if (_tb) delete _tb; };
	TrackBall* _tb;
};

class SphereMode : public TrackMode
{
public:
	virtual void apply(TrackBall* trackBall, const glm::vec3& point) override;
	virtual void draw() override;
};

class PanMode : public TrackMode
{
public:
	virtual void apply(TrackBall* trackBall, const glm::vec3& point) override;
	virtual void draw() override;
};