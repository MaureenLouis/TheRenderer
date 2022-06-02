#pragma once
#include "Core/OO/Singleton.h"


class Config
{
	GENERATE_SINGLETON(Config);

public:
	enum class PolygonMode : uint8_t
	{
		Fill = 0, Line = 1
	};


	using VideoModes = std::vector<GLFWvidmode>;
	void setVideoModes(const GLFWvidmode* videoModes, int count);
	
	const VideoModes& videoModes()const {
		return _videoModes;
	}

	int defaultVideoMode();
	void setDefaultVideoMode(int viewModeIndex);
	int& antiAlaisingLevel() { return _antialaising; }

	float _mouseSensitivity = 1.f;
	int   _patchVertices;
	int   _polygonMode;    // 0: fill mode 1: line mode

private:
	Config();
	~Config();
	
	int _antialaising;
	int _currentVideoMode;
	std::vector<GLFWvidmode> _videoModes;

	TCHAR _configPathBuf[MAX_PATH] = { 0 };
	static const TCHAR* INI_PATH;
};