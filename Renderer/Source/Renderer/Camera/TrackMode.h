#pragma once

FORWARD_DECL(TrackBall);

struct TrackUtil
{
	static float distance(const glm::vec3& p1, const glm::vec3& p2);
	static glm::vec3 hitSphere(TrackBall* trackBall, const glm::vec3& p);
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