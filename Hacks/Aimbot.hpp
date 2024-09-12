#include "Psilent.hpp"

class Aimbot {
public:
    float TempCross = 9999999.f;

    inline void DoAimbot(SDK::Entity* Entity, SDK::Entity* LocalPlayer, bool vis)
    {

        if (Cheat_Private::ESP::VisCheck && !vis) return;

        Vector3 HeadPosition = Entity->getBonePos(BoneList::Head);
        if (HeadPosition.Empty()) return;

        Vector3 HeadPos = W2S(HeadPosition);
        if (HeadPos.Empty()) return;

        int Bone = BoneList::LowerChest;
        if (Cheat_Private::Aimbot::TargetBone == 0)
            Bone = BoneList::Head;
        else if (Cheat_Private::Aimbot::TargetBone == 1)
            Bone = BoneList::Neck;
        else if (Cheat_Private::Aimbot::TargetBone == 2)
            Bone = BoneList::Pelivs;
        else if (Cheat_Private::Aimbot::TargetBone == 3)
            Bone = BoneList::LowerChest;
        switch (Cheat_Private::Settings::AimbotKeyINDEX)
        {
        case 0:
            Cheat_Private::Aimbot::AimbotKey = 0x01;
            break;
        case 1:
            Cheat_Private::Aimbot::AimbotKey = 0x02;
            break;
        case 2:
            Cheat_Private::Aimbot::AimbotKey = 0x05;
            break;
        case 3:
            Cheat_Private::Aimbot::AimbotKey = 0x06;
            break;
        case 4:
            Cheat_Private::Aimbot::AimbotKey = 0xA4;
            break;
        case 5:
            Cheat_Private::Aimbot::AimbotKey = 0xA0;
            break;
        }
        Vector3 TargetPos = W2S(Entity->getBonePos(Bone));
        if (TargetPos.Empty()) return;

        float LengtToCross = std::sqrt(std::pow(GetSystemMetrics(0) / 2 - HeadPos.x, 2) + std::pow(GetSystemMetrics(1) / 2 - HeadPos.y, 2));
        if (LengtToCross > Cheat_Private::Aimbot::FovCircleSize && LengtToCross > TempCross) return;
        TempCross = LengtToCross;
        if (Cheat_Private::Aimbot::Snapline)
        {
            ImVec2 Size = ImGui::CalcTextSize(_("X"));
            ImGui::GetBackgroundDrawList()->AddText(ImVec2(TargetPos.x - (Size.x / 2), TargetPos.y - (Size.y / 2)), ImColor(Cheat_Private::Aimbot::SnaplineColor[0], Cheat_Private::Aimbot::SnaplineColor[1], Cheat_Private::Aimbot::SnaplineColor[2], 255.f), _("X"));
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(GetSystemMetrics(0) / 2, GetSystemMetrics(1) / 2), ImVec2(TargetPos.x, TargetPos.y), ImColor(Cheat_Private::Aimbot::SnaplineColor[0], Cheat_Private::Aimbot::SnaplineColor[1], Cheat_Private::Aimbot::SnaplineColor[2], 255.f));
        }
        if (GetAsyncKeyState(Cheat_Private::Aimbot::AimbotKey) || GetAsyncKeyState(VK_LMENU))
        {
            Vector3 OldAngle = CalcAngle(LocalPlayer->GetBonePositionByHitBox(0), Entity->getBonePos(Bone));
            Vector3 ViewAngles = Read<Vector3>( LocalPlayer->getAddress() + Offsets::DT_Player::m_viewOffEntity);
            Vector3 delta = OldAngle - ViewAngles;
            Vector3 SilentPos = delta;
            SilentPos.Normalize();
            delta.Normalize();
            delta.y /= Cheat_Private::Aimbot::SmoothingAmount * 2;
            delta.x /= Cheat_Private::Aimbot::SmoothingAmount * 2;

            if (Cheat_Private::Aimbot::PSilent)
            {
                Silent->SilentAim({ OldAngle.x, OldAngle.y });
            }
  
            if (Cheat_Private::Aimbot::VABot)
            {
                LocalPlayer->SetViewAngles(Vector2(ViewAngles.x + delta.x, ViewAngles.y + delta.y));
            }
        }

       
    }


}; inline Aimbot aimbot;
