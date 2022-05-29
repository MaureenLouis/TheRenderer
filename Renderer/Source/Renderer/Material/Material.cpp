#include "stdafx.h"
#include "Material.h"

void Material::setMaterialColor(Material::Type type, const aiColor4D& color)
{
	switch (type.value())
	{
	case (Type::DiffuseColor):
	{
	    _diffuseColor = glm::vec4(color.r, color.g, color.b, color.a);
	}
	break;
	case (Type::SpecularColor):
	{
		_specularColor = glm::vec4(color.r, color.g, color.b, color.a);
	}
	break;
	default:
		ASSERT(false, "Unknown color type");
	}
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
	case (Type::SpecularColor):
    	{
		    return _specularColor;
	    }
		break;
	default:
		ASSERT(false, "Unknown color type");
	}
}

void Material::setMaterialStrength(Material::Type type, float value)
{
	switch (type.value())
	{
	case (Type::ShinenessStrength):
		{
			_shinenessStrength = value;
		}
		break;

		default:
			ASSERT(false, "Unknown value type");
	}
}

float Material::materialStrength(Material::Type type)
{
	switch (type.value())
	{
	case (Type::ShinenessStrength):
	{
		return _shinenessStrength;
	}
	break;
	default:
		ASSERT(false, "Unknown color type");
	}
}
