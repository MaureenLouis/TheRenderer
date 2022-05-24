#pragma once
#include "Core/OO/Singleton.h"


class Config
{
	GENERATE_SINGLETON(Config);

public:
	using VideoModes = std::vector<GLFWvidmode>;
	void setVideoModes(const GLFWvidmode* videoModes, int count);
	
	const VideoModes& videoModes()const {
		return _videoModes;
	}

	int defaultVideoMode();
	void setDefaultVideoMode(int viewModeIndex);

private:
	Config();
	~Config();
	
	int _currentVideoMode;
	std::vector<GLFWvidmode> _videoModes;

	TCHAR _configPathBuf[MAX_PATH] = { 0 };
	static const TCHAR* INI_PATH;
};