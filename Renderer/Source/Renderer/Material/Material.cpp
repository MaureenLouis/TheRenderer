#include "stdafx.h"
#include "Material.h"

void Material::setMaterialColor(Material::Type type, const aiColor4D& color)
{
	_diffuseColor = glm::vec4(color.r, color.g, color.b, color.a);
}

glm::vec4 Material::materialColor(Material::Type type)
{
	switch (type.value())
	{
	case (Type::DiffuseColor):
		{
		    return _diffuseColor;
		}
		break;
	default:
		ASSERT(false, "Unknown color type");
	}
}
