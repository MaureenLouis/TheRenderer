#include "stdafx.h"
#include "Scene.h"

Scene::Scene()
{
	_defaultLight = std::make_shared<LightComponent>();
	_defaultLight->setPosition(glm::vec3(3.f, 3.f, 3.f));
	_defaultLight->setColor(glm::vec3(1.f, 1.f, 1.f));
}

