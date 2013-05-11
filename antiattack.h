#pragma once

#pragma warning (disable:4005 700 996)

#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"

#if (defined(WIN32) || defined(_WIN32) || defined(_WIN64))
	#include <windows.h>
#else
	#include <pthread.h>
#endif

#include <time.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <queue>
#include <list>
#include <string>

#if defined(LINUX) || defined(FREEBSD) || defined(__FreeBSD__) || defined(__OpenBSD__)
	#include <unistd.h>
	#include <stdarg.h>
	#include <complex>
	#include <algorithm>
#endif

#define arguments(a) \
	!(params[0] != (a << 2))

typedef void (*logprintf_t)(char* format, ...);

#ifdef WIN32
	#define SLEEP(x) { Sleep(x); }
#else
	#define SLEEP(x) { usleep(x * 1000); }
	typedef unsigned long DWORD;
#endif

std::string stringvprintf(const char *format, va_list args)
{
	int length = vsnprintf(NULL, 0, format, args);
	char *chars = new char[++length];

	length = vsnprintf(chars, length, format, args);
	std::string result(chars);
	delete chars;

	return result;
}
