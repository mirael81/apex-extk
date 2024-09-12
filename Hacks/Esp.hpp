#include "Aimbot.hpp"
#include <map>


inline ImFont* Modern;
inline ImFont* Original;
struct Bounds {
    float left, right, top, bottom;
};

inline ID3D11ShaderResourceView* Peter_Texture;
inline ID3D11ShaderResourceView* Kitten_Texture;

namespace AmrmorICON
{
    inline ID3D11ShaderResourceView* CommonArmorTexture;
    inline ID3D11ShaderResourceView* UncommonArmorTexture;
    inline ID3D11ShaderResourceView* RareArmorTexture;
    inline ID3D11ShaderResourceView* LegendaryArmorTexture;
    inline ID3D11ShaderResourceView* MythicArmorTexture;
}
namespace WeaponIcon
{
    namespace PistolICON
    {
        inline ID3D11ShaderResourceView* P2020Texture;
        inline ID3D11ShaderResourceView* AlternatorTexture;
        inline ID3D11ShaderResourceView* Re45Texture;
        inline ID3D11ShaderResourceView* WingmenTexture;
    }
    namespace ShotgunICON {
        inline ID3D11ShaderResourceView* EVA8Texture;
        inline ID3D11ShaderResourceView* MastiffTexture;
        inline ID3D11ShaderResourceView* MozambiqueTexture;
        inline ID3D11ShaderResourceView* peacekeeperTexture;
    }
    namespace Rifle {
        inline ID3D11ShaderResourceView* CarTexture;
        inline ID3D11ShaderResourceView* CarbineTexture;
        inline ID3D11ShaderResourceView* FlatlineTexture;
        inline ID3D11ShaderResourceView* HemlockTexture;
        inline ID3D11ShaderResourceView* ProwlerTexture;
        inline ID3D11ShaderResourceView* RampageTexture;
        inline ID3D11ShaderResourceView* RepeaterTexture;
        inline ID3D11ShaderResourceView* ScoutTexture;
        inline ID3D11ShaderResourceView* SpitFireTexture;
    }
    namespace Special {
        inline ID3D11ShaderResourceView* BowTexture;
        inline ID3D11ShaderResourceView* DevotionTexture;
        inline ID3D11ShaderResourceView* KnifeTexture;
        inline ID3D11ShaderResourceView* KraberTexture;
        inline ID3D11ShaderResourceView* R99Texture;
    }
    namespace Sniper {
        inline ID3D11ShaderResourceView* ChargedRifleTexture;
        inline ID3D11ShaderResourceView* DMRTexture;
        inline ID3D11ShaderResourceView* SentinelTexture;

    }
    namespace Energy {
        inline ID3D11ShaderResourceView* NemesisTexture;
        inline ID3D11ShaderResourceView* VoltTexture;
        inline ID3D11ShaderResourceView* TripleTexture;
        inline ID3D11ShaderResourceView* EMGTexture;
        inline ID3D11ShaderResourceView* HAVOCTexture;

    }
}
inline std::vector<std::pair<int, int>> bones = {
    {8, 5}, // Head to CenterChest
    {5, 33}, {33, 34}, {34, 35}, {35, 36}, {36, 37}, // Left Arm
    {5, 10}, {10, 11}, {11, 12}, {12, 13}, {13, 14}, // Right Arm
    {5, 0}, // CenterChest to Dick
    {0, 55}, {55, 56}, {56, 58}, {58, 59}, // Left Leg
    {0, 60}, {60, 62}, {62, 63}, {63, 64}  // Right Leg
};
inline std::map<int, Vector3> boneScreenPositions;

inline Vector3 BoneSkePos(SDK::Entity* player, int boneIndex) {
    Vector3 bonePos = player->getBonePos(boneIndex);
    return W2S(bonePos);
}
inline void DrawLineSkeleton(Vector3 start, Vector3 end) {
  /*  ImGui::GetBackgroundDrawList()->AddLine(ImVec2(start.x + 1, start.y + 1), ImVec2(end.x + 1, end.y + 1),
        ImColor(0.f,0.f,0.f, 255.f));
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(start.x - 1, start.y - 1), ImVec2(end.x - 1, end.y - 1),
        ImColor(0.f, 0.f, 0.f, 255.f));*/
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(start.x, start.y), ImVec2(end.x, end.y),
        ImColor(Cheat_Private::ESP::SkeletonColor[0], Cheat_Private::ESP::SkeletonColor[1], Cheat_Private::ESP::SkeletonColor[2], 255.f));
}


class Esp {
public:
    bool WasGlow = false;


    inline void DrawEsp(SDK::Entity* Player, SDK::Entity* LocalPlayer, int Health, bool vis, int i)
    {
        Vector3 BasePos = Player->Get_Position();
        if (BasePos.Empty()) return;

        Vector3 LocalPos = LocalPlayer->Get_Position();
        float Distance = LocalPos.DistTo(BasePos) / 16.0f;
           
        uint64_t LocalPlayerAddy = LocalPlayer->getAddress();
        if (!LocalPlayerAddy)return;

        Vector3 ViewAngles = LocalPlayer->ViewAngles();

        if (Cheat_Private::ESP::Radar) {
            float radarSize = Cheat_Private::ESP::RadarSize * 80;  // Size of the radar

            // Screen dimensions
            const float screenWidth = ImGui::GetIO().DisplaySize.x;
            const float screenHeight = ImGui::GetIO().DisplaySize.y;

            // Radar positioning
            const float radarPosX = screenWidth - radarSize - 40.0f;  // Position near the bottom-right corner with margin
            const float radarPosY = screenHeight - radarSize - 40.0f;

            float radarCenter[2];
            radarCenter[0] = radarPosX + (radarSize / 2.0f);
            radarCenter[1] = radarPosY + (radarSize / 2.0f);

            ImDrawList* drawList = ImGui::GetBackgroundDrawList();

            // Draw radar background
            drawList->AddCircleFilled(ImVec2(radarCenter[0], radarCenter[1]), radarSize / 2.0f, ImColor(0, 0, 0, 150), 64);  // Semi-transparent black background
            drawList->AddCircle(ImVec2(radarCenter[0], radarCenter[1]), radarSize / 2.0f, ImColor(255, 255, 255, 50), 64, 2.0f);  // White border

            // Draw compass rose
            float compassSize = radarSize / 3.0f;
            ImVec2 northPoint = ImVec2(radarCenter[0], radarCenter[1] - compassSize);
            ImVec2 eastPoint = ImVec2(radarCenter[0] + compassSize, radarCenter[1]);
            ImVec2 southPoint = ImVec2(radarCenter[0], radarCenter[1] + compassSize);
            ImVec2 westPoint = ImVec2(radarCenter[0] - compassSize, radarCenter[1]);

            drawList->AddText(ImVec2(northPoint.x - 5, northPoint.y - 10), ImColor(255, 255, 255, 150), "N");
            drawList->AddText(ImVec2(eastPoint.x + 5, eastPoint.y - 5), ImColor(255, 255, 255, 150), "E");
            drawList->AddText(ImVec2(southPoint.x - 5, southPoint.y + 5), ImColor(255, 255, 255, 150), "S");
            drawList->AddText(ImVec2(westPoint.x - 15, westPoint.y - 5), ImColor(255, 255, 255, 150), "W");

            // Draw distance rings
            float ringSpacing = radarSize / 6.0f;  // Distance between rings
            for (int i = 1; i <= 3; ++i) {
                drawList->AddCircle(ImVec2(radarCenter[0], radarCenter[1]), i * ringSpacing, ImColor(255, 255, 255, 30), 64, 1.0f);  // Distant rings
            }

            float screenPos[2];

            // Get enemy position relative to the player and scale down
            screenPos[0] = (LocalPos.x - BasePos.x) / 10.0f;
            screenPos[1] = (LocalPos.y - BasePos.y) / 10.0f;

            // Rotate and translate to radar center
            screenPos[0] *= -1;
            screenPos[0] += radarCenter[0];
            screenPos[1] += radarCenter[1];

            // Apply rotation based on player view angles
            float rotatedPoint[2];
            RotatePoint(screenPos, radarCenter, ViewAngles.y - 90, rotatedPoint);

            // Clamp the rotated point to stay within radar bounds
            float radarRadius = radarSize / 2.0f - 10.0f;  // Ensure blips stay within radar
            float dx = rotatedPoint[0] - radarCenter[0];
            float dy = rotatedPoint[1] - radarCenter[1];
            float dist = sqrt(dx * dx + dy * dy);
            if (dist > radarRadius) {
                rotatedPoint[0] = radarCenter[0] + (dx / dist) * radarRadius;
                rotatedPoint[1] = radarCenter[1] + (dy / dist) * radarRadius;
            }

            // Enemy blip icon with bright color
            float enemySize = 6.0f;
            ImVec2 enemyBlip = ImVec2(rotatedPoint[0], rotatedPoint[1]);
            ImColor enemyColor = ImColor(255, 50, 50, 255);  // Bright red enemy blip
            drawList->AddCircleFilled(enemyBlip, enemySize, enemyColor);  // Red enemy blip

            // Draw local player icon (centered)
            drawList->AddTriangleFilled(
                ImVec2(radarCenter[0], radarCenter[1] - 6),
                ImVec2(radarCenter[0] - 5, radarCenter[1] + 5),
                ImVec2(radarCenter[0] + 5, radarCenter[1] + 5),
                ImColor(0, 255, 0, 255)  // Green triangle for player
            );
        }

        
        Vector3 HeadPosition = Player->getBonePos(BoneList::Head);
        if (HeadPosition.Empty()) return;

        Vector3 Pos = W2S(BasePos);
        Vector3 HeadPos = W2S(HeadPosition);
        if (Pos.Empty() || HeadPos.Empty()) return;

        int Height = HeadPos.y - Pos.y;
        int Width = Height / 2;

        

        // Drawing filled box if enabled
        if (Cheat_Private::ESP::Filledbox)
        {
            Draw::esp->DrawFilledBox(Pos.x - (Width / 2), Pos.y, Width, Height, ImColor(15.f, 15.f, 15.f, 155.f), .5f);
        }

        // Drawing box with visibility check if enabled
        if (Cheat_Private::ESP::Box)
        {
            ImColor boxColor = vis
                ? ImColor(Cheat_Private::ESP::VisColor[0], Cheat_Private::ESP::VisColor[1], Cheat_Private::ESP::VisColor[2], 255.f)
                : ImColor(Cheat_Private::ESP::NonVisColor[0], Cheat_Private::ESP::NonVisColor[1], Cheat_Private::ESP::NonVisColor[2], 255.f);

            if (!Cheat_Private::ESP::VisCheck)
                boxColor = ImColor{ Cheat_Private::ESP::BoxColor[0], Cheat_Private::ESP::BoxColor[1], Cheat_Private::ESP::BoxColor[2], 255.f };

            Draw::esp->DrawBox(Pos.x - (Width / 2), Pos.y, Width, Height, ImColor(0, 0, 0, 255), 2);
            Draw::esp->DrawBox(Pos.x - (Width / 2), Pos.y, Width, Height, boxColor, .1f);

        }

        // Draw Alert if visibility check and alert enabled
        if (Cheat_Private::ESP::alert && vis && visentcount > 0)
        {
            std::string alertText = _("ALERT ENEMY VISIBLE: ") + std::to_string(int(visentcount)) + _(" VISIBLE PLAYER'S");
            ImVec2 size = ImGui::CalcTextSize(alertText.c_str());
            ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), 18.f, ImVec2((GetSystemMetrics(0) / 2) - (size.x / 2), 300), ImColor(255, 0, 0, 255), alertText.c_str());
        }


        if (Cheat_Private::ESP::FOVArrows)
        {
            int radar_range = 200; // Example value, adjust according to your radar size

            bool shit = false;

         
            Vector3 EntityPos = WorldToRadar(ViewAngles.y, BasePos, LocalPos, 0, 0, Vector3(250, 250, 0), shit);

            int x = static_cast<int>(EntityPos.x);
            int y = static_cast<int>(EntityPos.y);

            auto angle = Vector3();
            Vector3 Temp = Vector3((250 / 2) - x, (250 / 2) - y, 0.f);

            // Adjusting the angle calculation
            VectorAnglesRadar(Temp, angle);
            const auto angle_yaw_rad = DEG2RAD(angle.y + 180.f);

            // Calculate new point positions
            const auto new_point_x = (250 / 2) + (radar_range) / 2 * 8 * cosf(angle_yaw_rad);
            const auto new_point_y = (250 / 2) + (radar_range) / 2 * 8 * sinf(angle_yaw_rad);

            std::array<Vector3, 3> points
            {
                Vector3(new_point_x - ((90) / 4 + 3.5f) / 2, new_point_y - ((radar_range) / 4 + 3.5f) / 2, 0.f),
                Vector3(new_point_x + ((90) / 4 + 3.5f) / 4, new_point_y, 0.f),
                Vector3(new_point_x - ((90) / 4 + 3.5f) / 2, new_point_y + ((radar_range) / 4 + 3.5f) / 2, 0.f)
            };

            // Rotate and draw the triangle around the calculated point
            RotateTriangle(points, angle.y + 180.f);
            ImGui::GetBackgroundDrawList()->AddTriangleFilled(
                { points.at(0).x, points.at(0).y },
                { points.at(1).x, points.at(1).y },
                { points.at(2).x, points.at(2).y },
                ImColor(255, 255, 255, 255)
            );
        }
      

        //ill never get back the 11 hours i spent :(
        if (Cheat_Private::ESP::WeaponICON)
        {
            struct BoxDimensions {
                int width;
                int height;
                int yheight;
            };

            BoxDimensions weaponBox = { 55, 30, 75 };
            BoxDimensions ammoBox = { 30, 15, 35 };

            if (Cheat_Private::ESP::Level || Cheat_Private::ESP::Distance) {
                weaponBox.yheight = 75;
                ammoBox.yheight = 45;
            }

            int boxX = Pos.x - (weaponBox.width / 2);
            int boxY = Pos.y + weaponBox.yheight;
            int flippedBoxY = boxY - weaponBox.height;

            int AboxX = Pos.x - (ammoBox.width / 2);
            int AboxY = Pos.y + ammoBox.yheight;
            int AflippedBoxY = AboxY - ammoBox.height;

            static const std::unordered_map<int, ID3D11ShaderResourceView*> weaponTextureMap = {
                {112, WeaponIcon::PistolICON::P2020Texture},
                {85, WeaponIcon::PistolICON::Re45Texture},
                {84, WeaponIcon::PistolICON::AlternatorTexture},
                {115, WeaponIcon::PistolICON::WingmenTexture},
                {92, WeaponIcon::ShotgunICON::EVA8Texture},
                {101, WeaponIcon::ShotgunICON::MastiffTexture},
                {109, WeaponIcon::ShotgunICON::peacekeeperTexture},
                {102, WeaponIcon::ShotgunICON::MozambiqueTexture},
                {119, WeaponIcon::Rifle::CarTexture},
                {0, WeaponIcon::Rifle::CarbineTexture},
                {94, WeaponIcon::Rifle::FlatlineTexture},
                {96, WeaponIcon::Rifle::HemlockTexture},
                {107, WeaponIcon::Rifle::ProwlerTexture},
                {6, WeaponIcon::Rifle::RampageTexture},
                {95, WeaponIcon::Rifle::RepeaterTexture},
                {113, WeaponIcon::Rifle::SpitFireTexture},
                {2, WeaponIcon::Special::BowTexture},
                {89, WeaponIcon::Special::DevotionTexture},
                {176, WeaponIcon::Special::KnifeTexture},
                {98, WeaponIcon::Special::KraberTexture},
                {111, WeaponIcon::Special::R99Texture},
                {87, WeaponIcon::Sniper::ChargedRifleTexture},
                {90, WeaponIcon::Sniper::DMRTexture},
                {1, WeaponIcon::Sniper::SentinelTexture},
                {120, WeaponIcon::Energy::NemesisTexture},
                {117, WeaponIcon::Energy::VoltTexture},
                {114, WeaponIcon::Energy::TripleTexture},
                {99, WeaponIcon::Energy::EMGTexture},
                {91, WeaponIcon::Energy::HAVOCTexture},
            };

          
            int weapon_index = Player->GetWeaponIndex();

            auto it = weaponTextureMap.find(weapon_index);
            if (it != weaponTextureMap.end()) {
                ID3D11ShaderResourceView* texture = it->second;
                {
                    ImColor WeaponICONColor = vis
                        ? ImColor(Cheat_Private::ESP::VisColor[0], Cheat_Private::ESP::VisColor[1], Cheat_Private::ESP::VisColor[2], 255.f)
                        : ImColor(Cheat_Private::ESP::NonVisColor[0], Cheat_Private::ESP::NonVisColor[1], Cheat_Private::ESP::NonVisColor[2], 255.f);

                    if (!Cheat_Private::ESP::VisCheck)
                        WeaponICONColor = ImColor{ Cheat_Private::ESP::WeaponIconColor[0], Cheat_Private::ESP::WeaponIconColor[1], Cheat_Private::ESP::WeaponIconColor[2], 255.f };

                    if (weapon_index == 112 || weapon_index == 85 || weapon_index == 84 || weapon_index == 115) { // my dumb ass imported pistols with an incorrect width and height so this checks for it and fixes my mistake
                        Draw::menu->DrawRotatedImageWithBoxColor(texture, AboxX, AflippedBoxY, ammoBox.width, -ammoBox.height, WeaponICONColor);
                    }
                    else {
                        Draw::menu->DrawRotatedImageWithBoxColor(texture, boxX, flippedBoxY, weaponBox.width, -weaponBox.height, WeaponICONColor);
                    }
                }
            }
        
        }
        if (Cheat_Private::ESP::Skeleton)
        {
            // Define the positions for bones
            Vector3 Head = Player->getBonePos(8);
            Vector3 CenterChest = Player->getBonePos(5);
            Vector3 Dick = Player->getBonePos(0);

            Vector3 LeftShoulder = Player->getBonePos(33);
            Vector3 LeftUpperArm = Player->getBonePos(34);
            Vector3 LeftArmJoint = Player->getBonePos(35);
            Vector3 LeftForArm = Player->getBonePos(36);
            Vector3 LeftHand = Player->getBonePos(37);

            Vector3 RightShoulder = Player->getBonePos(10);
            Vector3 RightUpperArm = Player->getBonePos(11);
            Vector3 RightArmJoint = Player->getBonePos(12);
            Vector3 RightForArm = Player->getBonePos(13);
            Vector3 RightHand = Player->getBonePos(14);

            Vector3 LeftHip = Player->getBonePos(55);
            Vector3 LeftHipJoint = Player->getBonePos(56);
            Vector3 LeftAnkle = Player->getBonePos(58);
            Vector3 LeftFoot = Player->getBonePos(59);

            Vector3 RightHip = Player->getBonePos(60);
            Vector3 RightHipJoint = Player->getBonePos(62);
            Vector3 RightAnkle = Player->getBonePos(63);
            Vector3 RightFoot = Player->getBonePos(64);

            // Transform the bone positions to screen space
            Vector3 HeadScreen = W2S(Head);
            Vector3 CenterChestScreen = W2S(CenterChest);
            Vector3 DickScreen = W2S(Dick);

            Vector3 LeftShoulderScreen = W2S(LeftShoulder);
            Vector3 LeftUpperArmScreen = W2S(LeftUpperArm);
            Vector3 LeftArmJointScreen = W2S(LeftArmJoint);
            Vector3 LeftForArmScreen = W2S(LeftForArm);
            Vector3 LeftHandScreen = W2S(LeftHand);

            Vector3 RightShoulderScreen = W2S(RightShoulder);
            Vector3 RightUpperArmScreen = W2S(RightUpperArm);
            Vector3 RightArmJointScreen = W2S(RightArmJoint);
            Vector3 RightForArmScreen = W2S(RightForArm);
            Vector3 RightHandScreen = W2S(RightHand);

            Vector3 LeftHipScreen = W2S(LeftHip);
            Vector3 LeftHipJointScreen = W2S(LeftHipJoint);
            Vector3 LeftAnkleScreen = W2S(LeftAnkle);
            Vector3 LeftFootScreen = W2S(LeftFoot);

            Vector3 RightHipScreen = W2S(RightHip);
            Vector3 RightHipJointScreen = W2S(RightHipJoint);
            Vector3 RightAnkleScreen = W2S(RightAnkle);
            Vector3 RightFootScreen = W2S(RightFoot);

            // Check if the screen positions are valid
            if (HeadScreen.Empty()) return;
            if (CenterChestScreen.Empty()) return;
            if (DickScreen.Empty()) return;

            if (LeftShoulderScreen.Empty()) return;
            if (LeftUpperArmScreen.Empty()) return;
            if (LeftArmJointScreen.Empty()) return;
            if (LeftForArmScreen.Empty()) return;
            if (LeftHandScreen.Empty()) return;

            if (RightShoulderScreen.Empty()) return;
            if (RightUpperArmScreen.Empty()) return;
            if (RightArmJointScreen.Empty()) return;
            if (RightForArmScreen.Empty()) return;
            if (RightHandScreen.Empty()) return;

            if (LeftHipScreen.Empty()) return;
            if (LeftHipJointScreen.Empty()) return;
            if (LeftAnkleScreen.Empty()) return;
            if (LeftFootScreen.Empty()) return;

            if (RightHipScreen.Empty()) return;
            if (RightHipJointScreen.Empty()) return;
            if (RightAnkleScreen.Empty()) return;
            if (RightFootScreen.Empty()) return;

            // Draw the skeleton lines

            // Head To UpperCenter
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(HeadScreen.x, HeadScreen.y), ImVec2(CenterChestScreen.x, CenterChestScreen.y), ImColor(Cheat_Private::ESP::SkeletonColor[0], Cheat_Private::ESP::SkeletonColor[1], Cheat_Private::ESP::SkeletonColor[2], 255.f));

            // Left Arm
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(CenterChestScreen.x, CenterChestScreen.y), ImVec2(LeftShoulderScreen.x, LeftShoulderScreen.y), ImColor(Cheat_Private::ESP::SkeletonColor[0], Cheat_Private::ESP::SkeletonColor[1], Cheat_Private::ESP::SkeletonColor[2], 255.f));
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(LeftShoulderScreen.x, LeftShoulderScreen.y), ImVec2(LeftUpperArmScreen.x, LeftUpperArmScreen.y), ImColor(Cheat_Private::ESP::SkeletonColor[0], Cheat_Private::ESP::SkeletonColor[1], Cheat_Private::ESP::SkeletonColor[2], 255.f));
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(LeftUpperArmScreen.x, LeftUpperArmScreen.y), ImVec2(LeftArmJointScreen.x, LeftArmJointScreen.y), ImColor(Cheat_Private::ESP::SkeletonColor[0], Cheat_Private::ESP::SkeletonColor[1], Cheat_Private::ESP::SkeletonColor[2], 255.f));
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(LeftArmJointScreen.x, LeftArmJointScreen.y), ImVec2(LeftForArmScreen.x, LeftForArmScreen.y), ImColor(Cheat_Private::ESP::SkeletonColor[0], Cheat_Private::ESP::SkeletonColor[1], Cheat_Private::ESP::SkeletonColor[2], 255.f));
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(LeftForArmScreen.x, LeftForArmScreen.y), ImVec2(LeftHandScreen.x, LeftHandScreen.y), ImColor(Cheat_Private::ESP::SkeletonColor[0], Cheat_Private::ESP::SkeletonColor[1], Cheat_Private::ESP::SkeletonColor[2], 255.f));

            // Right Arm
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(CenterChestScreen.x, CenterChestScreen.y), ImVec2(RightShoulderScreen.x, RightShoulderScreen.y), ImColor(Cheat_Private::ESP::SkeletonColor[0], Cheat_Private::ESP::SkeletonColor[1], Cheat_Private::ESP::SkeletonColor[2], 255.f));
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(RightShoulderScreen.x, RightShoulderScreen.y), ImVec2(RightUpperArmScreen.x, RightUpperArmScreen.y), ImColor(Cheat_Private::ESP::SkeletonColor[0], Cheat_Private::ESP::SkeletonColor[1], Cheat_Private::ESP::SkeletonColor[2], 255.f));
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(RightUpperArmScreen.x, RightUpperArmScreen.y), ImVec2(RightArmJointScreen.x, RightArmJointScreen.y), ImColor(Cheat_Private::ESP::SkeletonColor[0], Cheat_Private::ESP::SkeletonColor[1], Cheat_Private::ESP::SkeletonColor[2], 255.f));
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(RightArmJointScreen.x, RightArmJointScreen.y), ImVec2(RightForArmScreen.x, RightForArmScreen.y), ImColor(Cheat_Private::ESP::SkeletonColor[0], Cheat_Private::ESP::SkeletonColor[1], Cheat_Private::ESP::SkeletonColor[2], 255.f));
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(RightForArmScreen.x, RightForArmScreen.y), ImVec2(RightHandScreen.x, RightHandScreen.y), ImColor(Cheat_Private::ESP::SkeletonColor[0], Cheat_Private::ESP::SkeletonColor[1], Cheat_Private::ESP::SkeletonColor[2], 255.f));

            // CenterChest to Dick
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(CenterChestScreen.x, CenterChestScreen.y), ImVec2(DickScreen.x, DickScreen.y), ImColor(Cheat_Private::ESP::SkeletonColor[0], Cheat_Private::ESP::SkeletonColor[1], Cheat_Private::ESP::SkeletonColor[2], 255.f));

            // Dick to Left Hip
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(DickScreen.x, DickScreen.y), ImVec2(LeftHipScreen.x, LeftHipScreen.y), ImColor(Cheat_Private::ESP::SkeletonColor[0], Cheat_Private::ESP::SkeletonColor[1], Cheat_Private::ESP::SkeletonColor[2], 255.f));
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(LeftHipScreen.x, LeftHipScreen.y), ImVec2(LeftHipJointScreen.x, LeftHipJointScreen.y), ImColor(Cheat_Private::ESP::SkeletonColor[0], Cheat_Private::ESP::SkeletonColor[1], Cheat_Private::ESP::SkeletonColor[2], 255.f));
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(LeftHipJointScreen.x, LeftHipJointScreen.y), ImVec2(LeftAnkleScreen.x, LeftAnkleScreen.y), ImColor(Cheat_Private::ESP::SkeletonColor[0], Cheat_Private::ESP::SkeletonColor[1], Cheat_Private::ESP::SkeletonColor[2], 255.f));
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(LeftAnkleScreen.x, LeftAnkleScreen.y), ImVec2(LeftFootScreen.x, LeftFootScreen.y), ImColor(Cheat_Private::ESP::SkeletonColor[0], Cheat_Private::ESP::SkeletonColor[1], Cheat_Private::ESP::SkeletonColor[2], 255.f));

            // Dick to Right Hip
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(DickScreen.x, DickScreen.y), ImVec2(RightHipScreen.x, RightHipScreen.y), ImColor(Cheat_Private::ESP::SkeletonColor[0], Cheat_Private::ESP::SkeletonColor[1], Cheat_Private::ESP::SkeletonColor[2], 255.f));
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(RightHipScreen.x, RightHipScreen.y), ImVec2(RightHipJointScreen.x, RightHipJointScreen.y), ImColor(Cheat_Private::ESP::SkeletonColor[0], Cheat_Private::ESP::SkeletonColor[1], Cheat_Private::ESP::SkeletonColor[2], 255.f));
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(RightHipJointScreen.x, RightHipJointScreen.y), ImVec2(RightAnkleScreen.x, RightAnkleScreen.y), ImColor(Cheat_Private::ESP::SkeletonColor[0], Cheat_Private::ESP::SkeletonColor[1], Cheat_Private::ESP::SkeletonColor[2], 255.f));
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(RightAnkleScreen.x, RightAnkleScreen.y), ImVec2(RightFootScreen.x, RightFootScreen.y), ImColor(Cheat_Private::ESP::SkeletonColor[0], Cheat_Private::ESP::SkeletonColor[1], Cheat_Private::ESP::SkeletonColor[2], 255.f));

        }
        // Drawing Corner Box
        if (Cheat_Private::ESP::CornerBox)
        {
            ImColor cornerBoxColor = vis
                ? ImColor(Cheat_Private::ESP::VisColor[0], Cheat_Private::ESP::VisColor[1], Cheat_Private::ESP::VisColor[2], 255.f)
                : ImColor(Cheat_Private::ESP::NonVisColor[0], Cheat_Private::ESP::NonVisColor[1], Cheat_Private::ESP::NonVisColor[2], 255.f);

            if (!Cheat_Private::ESP::VisCheck)
                cornerBoxColor = ImColor{ Cheat_Private::ESP::BoxColor[0], Cheat_Private::ESP::BoxColor[1], Cheat_Private::ESP::BoxColor[2], 255.f };

            Draw::esp->DrawCorneredBox(Pos.x - (Width / 2), Pos.y, Width, Height, cornerBoxColor, .5f);
        }
        if (Cheat_Private::ESP::PeterGriffen)
        {
            Draw::menu->DrawRotatedImageWithBox(Peter_Texture, Pos.x - (Width / 2), Pos.y, Width, Height);
        }
        if (Cheat_Private::ESP::EKitten)
        {
            Draw::menu->DrawRotatedImageWithBox(Kitten_Texture, Pos.x - (Width / 2), Pos.y, Width, Height);
        }
        // Drawing Death Box
        if (Cheat_Private::ESP::DeathBox)
        {
            ImColor deathBoxColor = vis
                ? ImColor(Cheat_Private::ESP::VisColor[0], Cheat_Private::ESP::VisColor[1], Cheat_Private::ESP::VisColor[2], 255.f)
                : ImColor(Cheat_Private::ESP::NonVisColor[0], Cheat_Private::ESP::NonVisColor[1], Cheat_Private::ESP::NonVisColor[2], 255.f);

            if (!Cheat_Private::ESP::VisCheck)
                deathBoxColor = ImColor{ Cheat_Private::ESP::BoxColor[0], Cheat_Private::ESP::BoxColor[1], Cheat_Private::ESP::BoxColor[2], 255.f };

            Draw::esp->DeathBox(Pos.x - (Width / 2), Pos.y, Width, Height, deathBoxColor, .5f);
        }

        // Drawing SernEsp
        if (Cheat_Private::ESP::SernEsp && Distance <= 100)
        {
            Draw::esp->SeerHealth(HeadPos.x, HeadPos.y, Player->Get_Current_shield(), Player->Get_Max_shield(), Player->Get_shield_type(), Health);
        }

        // Drawing Skeleton ESP
        if (Cheat_Private::ESP::Skeleton)
        {
            //boneEsp(Player);
        }

        if (Cheat_Private::ESP::Level)
        {
            std::string levelText = std::to_string(int(Player->Get_Level())) + _("LV");
            ImVec2 sizeLevel = ImGui::CalcTextSize(levelText.c_str());

            ImColor levelColor = vis
                ? ImColor(Cheat_Private::ESP::VisColor[0], Cheat_Private::ESP::VisColor[1], Cheat_Private::ESP::VisColor[2], 255.f)
                : ImColor(Cheat_Private::ESP::NonVisColor[0], Cheat_Private::ESP::NonVisColor[1], Cheat_Private::ESP::NonVisColor[2], 255.f);

            if (!Cheat_Private::ESP::VisCheck)
                levelColor = ImColor{ Cheat_Private::ESP::LevelColor[0], Cheat_Private::ESP::LevelColor[1], Cheat_Private::ESP::LevelColor[2], 255.f };

            int offset = Cheat_Private::ESP::Distance ? -sizeLevel.x / 2 : 0;
            if(!Cheat_Private::ESP::Distance)
                Draw::esp->draw_text_outline_font(Pos.x - (sizeLevel.x / 2), (Pos.y - (sizeLevel.y / 2)) + 5, levelColor, levelText.c_str(), 1);
        }

        // Drawing Distance Text
        if (Cheat_Private::ESP::Distance)
        {
            std::string distanceText = std::to_string(int(Distance)) + _("M");
            ImVec2 sizeDistance = ImGui::CalcTextSize(distanceText.c_str());

            ImColor distanceColor = vis
                ? ImColor(Cheat_Private::ESP::VisColor[0], Cheat_Private::ESP::VisColor[1], Cheat_Private::ESP::VisColor[2], 255.f)
                : ImColor(Cheat_Private::ESP::NonVisColor[0], Cheat_Private::ESP::NonVisColor[1], Cheat_Private::ESP::NonVisColor[2], 255.f);

            if (!Cheat_Private::ESP::VisCheck)
                distanceColor = ImColor{ Cheat_Private::ESP::DistanceColor[0], Cheat_Private::ESP::DistanceColor[1], Cheat_Private::ESP::DistanceColor[2], 255.f };
            int offset = Cheat_Private::ESP::Level ? sizeDistance.x / 2 : 0;

            if (Cheat_Private::ESP::Level)
            {
                std::string NewText = std::to_string(int(Player->Get_Level())) + _("LV") +" : " + distanceText;
                ImVec2 sizeLevel = ImGui::CalcTextSize(NewText.c_str());
                Draw::esp->draw_text_outline_font(Pos.x - (sizeLevel.x / 2), (Pos.y - (sizeLevel.y / 2)) + 5, distanceColor, NewText.c_str(), 1);

            }
            else {
                Draw::esp->draw_text_outline_font(Pos.x - (sizeDistance.x / 2), (Pos.y - (sizeDistance.y / 2)) + 5, distanceColor, distanceText.c_str(), 1);
            }
        }
      
        // Drawing weapon ESP
        if (Cheat_Private::ESP::Name)
        {
            std::string nameText = get_weapon_name(Player->getAddress());
            ImVec2 size = ImGui::CalcTextSize(nameText.c_str());

            ImColor nameColor = vis
                ? ImColor(Cheat_Private::ESP::VisColor[0], Cheat_Private::ESP::VisColor[1], Cheat_Private::ESP::VisColor[2], 255.f)
                : ImColor(Cheat_Private::ESP::NonVisColor[0], Cheat_Private::ESP::NonVisColor[1], Cheat_Private::ESP::NonVisColor[2], 255.f);

            if (!Cheat_Private::ESP::VisCheck)
                nameColor = ImColor{ Cheat_Private::ESP::NameColor[0], Cheat_Private::ESP::NameColor[1], Cheat_Private::ESP::NameColor[2], 255.f };
            if (Cheat_Private::ESP::Weapon)
            {
                if (Cheat_Private::ESP::Operator)
                {
                    Draw::esp->draw_text_outline_font(Pos.x - (size.x / 2), ((Pos.y - (size.y / 2)) + Height) - 35, nameColor, nameText.c_str(), 1);

                }
                else {
                    Draw::esp->draw_text_outline_font(Pos.x - (size.x / 2), ((Pos.y - (size.y / 2)) + Height) - 20, nameColor, nameText.c_str(), 1);
                }
            }
            else {
                if (Cheat_Private::ESP::Operator)
                {
                    Draw::esp->draw_text_outline_font(Pos.x - (size.x / 2), ((Pos.y - (size.y / 2)) + Height) - 20, nameColor, nameText.c_str(), 1);

                }
                else {
                    Draw::esp->draw_text_outline_font(Pos.x - (size.x / 2), ((Pos.y - (size.y / 2)) + Height) - 5, nameColor, nameText.c_str(), 1);
                }

            }
        }

        // Drawing Operator ESP
        if (Cheat_Private::ESP::Operator)
        {
            std::string operatorText = Player->GetOperator();
            ImVec2 size = ImGui::CalcTextSize(operatorText.c_str());

            ImColor operatorColor = vis
                ? ImColor(Cheat_Private::ESP::VisColor[0], Cheat_Private::ESP::VisColor[1], Cheat_Private::ESP::VisColor[2], 255.f)
                : ImColor(Cheat_Private::ESP::NonVisColor[0], Cheat_Private::ESP::NonVisColor[1], Cheat_Private::ESP::NonVisColor[2], 255.f);

            if (!Cheat_Private::ESP::VisCheck)
                operatorColor = ImColor{ Cheat_Private::ESP::OperatorColor[0], Cheat_Private::ESP::OperatorColor[1], Cheat_Private::ESP::OperatorColor[2], 255.f };

            if (Cheat_Private::ESP::Weapon)
            {
                if (Cheat_Private::ESP::Name)
                {
                    Draw::esp->draw_text_outline_font(Pos.x - (size.x / 2), ((Pos.y - (size.y / 2)) + Height) - 20, operatorColor, operatorText.c_str(), 1);

                }
                else {
                    Draw::esp->draw_text_outline_font(Pos.x - (size.x / 2), ((Pos.y - (size.y / 2)) + Height) - 20, operatorColor, operatorText.c_str(), 1);
                }
            }
            else {
                if (Cheat_Private::ESP::Name)
                {
                    Draw::esp->draw_text_outline_font(Pos.x - (size.x / 2), ((Pos.y - (size.y / 2)) + Height) - 5, operatorColor, operatorText.c_str(), 1);

                }
                else {
                    Draw::esp->draw_text_outline_font(Pos.x - (size.x / 2), ((Pos.y - (size.y / 2)) + Height) - 5, operatorColor, operatorText.c_str(), 1);
                }

            }

        }
        // Name
        if (Cheat_Private::ESP::Weapon)
        {
            std::string nameText = Player->GetName(i);
            ImVec2 size = ImGui::CalcTextSize(nameText.c_str());

            ImColor nameColor = vis
                ? ImColor(Cheat_Private::ESP::VisColor[0], Cheat_Private::ESP::VisColor[1], Cheat_Private::ESP::VisColor[2], 255.f)
                : ImColor(Cheat_Private::ESP::NonVisColor[0], Cheat_Private::ESP::NonVisColor[1], Cheat_Private::ESP::NonVisColor[2], 255.f);

            if (!Cheat_Private::ESP::VisCheck)
                nameColor = ImColor{ Cheat_Private::ESP::WeaponColor[0], Cheat_Private::ESP::WeaponColor[1], Cheat_Private::ESP::WeaponColor[2], 255.f };

            Draw::esp->draw_text_outline_font(Pos.x - (size.x / 2), ((Pos.y - (size.y / 2)) + Height) - 5, nameColor, nameText.c_str(), 1);
        }


     

        // Draw Shield Bar
        if (Cheat_Private::ESP::Shield)
        {
            float spec = Pos.x - (Width / 3.2f);
            int shield = Player->Get_Current_shield();
            int shieldType = Player->Get_shield_type();

            ImColor shieldColor;
            bool drawShield = true;
            switch (shieldType)
            {
            case 5: shieldColor = ImColor(200, 15, 50); break;
            case 4: shieldColor = ImColor(205, 195, 50); break;
            case 3: shieldColor = ImColor(150, 65, 245); break;
            case 2: shieldColor = ImColor(25, 115, 175); break;
            case 1: shieldColor = ImColor(215, 215, 215); break;
            default: drawShield = false; break;
            }

            if (drawShield && shield != 0)
            {
                float barWidth = 4.0f; // Make the bar slightly wider for better visibility
                ImVec2 barPosMin = ImVec2(spec + Width * 1.1f, Pos.y);
                ImVec2 barPosMax = ImVec2(spec + Width * 1.1f + barWidth, Pos.y + Height);

                // Draw the background bar with a border
                ImGui::GetBackgroundDrawList()->AddRectFilled(barPosMin, barPosMax, ImColor(0, 0, 0, 255));
                ImGui::GetBackgroundDrawList()->AddRect(barPosMin, barPosMax, ImColor(255, 255, 255, 150)); // Add a semi-transparent white border

                // Calculate the height of the shield bar based on the shield percentage
                float shieldBarHeight = shield * Height / 125.0f;
                ImVec2 shieldBarMax = ImVec2(spec + Width * 1.1f + barWidth, Pos.y + shieldBarHeight);

                // Draw the shield bar with a gradient
                ImColor gradientStart = ImColor(shieldColor.Value.x, shieldColor.Value.y, shieldColor.Value.z, 0.8f); // Slightly transparent at the top
                ImColor gradientEnd = ImColor(shieldColor.Value.x, shieldColor.Value.y, shieldColor.Value.z, 1.0f);   // Solid color at the bottom

                ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(barPosMin, shieldBarMax, gradientStart, gradientStart, gradientEnd, gradientEnd);

                // Add slits representing every 25% (25%, 50%, 75%)
                for (int i = 1; i <= 3; i++)
                {
                    float slitPosY = Pos.y + (Height * i * 0.25f);
                    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(barPosMin.x, slitPosY), ImVec2(barPosMax.x, slitPosY), ImColor(0, 0, 0, 255));
                }

                // Add some styling, such as a gloss effect
                ImVec2 glossMin = ImVec2(barPosMin.x, barPosMin.y);
                ImVec2 glossMax = ImVec2(barPosMax.x, barPosMin.y + shieldBarHeight * 0.3f); // Gloss only on the upper part
                ImGui::GetBackgroundDrawList()->AddRectFilled(glossMin, glossMax, ImColor(255, 255, 255, 50)); // Add a soft white gloss effect
            }
        }

        if (Cheat_Private::ESP::Health)
        {
            if (Cheat_Private::ESP::Shield && Player->Get_Current_shield() != 0)
                return;

            // Determine the color based on health percentage
            ImColor healthColor = Health > 75 ? ImColor(0, 255, 0, 255) : Health > 45 ? ImColor(255, 99, 0, 255) : ImColor(255, 0, 0, 255);

            // Calculate positions and dimensions
            float spec = Pos.x - (Width / 3.2f);
            float barWidth = 4.0f; // Make the bar slightly wider for better visibility
            ImVec2 barPosMin = ImVec2(spec + Width * 1.1f, Pos.y);
            ImVec2 barPosMax = ImVec2(spec + Width * 1.1f + barWidth, Pos.y + Height);
            ImVec2 A = { barPosMin.x + 1, barPosMin.y + 1 };
            ImVec2 B = { barPosMax.x + 1, barPosMax.y + 1 };
            // Draw the background bar with a border
            ImGui::GetBackgroundDrawList()->AddRectFilled(A, B, ImColor(0, 0, 0, 255));

            ImGui::GetBackgroundDrawList()->AddRectFilled(barPosMin, barPosMax, ImColor(0, 0, 0, 255));
            ImGui::GetBackgroundDrawList()->AddRect(barPosMin, barPosMax, ImColor(255, 255, 255, 150)); // Add a semi-transparent white border

            // Calculate the height of the health bar based on the health percentage
            float healthBarHeight = Health * Height / 100.0f;
            ImVec2 healthBarMax = ImVec2(spec + Width * 1.1f + barWidth, Pos.y + healthBarHeight);

            // Draw the health bar with a gradient
            ImColor gradientStart = ImColor(healthColor.Value.x, healthColor.Value.y, healthColor.Value.z, 0.8f); // Slightly transparent at the top
            ImColor gradientEnd = ImColor(healthColor.Value.x, healthColor.Value.y, healthColor.Value.z, 1.0f);   // Solid color at the bottom

            ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(barPosMin, healthBarMax, gradientStart, gradientStart, gradientEnd, gradientEnd);

            // Add slits representing every 25% (25%, 50%, 75%)
            for (int i = 1; i <= 3; i++)
            {
                float slitPosY = Pos.y + (Height * i * 0.25f);
                ImGui::GetBackgroundDrawList()->AddLine(ImVec2(barPosMin.x, slitPosY), ImVec2(barPosMax.x, slitPosY), ImColor(0, 0, 0, 255));
            }

            // Add some styling, such as a gloss effect
            ImVec2 glossMin = ImVec2(barPosMin.x, barPosMin.y);
            ImVec2 glossMax = ImVec2(barPosMax.x, barPosMin.y + healthBarHeight * 0.3f); // Gloss only on the upper part
            ImGui::GetBackgroundDrawList()->AddRectFilled(glossMin, glossMax, ImColor(255, 255, 255, 50)); // Add a soft white gloss effect
        }

        
    }
};
         
inline Esp esp;

