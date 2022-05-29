#pragma once
#include "Core/OO/Singleton.h"
#include "entt.hpp"

class RenderGlobal
{
	GENERATE_SINGLETON(RenderGlobal);

public:
	/* 0: Rotate mode; 1: Scale mode 2: Pan mode 3: Select mode */
	int _trackMode;   
	bool _mouseDown;
	entt::entity _currentEntity;
private:
	RenderGlobal();

};