#include <iostream>
#include <Windows.h>
#include <vector>
#include <unordered_map>

namespace Cheat {
	namespace ESP {
		inline bool Glow = false;
		inline int Glow_Type = 0;
		inline bool Rainbow = false;
		inline bool HealthBased = false;
		inline bool SkipTeam = false;
		inline float GlowColor[4] = {255.f,255.f,255.f,255.f};
	}
	namespace Aimbot {
		inline bool Aimbot = false;
        inline bool pSilent = false;
		inline bool FovCircle = false;
		inline int AimbotKey = VK_LSHIFT;
		inline int Smoothing = 1; // 1 low \ 10 max
		inline float FovCircleSize = 100.f;
        inline bool Recoil_Control = false;
        inline float Recoil_Precent = false;
	}
    namespace Misc {
        inline bool SuperGlide = false;
        inline bool SuperGrapple = false;
        inline bool ThirdPerson = false;
        inline bool FreeCam = false;
        inline bool FakeFire = false;
        inline int FakeFireKey = VK_LSHIFT;
        inline int FreeCamKey = VK_LSHIFT;

    }
}

namespace Cheat_Private {
    namespace ESP {

        enum Style : int {
            Original = 0, // normal box + defualt font
            Modern = 1, // rounded box + modern font
            Pixel = 2, // outline box + pixel font
            Dynamic = 3, // Sharpened boxs + hyper font
            Advance = 4 // Debug boxes + debug font
        };

        inline bool Box = false;
        inline bool Filledbox = false;
        inline bool VisCheck = false;
        inline bool alert = false;
        inline bool CornerBox = false;
        inline bool ArmorICON = false;
        inline bool WeaponICON = false;
        inline bool DeathBox = false;
        inline bool PeterGriffen = false;
        inline bool EKitten = false;
        inline int BoxStyle = 0;
        inline bool Skeleton = false;
        inline bool Name = false;
        inline bool Distance = false;
        inline bool OFFArrow = false;
        inline bool Operator = false;
        inline float RadarSize = 2;
        inline bool Weapon = false;
        inline bool Glow = false;
        inline bool RainbowGlow = false;
        inline bool OperatorICON = false;
        inline bool WeaponGlow = false;
        inline bool HealthBasedGlow = false;
        inline bool SernEsp = false;
        inline bool RemoveTeam = false;
        inline bool RemoveKnocked = false;
        inline bool Radar = false;
        inline bool Health = false;
        inline bool Shield = false;
        inline bool FOVArrows = false;
        inline bool Level = false;
        inline bool HandGlow = false;

        inline float BoxColor[4] = {
           255.f,
         255.f,
         255.f,
         255.f
        };
        inline float WeaponIconColor[4] = {
           255.f,
         255.f,
         255.f,
         255.f
        };
        inline float WeaponColor[4] = {
          255.f,
        255.f,
        255.f,
        255.f
        };
        inline float DeathBoxColor[4] = {
          255.f,
         255.f,
         255.f,
         255.f
        };
        inline float VisColor[4] = {
          0.0f,
          255.f,
          0.0f,
          255.f
        };
        inline float NonVisColor[4] = {
          255.f,
          0.0f,
          0.0f,
          255.f
        };
        inline float SkeletonColor[4] = {
         255.f,
         255.f,
         255.f,
         255.f
        };
        inline float LevelColor[4] = {
          255.f,
         255.f,
         255.f,
         255.f
        };
        inline float NameColor[4] = {
         255.f,
         255.f,
         255.f,
         255.f
        };
        inline float OperatorColor[4] = {
         255.f,
         255.f,
         255.f,
         255.f
        };
        inline float CornerBoxColor[4] = {
          255.f,
         255.f,
         255.f,
         255.f
        };
        inline float DistanceColor[4] = {
         255.f,
         255.f,
         255.f,
         255.f
        };

        inline int TextPlacment[4];
    }
    namespace Aimbot {
        inline bool VABot = false;
        inline int AimbotKey;
        inline bool FovCircle = false;
        inline bool Fakefire = false;
        inline bool RcsControl = false;
        inline float FovCircleSize = 100.f;
        inline bool Snapline = false;
        inline bool PSilent = false;
        inline int TargetBone = 0;
        inline std::vector<std::string> BoneName = { "Head", "Neck", "UpperChest", "LowerChest" };
       // gui::combo("Combo", &combo, items, IM_ARRAYSIZE(items));
        inline float SmoothingAmount = 10.f;
        inline float FovCircleColor[4] = {
         255.f,
         255.f,
         255.f,
         255.f
        };
        inline float SnaplineColor[4] = {
         255.f,
         255.f,
         255.f,
         255.f
        };
    }
    namespace Settings {

        inline bool ControllerSupport = false;
       inline std::vector<std::string> KeyText = { "LMouse", "RMouse", "X1 Mouse", "X2 Mouse", "LEFT alt", "Left Shift" };
       inline int AimbotKeyINDEX = 0;
        inline float RenderDistance = 250.f;
        inline std::unordered_map < int, int > Resolution = {
          {
            640,
            480
          }, // 480p
          {
            1280,
            720
          }, // 720p
          {
            1920,
            1080
          }, // 1080p
          {
            2560,
            1440
          }, // 1440p
          {
            2048,
            1080
          }, // 1080p
          {
            3840,
            2160
          }
        }; // 4K or ULTRA HD

    }
    namespace Config {
        inline std::vector<std::string> ConfigName = { "Legit", "Rage", "Personal", "Extra" };
        inline int ConfigIndex = 0;
        inline int LoadConfig = 0;
        inline int SaveConfig = 0;
        inline int RunConfig = 0;
    }
    namespace Misc
    {
        inline bool Freecam = false;
        inline bool FakeDuck = false;
        inline int FakeDuckKEY = 0x0;
        inline int KafeDuckBIND = 0x0;
        inline bool AutoGrapple = false;
        inline bool SkinChanger = false;
        inline int SkinID = 1;
        inline bool KillSound = false;
        inline bool Fakefire = false;
        inline bool BetterMovement = false;
        inline bool BackTrack = false;
        inline bool Bhop = false;
        inline bool AmmoCounter = false;
        inline bool FastFire = false;
        inline float BackTrackStrength = 0.5f;
        inline bool AntiBan = false;
        inline bool ItemGlow = false;
        inline bool SuperGlide = false;
//        //2 Matrix
//// 4 full blue
//        11 full yellow
//            62 full bright white
//            64 full red
//            77 full black
//            81 blue pulse
//            52 full purple
           // 50 full green
        inline std::vector<std::string> WeaponGlowText = { "Matrix", "White", "Black", "Green", "Purple","Blue", "Yellow", "Red","Rainbow"};
        inline int WeaponGlowIndex = 0;
        inline int SelectedGlowIndex = 0;
        inline bool WeaponGlow = false;


        inline std::vector<std::string> HandGlowText = { "Matrix", "White", "Black", "Green", "Purple","Blue", "Yellow", "Red"};
        inline int HandGlowIndex = 0;
        inline int HandSelectedGlowIndex = 0;
        inline bool HandGlow = false;
    }

    namespace Loot {
        inline bool Icon = false;
        inline bool ChangeLootSize = false;
        inline float LootSize = 1.0f;
        inline bool Medic = false;
        inline float lootDistance = 500.f;
        inline bool LightAmmo = false;
        inline bool ShotgunAmmo = false;
        inline bool SniperAmmo = false;
        inline bool HeavyAmmo = false;
        inline bool EnergyAmmo = false;
        inline bool LightWeapon = false;
        inline bool Shotgun = false;
        inline bool Text = false;
        inline int BattleKey = 0;
        inline int BattleIndex = 0;
        inline bool BattleMode = false;
        inline bool Shield = false;
        inline bool Helmet = false;
        inline std::vector<std::string> KeyText = { "LMouse", "RMouse", "X1 Mouse", "X2 Mouse", "LEFT alt", "Left Shift" };
        inline float ShieldColor[4] = {
              255.f,
              255.f,
              255.f,
              255.f
        };
        inline float HelmetColor[4] = {
              255.f,
              255.f,
              255.f,
              255.f
        };
        inline float MedicaColor[4] = {
               255.f,
               255.f,
               255.f,
               255.f
        };
        inline float LightAmmoColor[4] = {
             255.f,
             255.f,
             255.f,
             255.f
        };
        inline float ShotGunAmmoColor[4] = {
             255.f,
             255.f,
             255.f,
             255.f
        };
        inline float SniperAmmoColor[4] = {
            255.f,
            255.f,
            255.f,
            255.f
        };
        inline float HeavyAmmoColor[4] = {
            255.f,
            255.f,
            255.f,
            255.f
        };
        inline float EnergyAmmoColor[4] = {
            255.f,
            255.f,
            255.f,
            255.f
        };

        inline float ShotGunColor[4] = {
           255.f,
           255.f,
           255.f,
           255.f
        };

        inline float LightWeaponColor[4] = {
           255.f,
           255.f,
           255.f,
           255.f
        };
    }
}