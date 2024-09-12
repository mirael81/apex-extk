#include "Misc.hpp"
#define pCommands  0x22B0D80 // .data:00000000022C2B80 00 00 00 00 00 00 00 00 qword_22C2B80   dq 0                    ; DATA XREF: sub_169780+15E↑w
//48 89 05 69 93 15 02
#define LatestCommandNumber  0x180D17C
#define NetChannel  0x17EC3E0

struct CUserCmd {
    int command_number; //0x0
    int tick_count; //0x4
    float command_time; //0x8
    float viewangle_x; //0xC
    float viewangle_y; //viewangle_x + 0x4
    float viewangle_z; //viewangle_x + 0x8
    char pad_0x18[0x14]; //0x18
    float forwardmove; //0x2C
    float sidemove; //0x30
    float upmove; //0x34
    int buttons; //0x38
    char impulse; //0x3C
};
class PSilent {
public:
    inline void Choke(uintptr_t netChannel) {
        Write<double>(netChannel + 0x2108, 999999);
    }
    inline void ForceChoke(double Packet) {
        uintptr_t netChannel = Read<uintptr_t>(sdk.R5Apex + NetChannel);
        Write<double>(netChannel + 0x2108, Packet);
    }
    inline void ChokeLoop() {
        uintptr_t netChannel = Read<uintptr_t>(sdk.R5Apex + NetChannel);
        uint32_t chokedCommands = Read<uint32_t>(netChannel + 0x2028);


        int attack_state = Read<int>(sdk.R5Apex + 0x0769b658);
        if (chokedCommands > 7) {
            Write<double>(netChannel + 0x2108, 0);
            return;
        }
        if (attack_state != 0) {

            if (chokedCommands == 0) {
                Choke(netChannel);
            }
        }
        else
        {
            if (chokedCommands != 0)
                ForceChoke(0);
        }

    }

    inline void SilentAim(Vector2 CalAngle) {

        uintptr_t netChannel = Read<uintptr_t>(sdk.R5Apex + NetChannel);
        ChokeLoop();
        uint32_t chokedCommands = Read<uint32_t>(netChannel + 0x2028);
        if (chokedCommands <= 0)
        {
            return;
        }       
        int current_number = Read<int>(sdk.R5Apex + LatestCommandNumber);
        int iDesiredCmdNumber = current_number + 1;
        uint64_t cmdBase = Read<uint64_t>(sdk.R5Apex + pCommands + 248);
        uint64_t old_usercmd = (cmdBase + (0x228 * (((uint64_t)iDesiredCmdNumber - 1) % 750)));
        uint64_t Currentusercmd = cmdBase + (0x228 * (((uint64_t)iDesiredCmdNumber) % 750));
        if (old_usercmd < Currentusercmd)
        {
            ChokeLoop();
            Write<Vector2>(old_usercmd + 0xC, Vector2(CalAngle.x, CalAngle.y));
        }
        Write<double>(netChannel + 0x2108, 0);


    }
}; inline PSilent* Silent;

inline void BackTrack()
{
    uintptr_t netChannel = Read<uintptr_t>(sdk.R5Apex + NetChannel);
    uint32_t chokedCommands = Read<uint32_t>(netChannel + 0x2028);
    Silent->ChokeLoop();
    if (chokedCommands <= 0)
    {
        Silent->Choke(0);
        return;
    }
    int current_number = Read<int>(sdk.R5Apex + LatestCommandNumber);
    int iDesiredCmdNumber = current_number + 1;
    uint64_t cmdBase = Read<uint64_t>(sdk.R5Apex + pCommands + 248);
    uint64_t old_usercmd = (cmdBase + (0x228 * (((uint64_t)iDesiredCmdNumber - 1) % 750)));
    uint64_t Currentusercmd = cmdBase + (0x228 * (((uint64_t)iDesiredCmdNumber) % 750));
    Write<float>(Currentusercmd + 0x8, Cheat_Private::Misc::BackTrackStrength * 5);
    Silent->ForceChoke(0);
}