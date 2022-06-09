#include "stdafx.h"
#include "LightComponent.h"

LightComponent::LightComponent()
{
	_lightPower = 10.f;
}

LightComponent::LightComponent(Ref<LightComponent>&& lightComponent)
{
	_position = lightComponent->position();
	_lightColor = lightComponent->color();
	_lightPower = lightComponent->lightPower();
}
