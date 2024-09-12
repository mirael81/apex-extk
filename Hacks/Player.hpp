#include "Cacha.hpp"


class Player {
public:

    void __fastcall RunCheat() {
        EntityList.clear();
        WebRadarHack::PositionList.clear();
        visentcount = 0;
        EntityCount = 0;
        SDK::Entity* LocalPlayer = Read<SDK::Entity*>(sdk.R5Apex + Offsets::Misc::m_LocalPlayer);
        if (!LocalPlayer) return;  // Exit if LocalPlayer is not available

        uint64_t localPlayerAddress = LocalPlayer->getAddress();
        if (!localPlayerAddress) return;  // Exit if localPlayerAddress is invalid

        int localTeamNum = LocalPlayer->Get_TeamNum();
        Vector3 localPosition = LocalPlayer->Get_Position();
        float worldTime = Read<float>(localPlayerAddress + Offsets::Misc::m_WorldTime);

        if (TempEntiyList.empty()) return;  // Return if there are no entities to process
        for (size_t i = 0; i < TempEntiyList.size(); i++) {  // Fixed out-of-bounds access with size_t
            SDK::Entity* Entity = TempEntiyList[i];
            if (!Entity) continue;
            
            uint64_t entityAddress = Entity->getAddress();
            if (!entityAddress || entityAddress == (uint64_t)LocalPlayer) continue;

           
            
            {
                int entityHealth = Entity->Current_Health();
                if (entityHealth <= 0.1f) continue;

                if (Entity->Get_TeamNum() == localTeamNum) continue;

                Vector3 entityBasePos = Entity->Get_Position();
                if (entityBasePos.Empty()) continue;

                float distance = localPosition.DistTo(entityBasePos) / 16.0f;
                if (distance >= Cheat_Private::Settings::RenderDistance) {
                    //gl->DisableGlow(Entity->getAddress());
                    continue;
                }
                EntityList.push_back(Entity);
                EntityCount += 1;

                float entityTime1 = Read<float>((uint64_t)Entity + Offsets::Misc::m_lastVisibleTime);  // CPlayer!lastVisibleTime=0x19a0
                bool isVisible = (entityTime1 + 0.2f) >= worldTime;
                if (isVisible)
                    visentcount += 1;

                

                if (Cheat_Private::Misc::AmmoCounter)
                {
                    uint64_t primary_weapons_latest = Read<uint64_t>(LocalPlayer->getAddress() + Offsets::Misc::m_PrimaryWeapon) & 0xFFFF;
                    uint64_t primary_weapons_list = Read<uint64_t>(sdk.R5Apex + Offsets::Misc::m_EntityList + (primary_weapons_latest * 0x20));
                    int CurrentAmmo = Read<int>(primary_weapons_list + 0x1590);
                    int MaxAmmo = Read<int>(primary_weapons_list + 0x1594);
                    int IsReloading = Read<int>(primary_weapons_list + 0x15aa);
                    std::string ReloadingText = std::string("Reloading");
                    ImVec2 Reloading_Size = ImGui::CalcTextSize(ReloadingText.c_str());
                    if (IsReloading == 1)
                        Draw::esp->draw_text_outline_font((GetSystemMetrics(0) / 2 - (Reloading_Size.x / 2)), (GetSystemMetrics(1) / 2 - (Reloading_Size.y / 2) - 70), ImColor(255, 255, 255, 255), ReloadingText.c_str(), 1.f);

                    std::string text = std::string(std::to_string(CurrentAmmo) + "/" + std::to_string(MaxAmmo));
                    ImVec2 Size = ImGui::CalcTextSize(text.c_str());
                    Draw::esp->draw_text_outline_font((GetSystemMetrics(0) / 2 - (Size.x / 2)), (GetSystemMetrics(1) / 2 - (Size.y / 2) - 50), ImColor(255, 255, 255, 255), text.c_str(), 1.f);
                }

                if (Cheat_Private::Misc::KillSound) {
                    float KillTime = LocalPlayer->LastKillTime();
                    std::string Name = Entity->GetName(i);

                    HandleKillEvent(KillTime, Name);

                    UpdateKills();
                    DrawKillText(killList);
                }

              
                esp.DrawEsp(Entity, LocalPlayer, entityHealth, isVisible, i);
                aimbot.DoAimbot(Entity, LocalPlayer, isVisible);
               // misc.DoMisc(Entity, LocalPlayer, isVisible, i);
            }

           
        }

        if (Cheat_Private::Loot::Text || Cheat_Private::Loot::Icon || Cheat_Private::Loot::ChangeLootSize) {
            for (SDK::Loot* MainLoot : LootList) {
                loot.DrawLoot(MainLoot, LocalPlayer);
                if (Cheat_Private::Loot::ChangeLootSize)
                {
                    DWORD64 LastWeapon = Read<DWORD64>((uintptr_t)MainLoot + Offsets::Misc::m_PrimaryWeapon); // current weapon // m_latestPrimaryWeapons
                    if (!LastWeapon)continue;
                    DWORD64 Weapon = Read<DWORD64>(sdk.R5Apex + Offsets::Misc::m_EntityList + (LastWeapon << 5));
                    Write<float>(LastWeapon + 0x0e20, 100.f);
                }
            }
        }
    }
};

inline Player player;
