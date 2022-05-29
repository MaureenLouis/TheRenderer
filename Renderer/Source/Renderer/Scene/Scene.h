#pragma once
#include "Renderer/Light/LightComponent.h"
#include "Renderer/Camera/TrackBall.h"

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

	entt::entity createEntity();

	entt::registry& registry()
	{
		return m_registry;
	}

private:
	entt::registry m_registry;

	Ref<LightComponent> _defaultLight;
	Ref<TrackBall>      _trackBall;
};