#include "Overlay.hpp"


//    Apex_Window = FindWindowA((_("UnityWndClass")), (_("Rust Six")));
//    Apex_Window = FindWindowA((_("Respawn001")), (_("Apex Legends")));

auto Overlay::OverlayRender::Setup() ->RENDER_INFORMATION {
    Apex_Window = FindWindowA((_("Respawn001")), (_("Apex Legends")));
    if (!Apex_Window) {
        LOG(_("Fail to Get Window\n"));
        return RENDER_COD_FAILED;
    }

    if (!Overlay::OverlayRender::Hijack()) return RENDER_HIJACK_FAILED;

    if (!Overlay::OverlayRender::ImGui()) return RENDER_IMGUI_FAILED;
    system(_("cls"));
    std::cout << CYAN << _(R"(

                                       .
                             /^\     .
                        /\   "V"
                       /__\   I      O  o
                      //..\\  I     .
                      \].`[/  I
                      /l\/j\  (]    .  O
                     /. ~~ ,\/I          .
                     \\L__j^\/I       o
                      \/--v}  I     o   .
                      |    |  I   _________
                      |    |  I c(`       ')o
                      |    l  I   \.     ,/      
                    _/j  L l\_!  _//^---^\\_
                 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                           ->XEX Apex<-
)") << _("\n");
    return RENDER_SETUP_SUCCESSFUL;
}
auto Overlay::OverlayRender::get_screen_status() -> bool {
    if (this->Apex_Window == GetForegroundWindow()) {
        return true;
    }

    if (this->Apex_Window == GetActiveWindow()) {
        return true;
    }

    if (GetActiveWindow() == GetForegroundWindow()) {
        return true;
    }

    return false;
}
auto Overlay::OverlayRender::Render() -> bool {
    static RECT rect_og;
    MSG msg = { NULL };
    ZeroMemory(&msg, sizeof(MSG));

    while (msg.message != WM_QUIT)
    {

        UpdateWindow(window_handle);
        ShowWindow(window_handle, SW_SHOW);

        if ((PeekMessageA)(&msg, window_handle, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        ImGuiIO& io = ImGui::GetIO();
    //   / io.ImeWindowHandle = window_handle;
        io.DeltaTime = 1.0f / 60.0f;


        POINT p_cursor;
        GetCursorPos(&p_cursor);
        io.MousePos.x = p_cursor.x;
        io.MousePos.y = p_cursor.y;

        if (GetAsyncKeyState(VK_LBUTTON)) {
            io.MouseDown[0] = true;
            io.MouseClicked[0] = true;
            io.MouseClickedPos[0].x = io.MousePos.x;
            io.MouseClickedPos[0].x = io.MousePos.y;
        }
        else
            io.MouseDown[0] = false;


        Overlay::OverlayRender::Draw();

    }
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    (DestroyWindow)(window_handle);
    system(_("cls"));
    std::cout << GREEN << _(R"(

                                       .
                             /^\     .
                        /\   "V"
                       /__\   I      O  o
                      //..\\  I     .
                      \].`[/  I
                      /l\/j\  (]    .  O
                     /. ~~ ,\/I          .
                     \\L__j^\/I       o
                      \/--v}  I     o   .
                      |    |  I   _________
                      |    |  I c(`       ')o
                      |    l  I   \.     ,/      -Row
                    _/j  L l\_!  _//^---^\\_
                 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                           ->XEX Apex<-
)") << _("\n");
    return true;
}
auto Overlay::OverlayRender::ImGui() -> bool {

    DXGI_SWAP_CHAIN_DESC swap_chain_description;
    ZeroMemory(&swap_chain_description, sizeof(swap_chain_description));
    swap_chain_description.BufferCount = 2;
    swap_chain_description.BufferDesc.Width = 0;
    swap_chain_description.BufferDesc.Height = 0;
    swap_chain_description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swap_chain_description.BufferDesc.RefreshRate.Numerator = 60;
    swap_chain_description.BufferDesc.RefreshRate.Denominator = 1;
    swap_chain_description.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    swap_chain_description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_chain_description.OutputWindow = window_handle;
    swap_chain_description.SampleDesc.Count = 1;
    swap_chain_description.SampleDesc.Quality = 0;
    swap_chain_description.Windowed = 1;
    swap_chain_description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    D3D_FEATURE_LEVEL d3d_feature_lvl;

    const D3D_FEATURE_LEVEL d3d_feature_array[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };

    D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, d3d_feature_array, 2, D3D11_SDK_VERSION, &swap_chain_description, &d3d_swap_chain, &d3d_device, &d3d_feature_lvl, &d3d_device_ctx);

    ID3D11Texture2D* pBackBuffer;

    d3d_swap_chain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

    d3d_device->CreateRenderTargetView(pBackBuffer, NULL, &d3d_render_target);

    pBackBuffer->Release();

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();

    // Our state
    ImVec4 clear_color = GetStyleColorVec4(ImGuiCol_WindowBg);
    io.IniFilename = NULL;

    (void)io;

    ImFontConfig font_config;
    font_config.PixelSnapH = false;
    font_config.OversampleH = 5;
    font_config.OversampleV = 5;
    font_config.RasterizerMultiply = 1.2f;

    static const ImWchar ranges[] =
    {
        0x0020, 0x00FF, // Basic Latin + Latin Supplement
        0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
        0x2DE0, 0x2DFF, // Cyrillic Extended-A
        0xA640, 0xA69F, // Cyrillic Extended-B
        0xE000, 0xE226, // icons
        0,
    };
   

    io.Fonts->AddFontFromMemoryTTF(MiniCondensedRegular, sizeof(MiniCondensedRegular), 16.f, &font_config, ranges);
    io.Fonts->AddFontFromMemoryTTF(Icons, sizeof(Icons), 12.0f, &font_config, ranges);
    io.Fonts->AddFontFromMemoryTTF(ComboArrow, sizeof(ComboArrow), 7.0f, &font_config, ranges);
    io.Fonts->AddFontFromMemoryTTF(ExpandIcon, sizeof(ExpandIcon), 20.0f, &font_config, ranges);

    io.Fonts->AddFontFromMemoryTTF(MiniCondensedRegular, sizeof(MiniCondensedRegular), 19.0f, &font_config, ranges);

 
        //C:\Users\1\Downloads\OCRAEXT.ttf
        //C:\\Windows\\Fonts\\arialbd.ttf
    FontList::Arial = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arialbd.ttf", 17.f);
    FontList::Calibri = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\calibri.ttf", 17.f);
    FontList::Ebrima = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\ebrimabd.ttf", 17.f);
    FontList::Franklin_Gothic = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\framd.ttf", 17.f);
    FontList::Pixel = io.Fonts->AddFontFromMemoryTTF(MiniCondensedRegular, sizeof(MiniCondensedRegular), 19.0f, &font_config, ranges);

    D3DX11_IMAGE_LOAD_INFO CUM;
    ID3DX11ThreadPump* ASS{ nullptr };
    if (!Peter_Texture)
        D3DX11CreateShaderResourceViewFromMemory(d3d_device, PeterData, sizeof(PeterData), &CUM, ASS, &Peter_Texture, 0);
    if (!Kitten_Texture)
        D3DX11CreateShaderResourceViewFromMemory(d3d_device, EkittenData, sizeof(EkittenData), &CUM, ASS, &Kitten_Texture, 0);
    if (!LootTexture::Armor::ShieldTexture)
        D3DX11CreateShaderResourceViewFromMemory(d3d_device, CommonArmorBytes, sizeof(CommonArmorBytes), &CUM, ASS, &LootTexture::Armor::ShieldTexture, 0);
    if (!LootTexture::Armor::HelmetTexture)
        D3DX11CreateShaderResourceViewFromMemory(d3d_device, Helmetbytes, sizeof(Helmetbytes), &CUM, ASS, &LootTexture::Armor::HelmetTexture, 0);
    //ARMOR TEXTURE
    if (!AmrmorICON::CommonArmorTexture)
        D3DX11CreateShaderResourceViewFromMemory(d3d_device, CommonArmorBytes, sizeof(CommonArmorBytes), &CUM, ASS, &AmrmorICON::CommonArmorTexture, 0);

    if (!AmrmorICON::UncommonArmorTexture)
        D3DX11CreateShaderResourceViewFromMemory(d3d_device, UncommonArmorBytes, sizeof(UncommonArmorBytes), &CUM, ASS, &AmrmorICON::UncommonArmorTexture, 0);

    if (!AmrmorICON::RareArmorTexture)
        D3DX11CreateShaderResourceViewFromMemory(d3d_device, RareArmorBytes, sizeof(RareArmorBytes), &CUM, ASS, &AmrmorICON::RareArmorTexture, 0);

    if (!AmrmorICON::LegendaryArmorTexture)
        D3DX11CreateShaderResourceViewFromMemory(d3d_device, LegendaryArmorBytes, sizeof(LegendaryArmorBytes), &CUM, ASS, &AmrmorICON::LegendaryArmorTexture, 0);

    if (!AmrmorICON::MythicArmorTexture)
        D3DX11CreateShaderResourceViewFromMemory(d3d_device, MythicArmorBytes, sizeof(MythicArmorBytes), &CUM, ASS, &AmrmorICON::MythicArmorTexture, 0);
    //meds
            //D3DX11CreateShaderResourceViewFromFileA(d3d_device,"C:\\Users\\1\\Desktop\\Coding\\Src\\XEX\Xex Apex V2\\img\\Meds\\evo-cache.png",&CUM,ASS, &LootTexture::MedTexture::EvoCacheTexture)

    if (!LootTexture::MedTexture::EvoCacheTexture)
        D3DX11CreateShaderResourceViewFromMemory(d3d_device, evobytes, sizeof(evobytes), &CUM, ASS, &LootTexture::MedTexture::EvoCacheTexture, 0);
    if (!LootTexture::MedTexture::LargeMedTexture)
        D3DX11CreateShaderResourceViewFromMemory(d3d_device, Medkitbytes, sizeof(Medkitbytes), &CUM, ASS, &LootTexture::MedTexture::LargeMedTexture, 0);
    if (!LootTexture::MedTexture::LargeShieldTexture)
        D3DX11CreateShaderResourceViewFromMemory(d3d_device, ShieldLargebytes, sizeof(ShieldLargebytes), &CUM, ASS, &LootTexture::MedTexture::LargeShieldTexture, 0);
    if (!LootTexture::MedTexture::PhynioxTexture)
        D3DX11CreateShaderResourceViewFromMemory(d3d_device, phynixbytes, sizeof(phynixbytes), &CUM, ASS, &LootTexture::MedTexture::PhynioxTexture, 0);
    if (!LootTexture::MedTexture::SmallMedTexture)
        D3DX11CreateShaderResourceViewFromMemory(d3d_device, MedsmallBytes, sizeof(MedsmallBytes), &CUM, ASS, &LootTexture::MedTexture::SmallMedTexture, 0);
    if (!LootTexture::MedTexture::SmallShieldTexture)
        D3DX11CreateShaderResourceViewFromMemory(d3d_device, ShieldSmallBytes, sizeof(ShieldSmallBytes), &CUM, ASS, &LootTexture::MedTexture::SmallShieldTexture, 0);
    

    if (!LootTexture::AmmoTexture::EnergyAmmoTexture)
        D3DX11CreateShaderResourceViewFromMemory(d3d_device, EnergyAmmoBytes, sizeof(EnergyAmmoBytes), &CUM, ASS, &LootTexture::AmmoTexture::EnergyAmmoTexture, 0);
    if (!LootTexture::AmmoTexture::HeavyAmmoTexture)
        D3DX11CreateShaderResourceViewFromMemory(d3d_device, HeavyAmmoBytes, sizeof(HeavyAmmoBytes), &CUM, ASS, &LootTexture::AmmoTexture::HeavyAmmoTexture, 0);
    if (!LootTexture::AmmoTexture::LightAmmoTexture)
        D3DX11CreateShaderResourceViewFromMemory(d3d_device, LightAmmoBytes, sizeof(LightAmmoBytes), &CUM, ASS, &LootTexture::AmmoTexture::LightAmmoTexture, 0);
    if (!LootTexture::AmmoTexture::ShotGunAmmoTexture)
        D3DX11CreateShaderResourceViewFromMemory(d3d_device, ShotgunAmmoBytes, sizeof(ShotgunAmmoBytes), &CUM, ASS, &LootTexture::AmmoTexture::ShotGunAmmoTexture, 0);
    if (!LootTexture::AmmoTexture::SniperAmmoTexture)
        D3DX11CreateShaderResourceViewFromMemory(d3d_device, SniperAmmoBytes, sizeof(SniperAmmoBytes), &CUM, ASS, &LootTexture::AmmoTexture::SniperAmmoTexture, 0);

    //WEAPON ICON
    {
        //p202
        if (!WeaponIcon::PistolICON::P2020Texture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, p2020Bytes, sizeof(p2020Bytes), &CUM, ASS, &WeaponIcon::PistolICON::P2020Texture, 0);
        //re45
        if (!WeaponIcon::PistolICON::Re45Texture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, re45Bytes, sizeof(re45Bytes), &CUM, ASS, &WeaponIcon::PistolICON::Re45Texture, 0);
        //alternator
        if (!WeaponIcon::PistolICON::AlternatorTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, alternatorBytes, sizeof(alternatorBytes), &CUM, ASS, &WeaponIcon::PistolICON::AlternatorTexture, 0);
        //wingmen
        if (!WeaponIcon::PistolICON::WingmenTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, wingmenBytes, sizeof(wingmenBytes), &CUM, ASS, &WeaponIcon::PistolICON::WingmenTexture, 0);



        if (!WeaponIcon::ShotgunICON::EVA8Texture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, eva_8_autoBytes, sizeof(eva_8_autoBytes), &CUM, ASS, &WeaponIcon::ShotgunICON::EVA8Texture, 0);
        if (!WeaponIcon::ShotgunICON::MastiffTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, mastiffBytes, sizeof(mastiffBytes), &CUM, ASS, &WeaponIcon::ShotgunICON::MastiffTexture, 0);
        if (!WeaponIcon::ShotgunICON::MozambiqueTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, mozambiqueBytes, sizeof(mozambiqueBytes), &CUM, ASS, &WeaponIcon::ShotgunICON::MozambiqueTexture, 0);
        if (!WeaponIcon::ShotgunICON::peacekeeperTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, peacekeeperBytes, sizeof(peacekeeperBytes), &CUM, ASS, &WeaponIcon::ShotgunICON::peacekeeperTexture, 0);



        if (!WeaponIcon::Rifle::CarTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, carbytes, sizeof(carbytes), &CUM, ASS, &WeaponIcon::Rifle::CarTexture, 0);
        if (!WeaponIcon::Rifle::CarbineTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, CarbineBytes, sizeof(CarbineBytes), &CUM, ASS, &WeaponIcon::Rifle::CarbineTexture, 0);
        if (!WeaponIcon::Rifle::FlatlineTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Flatlinebytes, sizeof(Flatlinebytes), &CUM, ASS, &WeaponIcon::Rifle::FlatlineTexture, 0);
        if (!WeaponIcon::Rifle::HemlockTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Hemlockbytes, sizeof(Hemlockbytes), &CUM, ASS, &WeaponIcon::Rifle::HemlockTexture, 0);
        if (!WeaponIcon::Rifle::ProwlerTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Prowlerbytes, sizeof(Prowlerbytes), &CUM, ASS, &WeaponIcon::Rifle::ProwlerTexture, 0);
        if (!WeaponIcon::Rifle::RampageTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Rampagebytes, sizeof(Rampagebytes), &CUM, ASS, &WeaponIcon::Rifle::RampageTexture, 0);
        if (!WeaponIcon::Rifle::RepeaterTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Repeaterbytes, sizeof(Repeaterbytes), &CUM, ASS, &WeaponIcon::Rifle::RepeaterTexture, 0);
        if (!WeaponIcon::Rifle::ScoutTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, scoutbytes, sizeof(scoutbytes), &CUM, ASS, &WeaponIcon::Rifle::ScoutTexture, 0);
        if (!WeaponIcon::Rifle::SpitFireTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, SpitFirebytes, sizeof(SpitFirebytes), &CUM, ASS, &WeaponIcon::Rifle::SpitFireTexture, 0);

        if (!WeaponIcon::Special::BowTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, BowBytes, sizeof(BowBytes), &CUM, ASS, &WeaponIcon::Special::BowTexture, 0);
        if (!WeaponIcon::Special::DevotionTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Devotionbytes, sizeof(Devotionbytes), &CUM, ASS, &WeaponIcon::Special::DevotionTexture, 0);
        if (!WeaponIcon::Special::KnifeTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Knifebytes, sizeof(Knifebytes), &CUM, ASS, &WeaponIcon::Special::KnifeTexture, 0);
        if (!WeaponIcon::Special::KraberTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Kraberbytes, sizeof(Kraberbytes), &CUM, ASS, &WeaponIcon::Special::KraberTexture, 0);
        if (!WeaponIcon::Special::R99Texture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, R99bytes, sizeof(R99bytes), &CUM, ASS, &WeaponIcon::Special::R99Texture, 0);

        if (!WeaponIcon::Sniper::ChargedRifleTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, ChargedRiflebytes, sizeof(ChargedRiflebytes), &CUM, ASS, &WeaponIcon::Sniper::ChargedRifleTexture, 0);
        if (!WeaponIcon::Sniper::DMRTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, DMRbytes, sizeof(DMRbytes), &CUM, ASS, &WeaponIcon::Sniper::DMRTexture, 0);
        if (!WeaponIcon::Sniper::SentinelTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Sentinelbytes, sizeof(Sentinelbytes), &CUM, ASS, &WeaponIcon::Sniper::SentinelTexture, 0);

        if (!WeaponIcon::Energy::EMGTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, EMGbytes, sizeof(EMGbytes), &CUM, ASS, &WeaponIcon::Energy::EMGTexture, 0);
        if (!WeaponIcon::Energy::HAVOCTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Havocbytes, sizeof(Havocbytes), &CUM, ASS, &WeaponIcon::Energy::HAVOCTexture, 0);
        if (!WeaponIcon::Energy::NemesisTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Nemisisbytes, sizeof(Nemisisbytes), &CUM, ASS, &WeaponIcon::Energy::NemesisTexture, 0);
        if (!WeaponIcon::Energy::TripleTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Triplebytes, sizeof(Triplebytes), &CUM, ASS, &WeaponIcon::Energy::TripleTexture, 0);
        if (!WeaponIcon::Energy::VoltTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Voltbytes, sizeof(Voltbytes), &CUM, ASS, &WeaponIcon::Energy::VoltTexture, 0);
      

    }
    ImGui_ImplWin32_Init(window_handle);

    ImGui_ImplDX11_Init(d3d_device, d3d_device_ctx);

    d3d_device->Release();

    return true;

}
HWND Overlay::OverlayRender::find_window(const char* classname, const char* windowname, int instance) {
    HWND window_hwnd = NULL;
    int count = 0;
    HWND window = NULL;
    do {
        window = FindWindowExA(NULL, window, classname, windowname);
        if (window) {
            count++;
            if (count == instance) {
                window_hwnd = window;
                break;
            }
        }
    } while (window);

    return window_hwnd;
}
bool  Overlay::OverlayRender::DoesFileExist(const wchar_t* filePath) {
    DWORD attributes = GetFileAttributes((LPCSTR)filePath);
    return (attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY));
}
bool Overlay::OverlayRender::StartWindow()
{

    return false;
}
//CEF-OSC-WIDGET, 0x30026, NVIDIA GeForce Overlay, NVIDIA Share.exe (9888): 9892

auto Overlay::OverlayRender::Hijack() -> bool
{
   
    window_handle = FindWindowA((_("MedalOverlayClass")), (_("MedalOverlay")));
    if (!window_handle) return false;
    MARGINS Margin = { -1 };
    DwmExtendFrameIntoClientArea(window_handle, &Margin);
    SetWindowPos(window_handle, 0, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_SHOWWINDOW);
    ShowWindow(window_handle, SW_SHOW);
    UpdateWindow(window_handle);
    return true;
}
auto Overlay::OverlayRender::Menu() -> void
{


    ImGui::End();


    ImGuiIO& io = ImGui::GetIO();
    static heads    category{ target };
    static subheads subcategory{ aim };

    static bool checkbox = false;
    static int  slider, combo, key = 0;


    static float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

    // preview.
    static bool boundingbox, name, healthbar, weapon = false;
    static float box_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

    static int boxtype = 0;

    // applying texture.
    D3DX11_IMAGE_LOAD_INFO AA;
    ID3DX11ThreadPump* FF{ nullptr };

    if (!valomodel)
        D3DX11CreateShaderResourceViewFromMemory(d3d_device, ValorantModel, sizeof(ValorantModel), &AA, FF, &valomodel, 0);

}

auto Overlay::OverlayRender::Draw() -> void {
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.f);

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    if (GetAsyncKeyState(VK_DELETE))
        exit(0);

    if (GetAsyncKeyState(VK_INSERT)&0x1)
        render_Menu = !render_Menu;

    if (render_Menu)
    {
        gui->render();
    }
   Draw::esp->draw_text_outline_font(5, 5, ImColor(0, 122, 255, 255), _("xex"),.5f);
   Draw::esp->draw_text_outline_font(5, 50, ImColor(255, 255, 255, 255), std::string("Map : " + LevelName).c_str(), .5f);
   Draw::esp->draw_text_outline_font(5, 75, ImColor(255, 255, 255, 255), std::string("Player Count : " + std::to_string(int(EntityCount))).c_str(), .5f);

   if (Cheat_Private::Aimbot::FovCircle)
   {
       ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(GetSystemMetrics(0) / 2, GetSystemMetrics(1) / 2), Cheat_Private::Aimbot::FovCircleSize + 1, ImColor(0,0,0,255), 255.f);
       ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(GetSystemMetrics(0) / 2, GetSystemMetrics(1) / 2), Cheat_Private::Aimbot::FovCircleSize - 1, ImColor(0,0,0,255), 255.f);

       ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(GetSystemMetrics(0) / 2, GetSystemMetrics(1) / 2), Cheat_Private::Aimbot::FovCircleSize, ImColor(Cheat_Private::Aimbot::FovCircleColor[0], Cheat_Private::Aimbot::FovCircleColor[1], Cheat_Private::Aimbot::FovCircleColor[2], 255.f));

   }
   player.RunCheat();

   if (Cheat_Private::Config::LoadConfig)
       if (CreateConfig())
       {
           MessageBox(NULL, _("Successfully Created Config"), _("XEX Config System"), MB_OK);
           Cheat_Private::Config::LoadConfig = 0;
       }

   if (Cheat_Private::Config::SaveConfig) {
       if (SaveConfig())
       {
           MessageBox(NULL, _("Successfully Saved Config"), _("XEX Config System"), MB_OK);
           Cheat_Private::Config::SaveConfig = 0;
       }
       else
       {
           MessageBox(NULL, _("Failed To Saved Config"), _("XEX Config System"), MB_OK);
           Cheat_Private::Config::SaveConfig = 0;
       }
   }
   if (Cheat_Private::Config::RunConfig) {
       if (LoadConfig())
       {
           MessageBox(NULL, _("Successfully Loaded Config"), _("XEX Config System"), MB_OK);
           Cheat_Private::Config::RunConfig = 0;
       }
       else
       {
           MessageBox(NULL, _("Failed To Loaded Config"), _("XEX Config System"), MB_OK);
           Cheat_Private::Config::RunConfig = 0;
       }
   }
   //Web.DrawRadar();
    ImGui::Render();
    const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
    d3d_device_ctx->OMSetRenderTargets(1, &d3d_render_target, nullptr);
    d3d_device_ctx->ClearRenderTargetView(d3d_render_target, clear_color_with_alpha);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    d3d_swap_chain->Present(0, 0);
    
}