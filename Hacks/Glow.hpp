#include "HitLog.hpp"

#define OFF_GLOW_HIGHLIGHTS 0xb13c6a0
#define OFF_GLOW_ENABLE 0x28c
#define OFF_GLOW_THROUGH_WALL 0x26c
#define OFF_GLOW_HIGHLIGHT_ID 0x29C
#define OFF_HIGHLIGHT_TYPE_SIZE 0x34
#define OFF_GLOW_FIX 0x268
#define OFF_GLOW_DISTANCE 0x294
inline float glowcolor[3] = { 255.5 / 4.25,255.f / 4.25 ,255.f / 4.25  };
inline int glowtest = 8;
struct HighlightFunctionBits
{
    uint8_t functionBits[4];
};

struct HighlightParameter
{
    float parameter[3];
};
inline bool WasToggled = false;

class Glow {
public:
    inline void weapon_glow(uintptr_t localPlayer, bool toggle)
    {
        switch (Cheat_Private::Misc::WeaponGlowIndex)
        {
        case 0:
            Cheat_Private::Misc::SelectedGlowIndex = 2;
            break;
        case 1:
            Cheat_Private::Misc::SelectedGlowIndex = 62;
            break;
        case 2:
            Cheat_Private::Misc::SelectedGlowIndex = 77;
            break;
        case 3:
            Cheat_Private::Misc::SelectedGlowIndex = 50;
            break;
        case 4:
            Cheat_Private::Misc::SelectedGlowIndex = 52;
            break;
        case 5:
            Cheat_Private::Misc::SelectedGlowIndex = 4;
            break;
        case 6:
            Cheat_Private::Misc::SelectedGlowIndex = 31;
            break;
        case 7:
            Cheat_Private::Misc::SelectedGlowIndex = 74;
            break;
        case 8:
            Cheat_Private::Misc::SelectedGlowIndex = 78;
            break;
        }
        if (toggle && Cheat_Private::Misc::WeaponGlow)
        {
            WasToggled = true;
            uint64_t actWeaponID = Read<uint64_t>(localPlayer + Offsets::Misc::m_m_hViewModels) & 0xFFFF;
            if (!actWeaponID) return;
            uint64_t currentWeapon = Read<uint64_t>(
                sdk.R5Apex + Offsets::Misc::m_EntityList + (actWeaponID << 5));
            if (!currentWeapon) return;
            Write<uint8_t>(currentWeapon + OFF_GLOW_ENABLE,
                1);
            Write<uint8_t>(currentWeapon + OFF_GLOW_HIGHLIGHT_ID,
                Cheat_Private::Misc::SelectedGlowIndex);

            if (Cheat_Private::Misc::SelectedGlowIndex == 78)
            {
                uint64_t HighlightSettings = Read<uint64_t>(sdk.R5Apex + OFF_GLOW_HIGHLIGHTS);
                //      
                static int cases = 0;
                static float r = 1.00f, g = 0.00f, b = 1.00f;
                switch (cases)
                {
                case 0: { r -= 0.003f; if (r <= 0) cases += 1; break; }
                case 1: { g += 0.003f; b -= 0.003f; if (g >= 1) cases += 1; break; }
                case 2: { r += 0.003f; if (r >= 1) cases += 1; break; }
                case 3: { b += 0.003f; g -= 0.003f; if (b >= 1) cases = 0; break; }
                default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
                }
                Write<HighlightParameter>(HighlightSettings + 0x34 * uint64_t(Cheat_Private::Misc::SelectedGlowIndex) + 8, { r / 4.25f,g / 4.25f,b / 4.25f });
                
            }

        }

        if (WasToggled && !Cheat_Private::Misc::WeaponGlow)
        {
            uint64_t actWeaponID = Read<uint64_t>(localPlayer + Offsets::Misc::m_m_hViewModels) & 0xFFFF;
            if (!actWeaponID) return;
            uint64_t currentWeapon = Read<uint64_t>(
                sdk.R5Apex + Offsets::Misc::m_EntityList + (actWeaponID << 5));
            if (!currentWeapon) return;

            Write<uint8_t>(currentWeapon + OFF_GLOW_ENABLE,
                0);
            Write<uint8_t>(currentWeapon + OFF_GLOW_HIGHLIGHT_ID,
                108);
            WasToggled = false;
        }
        if (Cheat_Private::Misc::WeaponGlow && !WasToggled)
            WasToggled = true;
    }
    inline void ItemGlow()
    {
        while (true)
        {
            if (Cheat_Private::Misc::ItemGlow) {
                const uintptr_t highlightSettingsPtr = Read<uintptr_t>(sdk.R5Apex + OFF_GLOW_HIGHLIGHTS);
                if (!highlightSettingsPtr) continue;
                const long highlightSize = 0x34;
                for (int highlightId = 1; highlightId < 50; highlightId++) {
                    const HighlightFunctionBits newGlowMode = { 137,138,35,127 };
                    const HighlightFunctionBits oldGlowMode = Read<HighlightFunctionBits>(highlightSettingsPtr + (highlightSize * highlightId) + 0);
                    // printf("H");
                    Write<HighlightFunctionBits>(highlightSettingsPtr + (highlightSize * highlightId) + 0, newGlowMode);
                }
                // Add a small delay to reduce CPU usage
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }

        }
    }
    inline void SetColor(uintptr_t entity, int conId, uint8_t settingIndex, HighlightFunctionBits setting, HighlightParameter color)
    {

        Write<int>(entity + OFF_GLOW_HIGHLIGHT_ID, 22);
        Write<int>(entity + OFF_GLOW_THROUGH_WALL, 1);
        Write<uint8_t>(entity + conId + OFF_GLOW_FIX, 2);
        Write<float>(entity + OFF_GLOW_DISTANCE, 99999.f);
        Write<int>(entity + OFF_GLOW_HIGHLIGHT_ID + 0, 46);  // Set glow highlight ID
        uint64_t HighlightSettings = Read<uint64_t>(sdk.R5Apex + OFF_GLOW_HIGHLIGHTS);

        Write<HighlightFunctionBits>(HighlightSettings + 0x34 * uint64_t(46) + 4, setting);
        Write<HighlightParameter>(HighlightSettings + 0x34 * uint64_t(46) + 8, color);
    }
    inline void DisableGlow(uintptr_t entity)
    {
        Write<int>(entity + OFF_GLOW_HIGHLIGHT_ID, 0);
        Write<int>(entity + OFF_GLOW_THROUGH_WALL, 0);
        Write<float>(entity + OFF_GLOW_DISTANCE, 0.f);
        uint64_t HighlightSettings = Read<uint64_t>(sdk.R5Apex + OFF_GLOW_HIGHLIGHTS);
        Write<int>(entity + OFF_GLOW_HIGHLIGHT_ID + 0, 0);  // Set glow highlight ID
    }
}; inline Glow* gl;
//blue 4
// yellow 31
// red ol 28
// light white 36
// 50 hard green
//red