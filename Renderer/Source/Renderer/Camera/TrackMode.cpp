#include "stdafx.h"
#include "TrackMode.h"
#include "TrackBall.h"
#include "Application/Application.h"
#include "Application/Global/Config.h"

void SphereMode::apply(TrackBall* trackBall, const glm::vec3& point)
{
	glm::vec3 hitOld = TrackUtil::hitSphere(trackBall, trackBall->lastPoint());
	glm::vec3 hitNew = TrackUtil::hitSphere(trackBall, point);
	const glm::vec3& center = trackBall->center();
	
	glm::vec3 axis = glm::normalize(glm::cross((hitNew - center), (hitOld - center)));


	float phi = TrackUtil::distance(hitNew, hitOld) / trackBall->_radius;
#if 0
    printf("%lf\n", glm::degrees(phi));
#endif
	if (phi != 0.f)
	{
		//phi = 0.003f;
	    trackBall->_track._rot = glm::angleAxis(glm::degrees(-phi), axis) * trackBall->_lastTrack._rot;
	}

}

void DrawPlaneHandle()
{
	float r = 1.0;
	float dr = r / 10.0f;

	glBegin(GL_LINE_STRIP);
	glVertex3f(+r + dr, +r, 0.0);
	glVertex3f(+r, +r + dr, 0.0);
	glVertex3f(+r - dr, +r, 0.0);
	glVertex3f(+r, +r - dr, 0.0);
	glVertex3f(+r + dr, +r, 0.0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(-r + dr, -r, 0.0);
	glVertex3f(-r, -r + dr, 0.0);
	glVertex3f(-r - dr, -r, 0.0);
	glVertex3f(-r, -r - dr, 0.0);
	glVertex3f(-r + dr, -r, 0.0);
	glEnd();
}


void DrawCircle(bool planehandle = true)
{
	int nside = 64;
	const double pi2 = 3.14159265 * 2.0;
	glBegin(GL_LINE_LOOP);
	for (double i = 0; i < nside; i++) {
		glNormal3d(cos(i * pi2 / nside), sin(i * pi2 / nside), 0.0);
		glVertex3d(cos(i * pi2 / nside), sin(i * pi2 / nside), 0.0);
	}
	glEnd();
	if (planehandle)
		DrawPlaneHandle();
}

void SphereMode::draw()
{
	glPushAttrib(GL_TRANSFORM_BIT | GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT | GL_LINE_BIT | GL_CURRENT_BIT | GL_LIGHTING_BIT);
	glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	glDepthMask(GL_FALSE);

	glLoadIdentity();

	glm::vec3 center = _tb->center();
	glTranslatef(center.x, center.y, center.z);
	float p = _tb->radius() / _tb->_track._scale;
	glScalef(p, p, p);


	float amb[4] = { .35f, .35f, .35f, 1.0f };
	float col[4] = { .5f, .5f, .8f, 1.0f };
	glEnable(GL_LINE_SMOOTH);
	if (true)
		glLineWidth(2);
	else
		glLineWidth(1);
	glDisable(GL_COLOR_MATERIAL); // has to be disabled, it is used by wrapper to draw meshes, and prevent direct material setting, used here

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4ui(255, 0, 0, 255);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, amb);

	col[0] = .40f; col[1] = .40f; col[2] = .85f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);
	DrawCircle(true);

	glRotatef(90, 1, 0, 0);
	col[0] = .40f; col[1] = .85f; col[2] = .40f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);
	DrawCircle(true);

	glRotatef(90, 0, 1, 0);
	col[0] = .85f; col[1] = .40f; col[2] = .40f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col);
	DrawCircle(true);

	// glPopMatrix();
	glPopAttrib();
}

float TrackUtil::distance(const glm::vec3& p1, const glm::vec3& p2)
{
	glm::vec3 sub = (p1 - p2);
	return glm::sqrt(sub.x * sub.x + sub.y * sub.y + sub.z * sub.z);
}

glm::vec3 TrackUtil::mouseCoordToNormalDevCoord(const glm::vec3& p)
{
	float width = (float)Application::get().window()->width();
	float height = (float)Application::get().window()->height();


	glm::vec3 mousePoint = glm::vec3(p.x / width * 2.f - 1.f, p.y / height * 2.f - 1.f, 0.f);
	mousePoint.y = -mousePoint.y;

	return mousePoint;
}


glm::vec3 TrackUtil::hitSphere(TrackBall* trackBall, const glm::vec3& p)
{
	glm::vec3 center = trackBall->center();

	glm::vec3 mousePoint = TrackUtil::mouseCoordToNormalDevCoord(p);

	float opSquared = (float)mousePoint.x * (float)mousePoint.x + (float)mousePoint.y * (float)mousePoint.y;

	if (opSquared <= 1.f)
	{
		mousePoint.z = glm::sqrt(1.f - opSquared);
	}
	else
	{
		mousePoint = glm::normalize(p);
	}

	return mousePoint;
}

glm::vec3 TrackUtil::hitViewPlane(TrackBall* trackBall, const glm::vec3& p)
{
	Plane3<float> vp = trackBall->getViewPlane();
	Line3<float, true> ln = trackBall->viewLineFromWindow(p);


	glm::vec3 ponVp;
	(void)TrackUtil::intersectionPlaneLine(vp, ln, ponVp);

	return ponVp;
}

bool TrackUtil::intersectionPlaneLine(const Plane3<float>& pl, const Line3<float, true>& li, glm::vec3& pt)
{
	const float epsilon = float(1e-8);



	float k = glm::dot(pl.direction(), li.direction());


	if ((k > -epsilon) && (k < epsilon))
	{
		return false;
	}

	float r = (
		pl.offset() - glm::dot(pl.direction(), li.origin())
		) / k;

	pt = li.origin() + li.direction() * r;

	return true;
}

void PanMode::apply(TrackBall* trackBall, const glm::vec3& point)
{
	glm::vec3 hitOld = TrackUtil::hitViewPlane(trackBall, trackBall->lastPoint());
	glm::vec3 hitNew = TrackUtil::hitViewPlane(trackBall, point);
	glm::vec3 hitDelta = hitNew - hitOld;

	float mouseSensitivity = Config::get()._mouseSensitivity;
	hitDelta = hitDelta * mouseSensitivity * 5.f;

	trackBall->translate(hitDelta);
}

void PanMode::draw()
{

}
