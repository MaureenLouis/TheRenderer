#include "stdafx.h"
#include "Scene.h"

Scene::Scene()
{
	_trackBall = std::make_shared<TrackBall>();


	_defaultLight = std::make_shared<LightComponent>();
	_defaultLight->setPosition(glm::vec3(-3.f, -3.f, -3.f));
	_defaultLight->setColor(glm::vec3(1.f, 1.f, 1.f));
}

entt::entity Scene::createEntity()
{
	return m_registry.create();
}

