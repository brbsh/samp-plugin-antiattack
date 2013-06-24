#pragma once



#include "natives.h"





amxNatives *gNatives;

extern logprintf_t logprintf;
extern amxParser *gParser;





const AMX_NATIVE_INFO amxNatives::aatNatives[] = 
{
	{"aat_Init", amxNatives::Init},
	{"aat_NetStats", amxNatives::NetStats},

	{NULL, NULL}
};



// native aat_Init(maxplayers, bool:logging, bool:clear_log);
cell AMX_NATIVE_CALL amxNatives::Init(AMX *amx, cell *params)
{
	if(!arguments(3))
	{
		aat_Debug("Number of arguments in native 'aat_Init' does not conform to definition");
		logprintf("Anti-Attack Warning: Number of arguments in native 'aat_Init' does not conform to definition");

		return NULL;
	}

	gParser->MaxPlayers = params[1];
	gParser->Logging = (params[2]) ? true : false;
	gParser->ClearLog = (params[3]) ? true : false;

	aat_Debug("Initialized with MaxPlayers: %i, Logging: %s, Clear log: %s", gParser->MaxPlayers, (gParser->Logging) ? ("enabled") : ("disabled"), (gParser->ClearLog) ? ("enabled") : ("disabled"));
	logprintf("Anti-Attack: Initialized with MaxPlayers: %i, Logging: %s, Clear log: %s", gParser->MaxPlayers, (gParser->Logging) ? ("enabled") : ("disabled"), (gParser->ClearLog) ? ("enabled") : ("disabled"));

	return 1;
}



// native aat_NetStats(stats[]);
cell AMX_NATIVE_CALL amxNatives::NetStats(AMX *amx, cell *params)
{
	if(!arguments(1))
	{
		aat_Debug("Number of arguments in native 'aat_NetStats' does not conform to definition");
		logprintf("Anti-Attack Warning: Number of arguments in native 'aat_NetStats' does not conform to definition");

		return NULL;
	}

    char *stats = NULL;

    amx_StrParam(amx, params[1], stats);

	if(stats == NULL)
	{
		aat_Debug("NULL network stats passed to native 'aat_NetStats'");
		logprintf("Anti-Attack warning: NULL network stats passed to native 'aat_NetStats'");

		return NULL;
	}

	std::string netStats;

	netStats.assign(stats);
	netStats.erase(NULL, (netStats.find("Inst. KBits per second: ") + 25));
	netStats.erase(netStats.find('\n'));
		
	float ret = atof(netStats.c_str());

	return amx_ftoc(ret);
}