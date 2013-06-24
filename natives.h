#pragma once



#include "antiattack.h"





class amxNatives
{

public:

	static const AMX_NATIVE_INFO aatNatives[];

	static cell AMX_NATIVE_CALL Init(AMX *amx, cell *params);
	static cell AMX_NATIVE_CALL NetStats(AMX *amx, cell *params);
};