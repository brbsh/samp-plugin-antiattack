#pragma once



#include "parser.h"





amxParser *gParser;

extern logprintf_t logprintf;
extern std::queue<attackData> amxQueue;





amxParser::amxParser()
{
	this->Active = true;

	boost::thread parser(&amxParser::Thread);
}



amxParser::~amxParser()
{
	this->Active = false;
}



void amxParser::Thread()
{
	attackData pushme;

	std::size_t find;
	std::size_t sub;
	std::fstream file;

	int seekOffset = -96;

	do
	{
		file.open("server_log.txt", (std::fstream::in | std::fstream::ate));
		file.seekg(seekOffset, std::fstream::cur);

		while(std::getline(file, pushme.data))
		{
			if((pushme.data.length() < 28) || (pushme.data.length() > abs(seekOffset)) || (pushme.data.find("[chat]") != std::string::npos)) 
				continue;

			find = pushme.data.find("Warning: PlayerDialogResponse PlayerId: ");
			sub = pushme.data.find(" dialog ID doesn't match last sent dialog ID");

			if((find != std::string::npos) && (sub != std::string::npos) && (find < sub))
			{
				pushme.type = 0;
				pushme.data.erase(NULL, (find + 40));
				pushme.data.erase((sub - 40));

				boost::mutex::scoped_lock lock(gParser->Mutex);
				amxQueue.push(pushme);
				lock.unlock();

				aat_Debug("* Pushing %i:%s to ProcessTick()", pushme.type, pushme.data.c_str());

				if((atoi(pushme.data.c_str()) < 0) || (atoi(pushme.data.c_str()) > gParser->MaxPlayers))
					break;

				boost::this_thread::sleep(boost::posix_time::seconds(5));

				if(gParser->ClearLog)
				{
					aat_Debug("Server log file cleaning...");

					file.close();
					file.open("server_log.txt", (std::fstream::out | std::fstream::trunc));
				}

				break;
			}

			find = pushme.data.find("Warning: PlayerDialogResponse crash exploit from PlayerId: ");

			if(find != std::string::npos)
			{
				pushme.type = 1;
				pushme.data.erase(NULL, (find + 59));

				boost::mutex::scoped_lock lock(gParser->Mutex);
				amxQueue.push(pushme);
				lock.unlock();

				aat_Debug("* Pushing %i:%s to ProcessTick()", pushme.type, pushme.data.c_str());

				if((atoi(pushme.data.c_str()) < 0) || (atoi(pushme.data.c_str()) > gParser->MaxPlayers))
					break;

				boost::this_thread::sleep(boost::posix_time::seconds(5));

				if(gParser->ClearLog)
				{
					aat_Debug("Server log file cleaning...");

					file.close();
					file.open("server_log.txt", (std::fstream::out | std::fstream::trunc));
				}

				break;
			}
			
			find = pushme.data.find("Warning: /rcon command exploit from: ");

			if(find != std::string::npos)
			{
				pushme.type = 2;
				pushme.data.erase(NULL, (find + 37));
				pushme.data.erase(pushme.data.find(":"));

				boost::mutex::scoped_lock lock(gParser->Mutex);
				amxQueue.push(pushme);
				lock.unlock();

				aat_Debug("* Pushing %i:%s to ProcessTick()", pushme.type, pushme.data.c_str());

				if((atoi(pushme.data.c_str()) < 0) || (atoi(pushme.data.c_str()) > gParser->MaxPlayers))
					break;

				boost::this_thread::sleep(boost::posix_time::seconds(5));

				if(gParser->ClearLog)
				{
					aat_Debug("Server log file cleaning...");

					file.close();
					file.open("server_log.txt", (std::fstream::out | std::fstream::trunc));
				}

				break;
			}

			find = pushme.data.find("Packet was modified, sent by id: ");
			sub = pushme.data.find(", ip: ");

			if((find != std::string::npos) && (sub != std::string::npos) && (find < sub))
			{
				pushme.type = 3;
				pushme.data.erase(NULL, (find + 33));
				pushme.data.erase((sub - 33));

				boost::mutex::scoped_lock lock(gParser->Mutex);
				amxQueue.push(pushme);
				lock.unlock();

				aat_Debug("* Pushing %i:%s to ProcessTick()", pushme.type, pushme.data.c_str());

				if((atoi(pushme.data.c_str()) < 0) || (atoi(pushme.data.c_str()) > gParser->MaxPlayers))
					break;

				boost::this_thread::sleep(boost::posix_time::seconds(5));

				if(gParser->ClearLog)
				{
					aat_Debug("Server log file cleaning...");

					file.close();
					file.open("server_log.txt", (std::fstream::out | std::fstream::trunc));
				}

				break;
			}

			find = pushme.data.find("Remote Port Refused for Player: ");

			if(find != std::string::npos)
			{
				pushme.type = 4;
				pushme.data.erase(NULL, (find + 32));

				boost::mutex::scoped_lock lock(gParser->Mutex);
				amxQueue.push(pushme);
				lock.unlock();

				aat_Debug("* Pushing %i:%s to ProcessTick()", pushme.type, pushme.data.c_str());

				if((atoi(pushme.data.c_str()) < 0) || (atoi(pushme.data.c_str()) > gParser->MaxPlayers))
					break;

				boost::this_thread::sleep(boost::posix_time::seconds(5));

				if(gParser->ClearLog)
				{
					aat_Debug("Server log file cleaning...");

					file.close();
					file.open("server_log.txt", (std::fstream::out | std::fstream::trunc));
				}

				break;
			}

			find = pushme.data.find("BAD RCON ATTEMPT BY: ");

			if(find != std::string::npos)
			{
				pushme.type = 5;
				pushme.data.erase(NULL, (find + 21));

				boost::mutex::scoped_lock lock(gParser->Mutex);
				amxQueue.push(pushme);
				lock.unlock();

				aat_Debug("* Pushing %i:%s to ProcessTick()", pushme.type, pushme.data.c_str());

				if((atoi(pushme.data.c_str()) < 0) || (atoi(pushme.data.c_str()) > gParser->MaxPlayers))
					break;

				boost::this_thread::sleep(boost::posix_time::seconds(5));

				if(gParser->ClearLog)
				{
					aat_Debug("Server log file cleaning...");

					file.close();
					file.open("server_log.txt", (std::fstream::out | std::fstream::trunc));
				}
				
				break;
			}

			find = pushme.data.find("Invalid client connecting from ");

			if(find != std::string::npos)
			{
				pushme.type = 6;
				pushme.data.erase(NULL, (find + 31));

				boost::mutex::scoped_lock lock(gParser->Mutex);
				amxQueue.push(pushme);
				lock.unlock();

				aat_Debug("* Pushing %i:%s to ProcessTick()", pushme.type, pushme.data.c_str());

				if((atoi(pushme.data.c_str()) < 0) || (atoi(pushme.data.c_str()) > gParser->MaxPlayers))
					break;

				boost::this_thread::sleep(boost::posix_time::seconds(5));

				if(gParser->ClearLog)
				{
					aat_Debug("Server log file cleaning...");

					file.close();
					file.open("server_log.txt", (std::fstream::out | std::fstream::trunc));
				}

				break;
			}

			find = pushme.data.find("Blocking ");
			sub = pushme.data.find(" due to a 'server full' attack");

			if((find != std::string::npos) && (sub != std::string::npos) && (find < sub))
			{
				pushme.type = 7;
				pushme.data.erase(NULL, (find + 9));
				pushme.data.erase((sub - 9));

				boost::mutex::scoped_lock lock(gParser->Mutex);
				amxQueue.push(pushme);
				lock.unlock();

				aat_Debug("* Pushing %i:%s to ProcessTick()", pushme.type, pushme.data.c_str());

				if((atoi(pushme.data.c_str()) < 0) || (atoi(pushme.data.c_str()) > gParser->MaxPlayers))
					break;

				boost::this_thread::sleep(boost::posix_time::seconds(5));

				if(gParser->ClearLog)
				{
					aat_Debug("Server log file cleaning...");

					file.close();
					file.open("server_log.txt", (std::fstream::out | std::fstream::trunc));
				}

				break;
			}
		}

		file.close();
		
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
	while(gParser->Active);
}