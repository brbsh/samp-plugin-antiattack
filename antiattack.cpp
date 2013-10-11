#pragma once



#include "antiattack.h"





logprintf_t logprintf;

boost::mutex gMutex;

std::queue<attackData> amxQueue;
std::list<AMX *> amxList;

extern void	*pAMXFunctions;
extern amxParser *gParser;
extern amxString *gString;





PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return (SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK);
}



PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) 
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	gParser = new amxParser();

	aat_Debug("\n\tAnti-Attack logging enabled...");
	aat_Debug("Plugin version: %s", PLUGIN_VERSION);

	logprintf("  Anti-Attack v%s by BJIADOKC loaded", PLUGIN_VERSION);

	return 1;
}



PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	amxList.clear();

	aat_Debug("Plugin has been terminated by gamemode!");
	aat_Debug("\tAnti-Attack logging disabled...");

	logprintf("  Anti-Attack v%s by BJIADOKC unloaded", PLUGIN_VERSION);

	delete gParser;
}



PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	amxList.push_back(amx);

	return amx_Register(amx, amxNatives::aatNatives, -1);
}



PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx) 
{
	for(std::list<AMX *>::iterator i = amxList.begin(); i != amxList.end(); i++) 
	{
		if(*i == amx) 
		{
			amxList.erase(i);

			break;
		}
	}

	return AMX_ERR_NONE;
}



PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
	while(!amxQueue.empty()) 
	{
		int amx_idx;
		attackData toamx;

		std::list<AMX *>::iterator end = amxList.end();

		aat_Debug("* ProcessTick() is not empty, executing...");

		boost::mutex::scoped_lock lock(gMutex);
		toamx = amxQueue.front();
		amxQueue.pop();
		lock.unlock();

		for(std::list<AMX *>::iterator amx = amxList.begin(); amx != end; amx++) 
		{
			if(toamx.type > 4)
			{
				cell amxAddress;

				if(!amx_FindPublic(*amx, "OnRemoteAttackAttempt", &amx_idx)) 
				{
					amx_PushString(*amx, &amxAddress, NULL, toamx.data.c_str(), NULL, NULL);
					amx_Push(*amx, (toamx.type - 5));

					amx_Exec(*amx, NULL, amx_idx);

					amx_Release(*amx, amxAddress);
				}
			}
			else
			{
				if(!amx_FindPublic(*amx, "OnIngameAttackAttempt", &amx_idx)) 
				{
					amx_Push(*amx, atoi(toamx.data.c_str()));
					amx_Push(*amx, toamx.type);
					
					amx_Exec(*amx, NULL, amx_idx);
				}
			}
		}
	}
}



void aat_Debug(char *text, ...)
{
	if(gParser->Logging)
	{
		va_list args;

		std::fstream logfile;
		std::string buffer;

		va_start(args, text);
		buffer = gString->vprintf(text, args);
		va_end(args);

		logfile.open("attack_log.txt", (std::fstream::out | std::fstream::app));
		logfile << buffer << std::endl;
		logfile.close();
	}
}
