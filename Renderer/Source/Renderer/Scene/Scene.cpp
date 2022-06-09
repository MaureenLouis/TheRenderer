#include "stdafx.h"
#include "Scene.h"
#include "renderer/Entity/Entity.h"
#include "Renderer/Components/BasicComponent.h"

Scene::Scene()
{
	_trackBall = std::make_shared<TrackBall>();

	_defaultLight = std::make_shared<LightComponent>();
	_defaultLight->setPosition(glm::vec3(-2.3f, 2.3f, 1.5f));
	_defaultLight->setColor(glm::vec3(1.f, 1.f, 1.f));

	/*
	Entity defaultLightEntity(this);
	defaultLightEntity.addComponent<TagComponent>("DefaultSpotLight");
	defaultLightEntity.addComponent<LightComponent>(std::move(_defaultLight));
	*/
}

entt::entity Scene::createEntity()
{
	return m_registry.create();
}

