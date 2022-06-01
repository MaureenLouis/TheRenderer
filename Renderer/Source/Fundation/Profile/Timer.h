#pragma once
#include "Core/Preprocessor/PreprocessorUtils.h"

class Timer
{
public:
	Timer(const char* funcName);
	~Timer();

private:
	double _begin;
	double _end;
	double _elapsed;
	const char* _funcname;
};


#define PROFILE_THIS_IMPL(funcname)    Timer CONCAT(_timer, __LINE__)(funcname)

#ifdef THERENDERER_PROFILE
#define PROFILE_THIS() PROFILE_THIS_IMPL(__FUNCTION__)
#else
#define PROFILE_THIS()
#endif

void test()
{
	PROFILE_THIS();
}