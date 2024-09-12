#include "Overlay/Overlay.hpp"
#include "Thread/Thread.hpp"
#include "auth/auth.hpp"
#include "protection/antiDbg.h"
#include "Virtualizer/VirtualizerSDK.h"
#include "mapper/kdmapper.hpp"

using namespace KeyAuth;
std::string name = _("oops");
std::string ownerid = _("43ePXQevYL");
std::string secret = _("244b1b3f383a70fa0f20ca24c4a8bc0fd82381aea77dd27eac884e653d15db09");
std::string version = _("1.0");
std::string url = _("https://keyauth.win/api/1.2/"); 
api KeyAuthApp(name, ownerid, secret, version, url, "");

HANDLE iqvw64e_device_handle;
inline std::string APPC = _("xx{XX+XX");

inline std::string GameTitle;
inline std::string MapDriver;

int main()
{
    //NtGdiMakeInfoDC
    SetConsoleTitle(_("Kernel Debugger"));
    kInterface = new Interface("NtGdiMakeInfoDC");

    if (!kInterface->ConnectToDriver())
    {
        LOG(_("Failed To Call Driver\n"));
        Sleep(2000);
        return EXIT_FAILURE;
    }
    localPid = PID("r5apex.exe");
    std::cout << "PID : " << localPid << "\n";
    if (!localPid)
        exit(0);
    sdk.R5Apex = kInterface->BaseAddress(localPid, "r5apex.exe");
    if (!sdk.R5Apex)
        exit(0);

    std::cout << sdk.R5Apex << "\n";
    Sleep(2500);
    system(_("cls"));
  
        system("cls");
        LOG(_("Starting Cheat\n"));
        LOG(_("Close Cheat [EXIT BUTTON]\n"));

        std::thread(&EntityCacha::EntityThread, entCacha).detach();

        std::thread(&Misc::DoMisc, misc).detach();

        std::thread(&LootCacha::LootThread, lootCacha).detach();

        BeginCheat();

}
