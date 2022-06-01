#include "stdafx.h"
#include "Timer.h"

Timer::Timer(const char* funcName)
{
	_funcname = funcName;
	_begin = clock();
}

Timer::~Timer()
{
	_end = clock();
	_elapsed = _end - _begin;

	APP_INFO("Function name: {0} elapsed : {1}", _funcname ,_elapsed);
}
