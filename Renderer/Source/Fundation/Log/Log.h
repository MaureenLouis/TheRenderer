#pragma once
#include "Fundation/Ref/Ref.h"

class Log
{
public:
	static void init();

	static Ref<spdlog::logger> getAppLogger();

	static Ref<spdlog::logger> getCoreLogger();

	Log(const Log& another) = delete;
	Log& operator=(const Log& another) = delete;

private:
	Log() = default;
	~Log() = default;

private:
	static Ref<spdlog::logger> s_appLogger;
	static Ref<spdlog::logger> s_coreLogger;
};

#if defined (_DEBUG)
#    define CORE_ERROR(...) Log::getCoreLogger()->error(__VA_ARGS__)
#    define CORE_WARN(...)  Log::getCoreLogger()->warn(__VA_ARGS__)
#    define CORE_INFO(...)  Log::getCoreLogger()->info(__VA_ARGS__)
#    define CORE_TRACE(...) Log::getCoreLogger()->trace(__VA_ARGS__)

#    define APP_ERROR(...) Log::getAppLogger()->error(__VA_ARGS__)
#    define APP_WARN(...)  Log::getAppLogger()->warn(__VA_ARGS__)
#    define APP_INFO(...)  Log::getAppLogger()->info(__VA_ARGS__)
#    define APP_TRACE(...) Log::getAppLogger()->trace(__VA_ARGS__)
#else
#    define CORE_ERROR(...)
#    define CORE_WARN(...) 
#    define CORE_INFO(...) 
#    define CORE_TRACE(...)

#    define APP_ERROR(...) 
#    define APP_WARN(...)  
#    define APP_INFO(...)  
#    define APP_TRACE(...) 
#endif