#include "../SDK/SDK.hpp"
#include "../Overlay/Drawing/Draw.hpp"
#include <mmsystem.h>
#include <chrono>


class BHop {
public:
	inline void DoBhop(uintptr_t Address) {
		Write<int>(Address, 5);
		Write<int>(Address, 4);
		Sleep(250);

	}
	inline void BhopThread()
	{
		while (true)
		{
			if (Cheat_Private::Misc::Bhop)
			{
				////0 LAND
				////65 JUMP
				//uint64_t INJUMP{ 0x0769b778 }; // if ur seeing this its bc i was to lazy to add to offsets :(
				//int Jump = Read<int>(sdk.R5Apex + INJUMP + 0x8);
				//auto LocalPlayer = Read<SDK::Entity*>(sdk.R5Apex + Offsets::Misc::m_LocalPlayer);
				///*if (!LocalPlayer)
				//	return;*/
				////if (LocalPlayer->Current_Health() <= 0.1f)return;
				//DoBhop(Jump);
				//Write<int>(sdk.R5Apex + 0x0769b778 + 0x8, 7);
				//Write<int>(sdk.R5Apex + 0x0769b778 + 0x8, 4);
				//Write<int>(sdk.R5Apex + 0x0769b778 + 0x8, 7);
				//Write<int>(sdk.R5Apex + 0x0769b778 + 0x8, 4);

				//printf("IN JUMP : %d\n", Jump);
			}
			else
				std::this_thread::sleep_for(std::chrono::milliseconds(2500));
		}
	}
}; inline BHop bp;