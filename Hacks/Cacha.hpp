#include "Loot.hpp"
inline bool DoClear = false;
class EntityCacha {
public:
    inline void EntityThread() {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));  
        while (true) {
            if (!sdk.R5Apex)
                return;
            TempEntiyList.clear();

            LevelName = ReadString(sdk.R5Apex + Offsets::Misc::m_GameWorld);
            if (LevelName.empty()) continue;
            if (LevelName.find("mp_lobby") != std::string::npos)
                continue;
            SDK::Entity* LocalPlayer = Read<SDK::Entity*>(sdk.R5Apex + Offsets::Misc::m_LocalPlayer);
            if (!LocalPlayer) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));  
                continue; 
            }

            if (LocalPlayer->Current_Health() <= 0.1f) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
                continue;
            }
            if (LevelName.find("mp_rr_canyonlands_staging_mu1") != std::string::npos)
                Size = 20000;
            else
                Size = 2500;

            for (int i = 0; i <= Size; i++) {
                SDK::Entity* Entity = Read<SDK::Entity*>(sdk.R5Apex + Offsets::Misc::m_EntityList + ((static_cast<unsigned long long>(i)) << 5));
                if (!Entity) continue;
                uint64_t entityAddress = Entity->getAddress();
                if (!entityAddress || entityAddress == (uint64_t)LocalPlayer) continue;
                float Distance = calcDist(LocalPlayer->Get_Position(), Entity->Get_Position());
                if ((Distance / 20) > 500) continue;
                std::string Name = Entity->getSignifierName();
                if (Name.empty()) continue;
               
                if (Name.find(_("player")) != std::string::npos || Name.find(_("npc_dummie")) != std::string::npos) {
                    if (Entity->Current_Health() <= 0.1f) continue;

                    TempEntiyList.push_back(Entity);
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
        }
    }
}; inline EntityCacha* entCacha;

class LootCacha {
public:
	inline void LootThread()
	{
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
        while (true) {
          {
                LootList.clear();

                SDK::Entity* LocalPlayer = Read<SDK::Entity*>(sdk.R5Apex + Offsets::Misc::m_LocalPlayer);
                if (!LocalPlayer) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));  // Sleep to prevent busy-waiting
                    continue;  // Continue to avoid accessing a null pointer
                }

                if (LocalPlayer->Current_Health() >= 0.1f) {
                    for (int i = 0; i <= 50000; i++) {
                        SDK::Entity* Entity = Read<SDK::Entity*>(sdk.R5Apex + Offsets::Misc::m_EntityList + ((static_cast<unsigned long long>(i)) << 5));
                        if (!Entity) continue;
                        if (Entity->getAddress() < 0xFFFFF)continue; // remove holders
                        uint64_t entityAddress = Entity->getAddress();
                        if (Entity->getSignifierName().empty()) continue;
                        float Distance = calcDist(LocalPlayer->Get_Position(), Entity->Get_Position());
                        if ((Distance / 16) > Cheat_Private::Loot::lootDistance) continue;
                        if ((Entity->getSignifierName().find(_("prop_survival")) != std::string::npos || Entity->getSignifierName().find(_("prop_death_box")) != std::string::npos))
                            LootList.push_back((SDK::Loot*)Entity);
                    }
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));  // Sleep to control loop frequency
        }
	} 
}; inline LootCacha lootCacha;