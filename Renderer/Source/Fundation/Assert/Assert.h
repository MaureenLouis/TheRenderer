#pragma once

#define ASSERT_HELPER(expression, file, function, line, format, ...)  \
{                                                                     \
char buff[128] = { 0 };												  \
sprintf(buff, format, __VA_ARGS__);								      \
_assert(#expression, buff, file, function,line);				      \
}

#ifdef _DEBUG
#    define ASSERT(expression, format, ...) ASSERT_HELPER(expression, __FILE__, __FUNCTION__, __LINE__, format, __VA_ARGS__)
#else
#    define ASSERT(expression, format, ...)  
#endif


void _assert(const char* expression, const char* message, const char* file, const char* function, const int line);


