#pragma once


#ifdef _DEBUG
#define glCheck(function)                           \
do {												\
	function;										\
	glCheckError(__FILE__, __FUNCTION__, __LINE__);	\
    __debugbreak();                                 \
} while (0)
#else
#define glCheck(function)
#endif

#ifdef _DEBUG
#define glShaderCheck(handle)                                                   \
do {												                            \
	int ret = glShaderCheckError(handle, __FILE__, __FUNCTION__, __LINE__);	    \
    if (ret != GL_TRUE) __debugbreak();                                         \
} while (0)
#else
#define glShaderCheck(function)
#endif

#ifdef _DEBUG
#define glProgramCheck(handle)                                                  \
do {												                            \
	int ret = glProgramCheckError(handle, __FILE__, __FUNCTION__, __LINE__);	\
    if (ret != GL_TRUE) __debugbreak();                                         \
} while (0)
#else
#define glProgramCheck(function)
#endif




// Error check
GLenum glCheckError(const char* file, const char* function, int line);
int glShaderCheckError(int handle, const char* file, const char* function, int line);
int glProgramCheckError(int handle, const char* file, const char* function, int line);



