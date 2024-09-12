#include <Windows.h>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <fstream>
#include <sstream>

#include "../utils/includes.h"

std::string GamePathA = _(" C:\\Program Files (x86)\Steam\\steamapps\\common\\");
std::string GamePathB = _(" D:\\Program Files (x86)\Steam\\steamapps\\common\\");
std::string GamePathC = _(" E:\\Program Files (x86)\Steam\\steamapps\\common\\");

std::string Game = _("r5apex.exe");
std::string Command = _("start");

const char* Version = _("GameBuild.txt");
const char* GameVersiion = _("1.09.93.32");
int VersionCount = 0;

class Threading {
public:

	HANDLE _BeginThreadex(void* Parm)
	{
		DWORD ThreadId = 0;

		HANDLE ThreadHandle = CreateThread(nullptr, 0,
			(LPTHREAD_START_ROUTINE)Parm
			, nullptr, 0,
			&ThreadId);

		//SHChangeNotifyRegisterThread(SCNRT_DISABLE);
		SetThreadPriorityBoost(ThreadHandle, true);

		if (ThreadHandle == NULL)
			CloseHandle(ThreadHandle);
		else
		{
#ifdef DEBUG
			LOG_DEBUG(_("Entity Thread Created At : 0x%lx\n"), (uint64_t)ThreadHandle));
#endif 
		}
		return ThreadHandle;
	}
};

//-----//

DWORD WINAPI GameCheck() 
{
	//GameVersion
	int nsize = 10;
	std::vector<char> somedata(nsize);
	std::ifstream myfile;
	wrongfile:
	switch (VersionCount)
	{
	case 0:
		myfile.open(std::string(GamePathA + Version));
	break;
	case 1:
		myfile.open(std::string(GamePathB + Version));
	break;
	case 2:
		myfile.open(std::string(GamePathC + Version));
	break;
	}
	myfile.read(somedata.data(), nsize);
	if (!somedata.data())
	{
		VersionCount += 1;
		goto wrongfile;
	}
	myfile.close();
	Version = somedata.data();
	//end


	if (strcmp(Version, GameVersiion) == 0)
	{
		LOG_DEBUG(_("Game Version Current With Cheat : %s"), Version);
	}
	else
	{
		LOG_DEBUG(_("Game Version Incorrect With Cheat Build  : %s"), Version);

	}
	LOG_DEBUG(_("Starting Apex Legends\n"));

	if (system(std::string(Command + GamePathA + Game).c_str()) < 1)
		if (system(std::string(Command + GamePathB + Game).c_str()) < 1)
			if (system(std::string(Command + GamePathC + Game).c_str()) < 1)
				exit(0);

	return 0;
}