#include "stdafx.h"
#include <pathcch.h>

const TCHAR* Config::INI_PATH = TEXT("\\Config\\AppConfig.ini");

void Config::setVideoModes(const GLFWvidmode* videoModes, int count)
{
	assert(videoModes);
	assert(count);

	for (int i = 0; i < count; i++)
	{
		_videoModes.push_back(videoModes[i]);
	}
}

int Config::defaultVideoMode()
{
	return _currentVideoMode;
}

void Config::setDefaultVideoMode(int viewModeIndex)
{
	// Update config properties
	_currentVideoMode = viewModeIndex;
}

Config::Config()
{
	// Find .ini file
	long ret = 0;

	// 获取程序根目录
	TCHAR exePathBuf[MAX_PATH] = { 0 };
	ret = ::GetModuleFileName(NULL, exePathBuf, MAX_PATH);
	ret = ::PathCchRemoveFileSpec(exePathBuf, MAX_PATH);

	if (ret != 0)
	{
		APP_ERROR("Error to find the root directory of the App.");
		return;
	}

	::wsprintf(_configPathBuf, TEXT("%s%s"), exePathBuf, INI_PATH);

	// initialize config properties

	_currentVideoMode = ::GetPrivateProfileInt(TEXT("VideoMode"), TEXT("Resolution"), 0, _configPathBuf);
	_antialaising= ::GetPrivateProfileInt(TEXT("VideoMode"), TEXT("Antialaising"), 4, _configPathBuf);
}

Config::~Config()
{
	// sync with .ini file
	TCHAR buf[128] = { 0 };
	::wsprintf(buf, TEXT("%d"), _currentVideoMode);
	::WritePrivateProfileString(TEXT("VideoMode"), TEXT("Resolution"), buf, _configPathBuf);
	::wsprintf(buf, TEXT("%d"), _antialaising);
	::WritePrivateProfileString(TEXT("VideoMode"), TEXT("Antialaising"), buf, _configPathBuf);
}
