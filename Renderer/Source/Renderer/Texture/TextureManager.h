#pragma once
#include "Core/OO/Singleton.h"
#include "Renderer/Texture/Texture.h"

class TextureManager
{
	GENERATE_SINGLETON(TextureManager);

private:
	TextureManager() = default;
	~TextureManager() = default;

private:
	std::unordered_map<int, Ref<Texture2D>> _manager;
};