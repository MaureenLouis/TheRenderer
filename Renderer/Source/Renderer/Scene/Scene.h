#pragma once
#include "Renderer/Light/LightComponent.h"
#include "Renderer/Camera/TrackBall.h"
#include "Renderer/Components/MeshComponent.h"

class Scene
{
	GENERATE_SINGLETON(Scene);

private:
	Scene();

public:
	Ref<TrackBall>& trackBall()
	{ return _trackBall; }

	Ref<LightComponent>& defaultLight()
	{ return _defaultLight; }

	entt::registry& registry()
	{ return m_registry; }

	entt::entity createEntity();

	template <typename Component>
	Component& getComponent(const entt::entity& handle)
	{
		Component& component = m_registry.get<Component>(handle);
		return component;
	}
	
private:
	entt::registry m_registry;

	Ref<LightComponent> _defaultLight;
	Ref<TrackBall>      _trackBall;
};