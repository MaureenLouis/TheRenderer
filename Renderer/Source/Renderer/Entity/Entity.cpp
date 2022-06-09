#include "stdafx.h"
#include "Entity.h"

Entity::Entity(Scene* scene)
{
	if (!scene)
	{
		ASSERT(false, "scene is nullptr!");
		return;
	}

	EntityHandleType entityHandle = scene->createEntity();
	_entityHandle = entityHandle;
}
