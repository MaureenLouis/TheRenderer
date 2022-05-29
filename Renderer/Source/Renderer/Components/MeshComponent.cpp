#include "stdafx.h"
#include "MeshComponent.h"

MeshComponent::MeshComponent(Ref<TrackBall>& trackBall)
	: _trackBall(trackBall)
{
	_model = std::make_unique<Model>("D:\\Projects\\TheRenderer\\Asset\\Model\\Inherient\\teapot.obj");

}

void MeshComponent::draw()
{
	glm::mat4& m = _trackBall->model();
	glm::mat4& v = _trackBall->viewMatrix();
	glm::mat4& p = _trackBall->project();

	_model->draw(m * glm::scale(glm::mat4(1.f), glm::vec3(0.2f, 0.2f, 0.2f)), v, p);
}
