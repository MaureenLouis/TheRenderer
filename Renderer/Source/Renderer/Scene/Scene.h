#pragma once

class Scene
{
public:
	Scene();
	~Scene();

private:
	entt::registry m_registry;
};