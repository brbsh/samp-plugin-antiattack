#pragma once



#include "antiattack.h"





class amxParser
{

public:

	bool Active;
	bool Logging;
	bool ClearLog;
	int MaxPlayers;

	boost::mutex Mutex;

	amxParser();
	~amxParser();

	static void Thread();
};