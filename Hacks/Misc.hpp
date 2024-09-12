#include "Glow.hpp"

#pragma comment(lib, "winmm.lib")



//outline 23

inline float previousPitch = 0;
inline float previousYaw = 0;
inline float pitchSTR = 1;
inline float yawSTR = 1;



class Misc{
public:
     int MAX = 99999999999;
    
    
    void NoRecoil(SDK::Entity* Localplayer)
    {
        Vector3 angles = Localplayer->ViewAngles();
        Vector2 punch = Read<Vector2>(Localplayer->getAddress() + 0x2438);
        if (punch.y < 0 || punch.x < 0) {
            angles.x -= (punch.y - previousYaw) * yawSTR;
            angles.y -= (punch.x - previousPitch) * pitchSTR;
            //NormalizeAngles(angles);
            Localplayer->SetViewAngles({ angles.x,angles.y });
            previousPitch = punch.x;
            previousYaw = punch.y;
        }
    }
  
    bool Once = true;
    void DoMisc()
    {
        while (true)
        {
            SDK::Entity* LocalPlayer = Read<SDK::Entity*>(sdk.R5Apex + Offsets::Misc::m_LocalPlayer);
            if (!LocalPlayer) continue;  // Exit if LocalPlayer is not available

            uint64_t localPlayerAddress = LocalPlayer->getAddress();
            if (!localPlayerAddress) continue;  // Exit if localPlayerAddress is invalid
            gl->weapon_glow((uint64_t)LocalPlayer, 1);

            if (Cheat_Private::Misc::BetterMovement)
                Write<float>(LocalPlayer->getAddress() + 0x3b7c, 1.345); // 1.345
            else
                Write<float>(LocalPlayer->getAddress() + 0x3b7c, 1.0000f); // 1.345

            if (TempEntiyList.empty()) continue;  // Return if there are no entities to process
            for (size_t i = 0; i < TempEntiyList.size(); i++) {
                
            
                SDK::Entity* Entity = TempEntiyList[i];
                if (!Entity) continue;

                uint64_t entityAddress = Entity->getAddress();
                if (!entityAddress || entityAddress == (uint64_t)LocalPlayer) continue;

                int entityHealth = Entity->Current_Health();
                if (entityHealth <= 0.1f) continue;

                if (Cheat_Private::Aimbot::RcsControl)
                {
                    NoRecoil(LocalPlayer);
                }
                if (Cheat_Private::Misc::BackTrack)
                {
                    //BackTrack();
                }
                if (Cheat_Private::Misc::AntiBan)
                {
                    //Write<bool>( sdk.R5Apex + 0x01852510, true); //eosIsActive=0x01852510
                    //Write<float>( sdk.R5Apex + 0x01852510, 0.f); 
                    //Write<float>( sdk.R5Apex + 0x01852300, -1.f); // eosLoginRetryMaxTime = 0x01852300
                    //Write<std::string>( sdk.R5Apex + 0x01852720, _("76796531e86443548754600511f42e9e"));
                    //Write<std::string>( sdk.R5Apex + 0x01852880, _("ec47bae0651a4765a063c1e83ec41b34"));

                }

                if (Cheat_Private::ESP::Glow)
                {
                    gl->SetColor(Entity->getAddress(), 2, 47, { 137,138,35,127 }, { glowcolor[0],glowcolor[1],glowcolor[2] }); // 0 -green 0 - 0 - red

                }
                if (Cheat_Private::Misc::FakeDuck)
                {
                    switch (Cheat_Private::Misc::FakeDuckKEY)
                    {
                    case 0:
                        Cheat_Private::Misc::KafeDuckBIND = 0x01;
                        break;
                    case 1:
                        Cheat_Private::Misc::KafeDuckBIND = 0x02;
                        break;
                    case 2:
                        Cheat_Private::Misc::KafeDuckBIND = 0x05;
                        break;
                    case 3:
                        Cheat_Private::Misc::KafeDuckBIND = 0x06;
                        break;
                    case 4:
                        Cheat_Private::Misc::KafeDuckBIND = 0xA4;
                        break;
                    case 5:
                        Cheat_Private::Misc::KafeDuckBIND = 0xA0;
                        break;
                    }
                    if (GetAsyncKeyState(Cheat_Private::Misc::KafeDuckBIND))
                    {
                        Write<int>(sdk.R5Apex + 0x0769b868 + 0x8, 6); // in_duck=0x0769b7e8
                        Write<int>(sdk.R5Apex + 0x0769b868 + 0x8, 4); // in_duck=0x0769b7e8
                        Sleep(1);
                        Write<int>(sdk.R5Apex + 0x0769b868 + 0x8, 6); // in_duck=0x0769b7e8
                        Write<int>(sdk.R5Apex + 0x0769b868 + 0x8, 4); // in_duck=0x0769b7e8
                    }
                }

                if (Cheat_Private::Misc::Bhop)
                {
                    if (GetAsyncKeyState(VK_SPACE))
                    {
                        Write<int>(sdk.R5Apex + 0x0769b778 + 0x8, 7);
                        Write<int>(sdk.R5Apex + 0x0769b778 + 0x8, 4);
                        //Sleep(25);
                    }
                 
                }
                if (Cheat_Private::Misc::Fakefire)
                {
                    if (GetAsyncKeyState(VK_LBUTTON))
                    {

                        Write<int>(sdk.R5Apex + 0x0769b658 + 0x8, 7);
                        Write<int>(sdk.R5Apex + 0x0769b658 + 0x8, 4);
                       // Sleep(25);
                    }

                }

                if (Cheat_Private::Misc::SuperGlide)
                {
                    uintptr_t m_grapple = 0x2cc0;
                    uintptr_t timeBase = 0x2088;
                    uintptr_t OFFSET_m_traversalStartTime = 0x2b70;
                    uintptr_t OFFSET_m_traversalProgress = 0x2b6c;
                    static float startjumpTime = 0;
                    static bool startSg = false;

                    float    WorldTime = Read<float>(LocalPlayer->getAddress() + timeBase);
                    float m_traversalStartTime = Read<float>(LocalPlayer->getAddress() + OFFSET_m_traversalStartTime);
                    float m_traversalProgress = Read<float>(LocalPlayer->getAddress() + OFFSET_m_traversalProgress);
                    auto HangOnWall = -(m_traversalStartTime - WorldTime);

                    if (GetAsyncKeyState(0x57))
                    {
                        if (m_traversalProgress > 0.87f && !startSg && HangOnWall > 0.05f && HangOnWall < 1.5f) {
                            //start SG
                            startjumpTime = WorldTime;
                            startSg = true;
                        }

                        if (startSg) {
                            //press button
                            Write<int>(sdk.R5Apex + 0x0769b778 + 0x8, 7); // in jump
                            if ((WorldTime - startjumpTime) > 0.007) {
                                Write<int>(sdk.R5Apex + 0x0769b868 + 0x8, 6); // in_duck=0x0769b7e8
                            }
                        }

                        if ((WorldTime - startjumpTime) > 1.5f && startSg) {
                            //need to release button
                            Write<int>(sdk.R5Apex + 0x0769b778 + 0x8, 4);
                            Write<int>(sdk.R5Apex + 0x0769b868 + 0x8, 4); //in_duck = 0x0769b7e8
                            startSg = false;
                        }

                    }
                }
                if (Cheat_Private::Misc::Freecam)
                {
                    if (GetAsyncKeyState(0x58))
                    {//m_iObserverMode
                        Write<int>(LocalPlayer->getAddress() + 0x3524, 7);
                    }
                    else {
                        Write<int>(LocalPlayer->getAddress() + 0x3524, 0);
                    }

                }
                if (Cheat_Private::Misc::SkinChanger)
                {
                    DWORD64 LastWeapon = Read<DWORD64>(LocalPlayer->getAddress() + Offsets::Misc::m_PrimaryWeapon) & 0xFFFF; // current weapon // m_latestPrimaryWeapons
                    DWORD64 Weapon = Read<DWORD64>(sdk.R5Apex + Offsets::Misc::m_EntityList + (LastWeapon << 5));
                    Write<int>(Weapon + 0x0d68, Cheat_Private::Misc::SkinID);

                }
                if (Cheat_Private::Misc::AutoGrapple)
                {

                    if (GetAsyncKeyState(0x51))
                    {
                        Write<int>(sdk.R5Apex + 0x0769b6e0 + 0x8, 4);

                        auto Gn = Read<int>(LocalPlayer->getAddress() + 0x2cc0 + 0x0048);
                        if (Gn == 1) {
                            Write<int>(sdk.R5Apex + 0x0769b6e0 + 0x8, 5);
                        }
                    }
                }
            }

            if (Cheat_Private::Misc::ItemGlow && Once)
            {
                std::thread(&Glow::ItemGlow, gl).detach();
                Once = false;
            }

        }
    }
    
}; inline Misc misc;

