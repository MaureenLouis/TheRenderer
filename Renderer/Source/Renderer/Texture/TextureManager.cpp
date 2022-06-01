#include "stdafx.h"
#include "TextureManager.h"

Ref<Texture2D> TextureManager::registerTexture(const char* path)
{
	ManagerType::iterator it = _manager.find(std::string(path));
	if (it != _manager.end())
	{
		return it->second;
	}

	Ref<Texture2D> texture = std::make_shared<Texture2D>(path);
	_manager.insert(std::pair(std::string(path), texture));
	return texture;
}
