#pragma once
#include "Renderer/Light/LightComponent.h"

class Scene
{
	GENERATE_SINGLETON(Scene);

private:
	Scene();

public:


	Ref<LightComponent>& defaultLight()
	{ return _defaultLight; }

private:
	entt::registry m_registry;

	Ref<LightComponent> _defaultLight;
};