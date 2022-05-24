#include "stdafx.h"
#include "Assert.h"
#include <crtdbg.h>

void _assert(const char* expression, const char* message, const char* file, const char* function, const int line)
{
	char szTemp[1024 * 4] = "";
	snprintf(szTemp, sizeof(szTemp),
		"\n\n *** Assertion ***\n\n    Expression: \"%s\"\n    Function: \"%s\"\n    File: \"%s\"\n    Line: %u\n    Message: \"%s\"\n\n", expression,
		function, file, line, message);
	szTemp[1024 * 4 - 1] = '\0';

	// TODO: Show a dialog if Debugger is attached
#ifdef _DEBUG
	uint32_t iRes = _CrtDbgReport(_CRT_ASSERT, file, line, nullptr, "'%s'\nFunction: %s\nMessage: %s", expression, function, message);
#endif
	/// Else: Write to a file.
}
