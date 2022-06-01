#include "stdafx.h"
#include "TextureManager.h"

Ref<Texture2D> TextureManager::registerTexture(const std::string& path)
{
	ManagerType::iterator it = _manager.find(path);
	if (it != _manager.end())
	{
		return it->second;
	}

	Ref<Texture2D> texture = std::make_shared<Texture2D>(path.c_str());
	_manager.insert(std::pair(path, texture));
	return texture;
}
