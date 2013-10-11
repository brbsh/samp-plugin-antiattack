#pragma once
#pragma warning (disable:4005 700 996 4244 4018)



#if (defined(WIN32) || defined(_WIN32) || defined(_WIN64))
	#include <windows.h>
#endif

#include <time.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <queue>
#include <list>
#include <string>
#include <string.h>

#if defined(LINUX) || defined(FREEBSD) || defined(__FreeBSD__) || defined(__OpenBSD__)
	#include <unistd.h>
	#include <stdarg.h>
	#include <complex>
	#include <algorithm>
#endif

#include <boost/bind.hpp>
#include <boost/thread.hpp>

#define HAVE_STDINT_H

#include "SDK/plugin.h"

#include "natives.h"
#include "parser.h"
#include "string.h"



#define CFG_PLUGIN_VERSION "1.2.2-R2"

#define arguments(a) \
	!(params[0] != (a << 2))




typedef void (*logprintf_t)(char *format, ...);



struct attackData
{
	int type;
	std::string data;
};



void aat_Debug(char *text, ...);