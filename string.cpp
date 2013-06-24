#pragma once



#include "string.h"





amxString *gString;





std::string amxString::vprintf(const char *format, va_list args)
{
	int length = vsnprintf(NULL, NULL, format, args);
	char *chars = NULL;
	
	chars = (char *)malloc(++length);

	vsnprintf(chars, length, format, args);
	std::string result(chars);

	delete[] chars;

	return result;
}
