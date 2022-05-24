#pragma once
#include "Core/OO/Interface.h"
#include "Core/OO/Semantics.h"

FORWARD_DECL(Event);

Interface(Layer)
{
	Pure(void onAttach());
	Pure(void onDetach());
	Pure(void onUpdate(double deltaTime));
	Pure(void onEvent(Event& event));
};