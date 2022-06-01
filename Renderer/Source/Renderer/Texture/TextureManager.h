#pragma once
#include "Core/OO/Singleton.h"
#include "Renderer/Texture/Texture.h"

class TextureManager
{
	GENERATE_SINGLETON(TextureManager);
	using ManagerType = std::unordered_map<std::string, Ref<Texture2D>>;

public:
	Ref<Texture2D> registerTexture(const char* path);
private:
	TextureManager() = default;
	~TextureManager() = default;

private:
	ManagerType _manager;
};