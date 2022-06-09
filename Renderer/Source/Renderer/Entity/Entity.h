#pragma once
#include "Renderer/Scene/Scene.h"

/*
 * @brief: An entity represents a general-purpose object. 
 *         It only consists of a unique ID. Implementations 
 *         typically use a plain integer for this.
 * 
 */
class Entity
{
	using EntityHandleType = entt::entity;
public:
	Entity(Scene* scene);

	template <typename ComponentType>
	bool hasComponent()
	{
		return _scene->registry().any_of<ComponentType>(_entityHandle);
	}

	template<typename ComponentType, typename ...Args>
	ComponentType& addComponent(Args&&... args)
	{
		return _scene->registry().emplace<ComponentType>(_entityHandle, std::forward<Args>(args)...);
	}

	template<typename ComponentType>
	ComponentType& getComponent()
	{
		return _scene->registry().get<ComponentType>(_entityHandle);
	}

	template <typename ComponentType>
	void removeComponent()
	{
		_scene->registry().remove<ComponentType>(_entityHandle);
	}

	const EntityHandleType handle() const
	{
		return _entityHandle;
	}

private:
	EntityHandleType   _entityHandle;
	Scene*       _scene;
};

