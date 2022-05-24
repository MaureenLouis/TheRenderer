#include "stdafx.h"
#include "Log.h"

Ref<spdlog::logger> Log::s_appLogger;
Ref<spdlog::logger> Log::s_coreLogger;

void Log::init()
{
	spdlog::set_pattern("[%n][%^%l %$] %v");

	// core logger
	s_coreLogger = spdlog::stdout_color_mt("Core:");
	s_coreLogger->set_level(spdlog::level::trace);

	// client logger
	s_appLogger = spdlog::stdout_color_mt("Application:");
	s_appLogger->set_level(spdlog::level::trace);
}

Ref<spdlog::logger> Log::getAppLogger()
{
	return s_appLogger;
}

Ref<spdlog::logger> Log::getCoreLogger()
{
	return s_coreLogger;
}

