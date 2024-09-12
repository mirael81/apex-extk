#pragma once
#include <D3D11.h>
#include <d3d9types.h>
#include <dwmapi.h>
#include <d3d11.h>
#include "Fonts/Russian.hpp"
#include "../img/Cartoon/Peter_Griffen.h"
#include "../img/Cartoon/EKitten.h"

#include "../framework/settings/functions.h"
#include "../framework/data/font.h"
#include "../Custom Radar/Webradar.hpp"
#include "../framework/data/imgui_freetype.h"
#include "../framework/data/texture.h"
#pragma comment(lib, "d3dx11.lib")

#include <D3DX11tex.h>
#pragma comment(lib, "D3DX11.lib")


//Armor ICON
#include "../img/Armor/Common Armor Bytes.h"
#include "../img/Armor/Uncommon Armor Bytes.h"
#include "../img/Armor/Rare Armor Bytes.h"
#include "../img/Armor/Legendary Armor Bytes.h"
#include "../img/Armor/Mythic Armor Bytes.h"
#include "../img/Armor/Helmetbytes.h"

//WEAPON ICON
#include "../img/Weapons/Pistol/p2020 bytes.h"
#include "../img/Weapons/Pistol/alternator bytes.h"
#include "../img/Weapons/Pistol/re45 bytes.h"
#include "../img/Weapons/Pistol/wingmen bytes.h"

#include "../img/Weapons/Shotgun/eva_8_auto bytes.h"
#include "../img/Weapons/Shotgun/mastiff bytes.h"
#include "../img/Weapons/Shotgun/mozambique bytes.h"
#include "../img/Weapons/Shotgun/peacekeeper bytes.h"

#include "../img/Weapons/Rifle/car bytes.h"
#include "../img/Weapons/Rifle/Carbine bytes.h"
#include "../img/Weapons/Rifle/Flatline bytes.h"
#include "../img/Weapons/Rifle/Hemlok bytes.h"
#include "../img/Weapons/Rifle/Prowler bytes.h"
#include "../img/Weapons/Rifle/Rampage bytes.h"
#include "../img/Weapons/Rifle/Repeater bytes.h"
#include "../img/Weapons/Rifle/scout bytes.h"
#include "../img/Weapons/Rifle/Spit-Fire bytes.h"

#include "../img/Weapons/Special/Bow bytes.h"
#include "../img/Weapons/Special/Devotion bytes.h"
#include "../img/Weapons/Special/Knife bytes.h"
#include "../img/Weapons/Special/Kraber bytes.h"
#include "../img/Weapons/Special/R99 Bytes.h"

#include "../img/Weapons/Sniper/ChargedRifle bytes.h"
#include "../img/Weapons/Sniper/DMR bytes.h"
#include "../img/Weapons/Sniper/Sentinel Bytes.h"


#include "../img/Weapons/Energy/EMG bytes.h"
#include "../img/Weapons/Energy/Havoc bytes.h"
#include "../img/Weapons/Energy/Nemisis bytes.h"
#include "../img/Weapons/Energy/Triple bytes.h"
#include "../img/Weapons/Energy/Volt bytes.h"


//meds
#include "../img/Meds/evo-cache bytes.h"
#include "../img/Meds/Med-Kit bytes.h"
#include "../img/Meds/Med-Small bytes.h"
#include "../img/Meds/phynix bytes.h"
#include "../img/Meds/Shield-Large bytes.h"
#include "../img/Meds/Shield-Small bytes.h"


//Ammo
#include "../img/Ammo/EnergyAmmobytes.h"
#include "../img/Ammo/HeavyAmmobytes.h"
#include "../img/Ammo/LightAmmobytes.h"
#include "../img/Ammo/ShotgunAmmobytes.h"
#include "../img/Ammo/SniperAmmobytes.h"

#define ALPHA    (ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar)
#define NO_ALPHA (ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar)
inline int FetSe = 0;
inline int GameSelection = 0;

using namespace ImGui;

inline Player Init;

inline int Segments = 10;
inline HWND window_handle;

inline ID3D11Device* d3d_device;
inline ID3D11DeviceContext* d3d_device_ctx;
inline IDXGISwapChain* d3d_swap_chain;
inline ID3D11RenderTargetView* d3d_render_target;
inline D3DPRESENT_PARAMETERS d3d_present_params;

inline HWND hwnd;
inline ImFont* DefeatureFont;
inline ImFont* Russian;


enum RENDER_INFORMATION : int {
    RENDER_HIJACK_FAILED = 0,
    RENDER_IMGUI_FAILED = 1,
    RENDER_DRAW_FAILED = 2,
    RENDER_SETUP_SUCCESSFUL = 3,
    RENDER_COD_FAILED = 4,
};

enum heads {
    target, sword, car, eye, people, earth, tools, scripts, settings
};

enum subheads {
    aim, rage, other
};

inline bool expand = false;
inline float anim = 0.0f, expand_anim = 0.0f;
inline float accent_c[3] = { 32 / 255.0f, 105 / 255.0f, 244 / 255.0f };

inline ID3D11ShaderResourceView* valomodel = nullptr;

namespace Overlay {
    class OverlayRender {

        HWND Apex_Window = { };

    public:

        RECT rect;

        bool StartCheat = false;

        int Slec = 0;

        bool render_Menu = false;

        bool DoOnce = false;

        auto Setup() -> RENDER_INFORMATION;

        auto get_screen_status() -> bool;
       
        auto Render() -> bool;

        auto ImGui() -> bool;

        HWND find_window(const char* classname, const char* windowname = NULL, int instance = 1);
          
        bool DoesFileExist(const wchar_t* filePath);

        bool StartWindow();

        auto Hijack() -> bool;

        auto Menu() -> void;


        auto Draw() -> void;
    };
} static Overlay::OverlayRender* Renderer = new Overlay::OverlayRender();

inline void __fastcall BeginCheat()
{
    LOG(_("Starting Overlay\n"));
    if (Renderer->Setup() != RENDER_INFORMATION::RENDER_SETUP_SUCCESSFUL)
        LOG(_("Failed To Create Overlay\n "));
    SleepEx(2500, false);
    Renderer->Render();
}