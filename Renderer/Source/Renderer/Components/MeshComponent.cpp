#include "stdafx.h"
#include "MeshComponent.h"

MeshComponent::MeshComponent(Ref<TrackBall>& trackBall, const char* path)
	: _trackBall(trackBall)
{
	_model = std::make_unique<Model>(path);
}

void MeshComponent::draw()
{
	glm::mat4& m = _trackBall->model();
	glm::mat4& v = _trackBall->viewMatrix();
	glm::mat4& p = _trackBall->project();

	_model->draw(m * glm::scale(glm::mat4(1.f), glm::vec3(0.2f, 0.2f, 0.2f)), v, p);
}

std::vector<Ref<Material>> MeshComponent::materials()
{
	std::vector<Ref<Material>> ret;

	for (auto mesh : _model->_meshes)
	{
		Ref<Material> material = mesh->_material;
		ret.push_back(material);
	}

	return ret;
}

