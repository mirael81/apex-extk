#include "Esp.hpp"
inline int TestPas[4] = { 1474,3207,30 };
inline int TestPaB[4] = { 25,25,30 };
// Declare MedList properly
namespace LootTexture
{
    namespace MedTexture {
        inline ID3D11ShaderResourceView* SmallMedTexture;
        inline ID3D11ShaderResourceView* LargeMedTexture;
        inline ID3D11ShaderResourceView* SmallShieldTexture;
        inline ID3D11ShaderResourceView* LargeShieldTexture;
        inline ID3D11ShaderResourceView* PhynioxTexture;
        inline ID3D11ShaderResourceView* EvoCacheTexture;
    }
    namespace AmmoTexture {
        inline ID3D11ShaderResourceView* SniperAmmoTexture;
        inline ID3D11ShaderResourceView* ShotGunAmmoTexture;
        inline ID3D11ShaderResourceView* LightAmmoTexture;
        inline ID3D11ShaderResourceView* HeavyAmmoTexture;
        inline ID3D11ShaderResourceView* EnergyAmmoTexture;
    }
    namespace Armor {
        inline ID3D11ShaderResourceView* ShieldTexture;
        inline ID3D11ShaderResourceView* HelmetTexture;
    }
}
inline std::vector<std::pair<int, std::string>> MedList = {
    {202, "Sringe"},
    {201, "Med-Kit"},
    {335, "Evo-Cache"},
    {204, "Shield-Cell"},
    {203, "Shield-Battery"},
    {200, "Phoenix-Kit"}
};

inline std::vector<std::pair<int, std::string>> LightGunList = {
    {117, "P2020"},
    {126, "RE-45"},
    {45, "Alternator"},
    {82, "R-301"},
    {77, "M600 Spit-fire"},
    {40, "G7 Scout"}
};

inline std::vector<std::pair<int, std::string>> ShotGunlist = {
    {98, "mozambique"},
    {87, "EVA"},
    {93, "PeaceKeeper"},
    {2, "Mastiff"}
};

inline std::vector<std::pair<int, std::string>> ShieldList = {
    {220, "Shield Level 1"},
    {221, "Shield Level 2"},
    {222, "Shield Level 3"},
    {223, "Shield Level 4"}
};

inline std::vector<std::pair<int, std::string>> HelmetList = {
      {205, "Helmet Level 1"},
    {206, "Helmet Level 2"},
    {207, "Helmet Level 3"},
    {208, "Helmet Level 4"}
};
//154 Sniper Ammo
//152 Shotgun ammo
//150 Light Ammo
//153 Heavy Ammo
//151 Energy Ammo
//
//
inline bool ToggleMode = false;
class Loot {
public:
    inline void DrawLoot(SDK::Loot* loot, SDK::Entity* LocalPlayer)
    {
       Vector3 Pos = loot->GetPosition();
      float Distance = calcDist(LocalPlayer->Get_Position(), Pos);
      switch (Cheat_Private::Loot::BattleIndex)
      {
      case 0:
          Cheat_Private::Loot::BattleKey = 0x01;
          break;
      case 1:
          Cheat_Private::Loot::BattleKey = 0x02;
          break;
      case 2:
          Cheat_Private::Loot::BattleKey = 0x05;
          break;
      case 3:
          Cheat_Private::Loot::BattleKey = 0x06;
          break;
      case 4:
          Cheat_Private::Loot::BattleKey = 0xA4;
          break;
      case 5:
          Cheat_Private::Loot::BattleKey = 0xA0;
          break;
      }
      if (Cheat_Private::Loot::BattleMode && GetAsyncKeyState(Cheat_Private::Loot::BattleKey))
      {
          if ((Distance / 16) > Cheat_Private::Loot::lootDistance) return;
          int LootIndex = loot->GetIndex();
          Vector3 HeadPos = Pos;
          HeadPos.z += 25;
          // Calculate height and width for drawing
          float Height = HeadPos.y - Pos.y;
          float Width = Height / 2.0f;  // Use 2.0f to ensure float division

          // Convert world position to screen-space
          Vector3 Spair = W2S(Pos);
          if (Spair.Empty()) return;  // Return if position is not on screen
           //ImGui::GetBackgroundDrawList()->AddText(ImVec2(Spair.x, Spair.y), ImColor(255, 255, 255, 255), std::string(std::to_string(LootIndex)).c_str());


          struct BoxDimensions {
              int width;
              int height;
              int yheight;
          };

          BoxDimensions weaponBox = { 55, 30, 35 };
          BoxDimensions ammoBox = { 35,15,11 }; // 35 15, 11
          BoxDimensions HealthBox = { 50,37,1 }; //50 37 1
          BoxDimensions WammoBox = { 30, 30, 35 };
          BoxDimensions ShiledBox = { TestPaB[0], TestPaB[1], TestPaB [2]};

          weaponBox.yheight = 45;
          ShiledBox.yheight = 45;
          ammoBox.yheight = 45;
          HealthBox.yheight = 45;
          WammoBox.yheight = 45;

          int boxX = Spair.x - (weaponBox.width / 2);
          int boxY = Spair.y + weaponBox.yheight;
          int flippedBoxY = boxY - weaponBox.height;

          int AboxX = Spair.x - (ammoBox.width / 2);
          int AboxY = Spair.y + ammoBox.yheight;
          int AflippedBoxY = AboxY - ammoBox.height;


          int BboxX = Spair.x - (HealthBox.width / 2);
          int BboxY = Spair.y + HealthBox.yheight;
          int BflippedBoxY = BboxY - HealthBox.height;

          int KboxX = Spair.x - (WammoBox.width / 2);
          int KboxY = Spair.y + WammoBox.yheight;
          int KflippedBoxY = KboxY - WammoBox.height;

          int XboxX = Spair.x - (ShiledBox.width / 2);
          int XboxY = Spair.y + ShiledBox.yheight;
          int XflippedBoxY = XboxY - ShiledBox.height;
          // Drawing logic for Med items
          if (Cheat_Private::Loot::Medic)
          {
              for (size_t MedicIndex = 0; MedicIndex < MedList.size(); MedicIndex++)  // Iterate through MedList
              {
                  auto MedicLoot = MedList[MedicIndex];

                  if (MedicLoot.first == LootIndex)  // If loot index matches
                  {
                      std::string Text = MedicLoot.second;

                      // Calculate text size for centering
                      ImVec2 Size = ImGui::CalcTextSize(Text.c_str());

                      // Draw text if enabled
                      if (Cheat_Private::Loot::Text)
                      {
                          Draw::esp->draw_text_outline_font(
                              Spair.x - (Size.x / 2.0f), Spair.y - (Size.y / 2.0f),  // Use screen-space coordinates (Spair)
                              ImColor(
                                  Cheat_Private::Loot::MedicaColor[0],
                                  Cheat_Private::Loot::MedicaColor[1],
                                  Cheat_Private::Loot::MedicaColor[2], 255.f),
                              Text.c_str(), 1);
                      }


                      if (Cheat_Private::Loot::Icon)
                      {

                          switch (MedicLoot.first)
                          {
                          case 202:
                              Draw::menu->DrawRotatedImageWithBox(LootTexture::MedTexture::SmallMedTexture, BboxX, BflippedBoxY, weaponBox.width, -HealthBox.height);

                              break;
                          case 201:
                              Draw::menu->DrawRotatedImageWithBox(LootTexture::MedTexture::LargeMedTexture, BboxX, BflippedBoxY, weaponBox.width, -HealthBox.height);
                              break;
                          case 335:
                              Draw::menu->DrawRotatedImageWithBox(LootTexture::MedTexture::EvoCacheTexture, BboxX, BflippedBoxY, weaponBox.width, -HealthBox.height);
                              break;
                          case 204:
                              Draw::menu->DrawRotatedImageWithBox(LootTexture::MedTexture::SmallShieldTexture, BboxX, BflippedBoxY, weaponBox.width, -HealthBox.height);
                              break;
                          case 203:
                              Draw::menu->DrawRotatedImageWithBox(LootTexture::MedTexture::LargeShieldTexture, BboxX, BflippedBoxY, weaponBox.width, -HealthBox.height);
                              break;
                          case 200:
                              Draw::menu->DrawRotatedImageWithBox(LootTexture::MedTexture::PhynioxTexture, BboxX, BflippedBoxY, weaponBox.width, -HealthBox.height);
                              break;
                          }
                      }
                  }
              }
          }
          if (Cheat_Private::Loot::LightWeapon)
          {
              for (size_t LightGunIndex = 0; LightGunIndex < LightGunList.size(); LightGunIndex++)  // Iterate through MedList
              {
                  auto LightGun = LightGunList[LightGunIndex];

                  if (LightGun.first == LootIndex)  // If loot index matches
                  {
                      std::string Text = LightGun.second;

                      // Calculate text size for centering
                      ImVec2 Size = ImGui::CalcTextSize(Text.c_str());

                      // Draw text if enabled
                      if (Cheat_Private::Loot::Text)
                      {
                          Draw::esp->draw_text_outline_font(
                              Spair.x - (Size.x / 2.0f), Spair.y - (Size.y / 2.0f),  // Use screen-space coordinates (Spair)
                              ImColor(
                                  Cheat_Private::Loot::LightWeaponColor[0],
                                  Cheat_Private::Loot::LightWeaponColor[1],
                                  Cheat_Private::Loot::LightWeaponColor[2], 255.f),
                              Text.c_str(), 1);
                      }


                      if (Cheat_Private::Loot::Icon)
                      {


                          switch (LightGun.first)
                          {
                          case 117:
                              Draw::menu->DrawRotatedImageWithBox(WeaponIcon::PistolICON::P2020Texture, AboxX, AflippedBoxY, ammoBox.width, -ammoBox.height);
                              break;
                          case 126:
                              Draw::menu->DrawRotatedImageWithBox(WeaponIcon::PistolICON::Re45Texture, AboxX, AflippedBoxY, ammoBox.width, -ammoBox.height);
                              break;
                          case 45:
                              Draw::menu->DrawRotatedImageWithBox(WeaponIcon::PistolICON::AlternatorTexture, AboxX, AflippedBoxY, ammoBox.width, -ammoBox.height);
                              break;
                          case 82:
                              Draw::menu->DrawRotatedImageWithBox(WeaponIcon::Rifle::CarbineTexture, boxX, flippedBoxY, weaponBox.width, -weaponBox.height);
                              break;
                          case 77:
                              Draw::menu->DrawRotatedImageWithBox(WeaponIcon::Rifle::SpitFireTexture, boxX, flippedBoxY, weaponBox.width, -weaponBox.height);
                              break;
                          case 40:
                              Draw::menu->DrawRotatedImageWithBox(WeaponIcon::Rifle::ScoutTexture, boxX, flippedBoxY, weaponBox.width, -weaponBox.height);
                              break;
                          }
                      }
                  }
              }
          }
          if (Cheat_Private::Loot::Shotgun)
          {
              for (size_t ShotgunIndex = 0; ShotgunIndex < ShotGunlist.size(); ShotgunIndex++)  // Iterate through MedList
              {
                  auto Shotgun = ShotGunlist[ShotgunIndex];

                  if (Shotgun.first == LootIndex)  // If loot index matches
                  {
                      std::string Text = Shotgun.second;

                      // Calculate text size for centering
                      ImVec2 Size = ImGui::CalcTextSize(Text.c_str());

                      // Draw text if enabled
                      if (Cheat_Private::Loot::Text)
                      {
                          Draw::esp->draw_text_outline_font(
                              Spair.x - (Size.x / 2.0f), Spair.y - (Size.y / 2.0f),  // Use screen-space coordinates (Spair)
                              ImColor(
                                  Cheat_Private::Loot::ShotGunColor[0],
                                  Cheat_Private::Loot::ShotGunColor[1],
                                  Cheat_Private::Loot::ShotGunColor[2], 255.f),
                              Text.c_str(), 1);
                      }


                      if (Cheat_Private::Loot::Icon)
                      {


                          switch (Shotgun.first)
                          {
                          case 98:
                              Draw::menu->DrawRotatedImageWithBox(WeaponIcon::ShotgunICON::MozambiqueTexture, AboxX, AflippedBoxY, ammoBox.width, -ammoBox.height);
                              break;
                          case 87:
                              Draw::menu->DrawRotatedImageWithBox(WeaponIcon::ShotgunICON::EVA8Texture, AboxX, AflippedBoxY, ammoBox.width, -ammoBox.height);
                              break;
                          case 93:
                              Draw::menu->DrawRotatedImageWithBox(WeaponIcon::ShotgunICON::peacekeeperTexture, AboxX, AflippedBoxY, ammoBox.width, -ammoBox.height);
                              break;
                          case 2:
                              Draw::menu->DrawRotatedImageWithBox(WeaponIcon::ShotgunICON::MastiffTexture, boxX, flippedBoxY, weaponBox.width, -weaponBox.height);
                              break;

                          }
                      }
                  }
              }
          }
          if (Cheat_Private::Loot::Shield)
          {
              for (size_t ShieldIndex = 0; ShieldIndex < ShieldList.size(); ShieldIndex++)  // Iterate through MedList
              {
                  auto Shield = ShieldList[ShieldIndex];

                  if (Shield.first == LootIndex)  // If loot index matches
                  {
                      std::string Text = Shield.second;

                      // Calculate text size for centering
                      ImVec2 Size = ImGui::CalcTextSize(Text.c_str());

                      // Draw text if enabled
                      if (Cheat_Private::Loot::Text)
                      {
                          Draw::esp->draw_text_outline_font(
                              Spair.x - (Size.x / 2.0f), Spair.y - (Size.y / 2.0f),  // Use screen-space coordinates (Spair)
                              ImColor(
                                  Cheat_Private::Loot::ShieldColor[0],
                                  Cheat_Private::Loot::ShieldColor[1],
                                  Cheat_Private::Loot::ShieldColor[2], 255.f),
                              Text.c_str(), 1);
                      }


                      if (Cheat_Private::Loot::Icon)
                      {


                          switch (Shield.first)
                          {
                          case 220:
                              Draw::menu->DrawRotatedImageWithBoxColor(LootTexture::Armor::ShieldTexture, XboxX, XflippedBoxY, ShiledBox.width, -ShiledBox.height, { 168, 168,168, 255});
                              break;
                          case 221:
                              Draw::menu->DrawRotatedImageWithBoxColor(LootTexture::Armor::ShieldTexture, XboxX, XflippedBoxY, ShiledBox.width, -ShiledBox.height, { 11, 40,254, 255 });
                              break;
                          case 222:
                              Draw::menu->DrawRotatedImageWithBoxColor(LootTexture::Armor::ShieldTexture, XboxX, XflippedBoxY, ShiledBox.width, -ShiledBox.height, { 244, 12,136, 255 });
                              break;
                          case 223:
                              Draw::menu->DrawRotatedImageWithBoxColor(LootTexture::Armor::ShieldTexture, XboxX, XflippedBoxY, ShiledBox.width, -ShiledBox.height, { 255, 0,0, 255 });
                              break;

                          }
                      }
                  }
              }
          }
          if (Cheat_Private::Loot::Helmet)
          {
              for (size_t HelmetIndex = 0; HelmetIndex < HelmetList.size(); HelmetIndex++)  // Iterate through MedList
              {
                  auto Helmet = HelmetList[HelmetIndex];

                  if (Helmet.first == LootIndex)  // If loot index matches
                  {
                      std::string Text = Helmet.second;

                      // Calculate text size for centering
                      ImVec2 Size = ImGui::CalcTextSize(Text.c_str());

                      // Draw text if enabled
                      if (Cheat_Private::Loot::Text)
                      {
                          Draw::esp->draw_text_outline_font(
                              Spair.x - (Size.x / 2.0f), Spair.y - (Size.y / 2.0f),  // Use screen-space coordinates (Spair)
                              ImColor(
                                  Cheat_Private::Loot::HelmetColor[0],
                                  Cheat_Private::Loot::HelmetColor[1],
                                  Cheat_Private::Loot::HelmetColor[2], 255.f),
                              Text.c_str(), 1);
                      }


                      if (Cheat_Private::Loot::Icon)
                      {


                          switch (Helmet.first)
                          {
                          case 205:
                              Draw::menu->DrawRotatedImageWithBoxColor(LootTexture::Armor::HelmetTexture, XboxX, XflippedBoxY, ShiledBox.width, -ShiledBox.height, { 168, 168,168, 255 });
                              break;
                          case 206:
                              Draw::menu->DrawRotatedImageWithBoxColor(LootTexture::Armor::HelmetTexture, XboxX, XflippedBoxY, ShiledBox.width, -ShiledBox.height, { 11, 40,254, 255 });
                              break;
                          case 207:
                              Draw::menu->DrawRotatedImageWithBoxColor(LootTexture::Armor::HelmetTexture, XboxX, XflippedBoxY, ShiledBox.width, -ShiledBox.height, { 244, 12,136, 255 });
                              break;
                          case 208:
                              Draw::menu->DrawRotatedImageWithBoxColor(LootTexture::Armor::HelmetTexture, XboxX, XflippedBoxY, ShiledBox.width, -ShiledBox.height, { 255, 0,0, 255 });
                              break;

                          }
                      }
                  }
              }
          }
          if (Cheat_Private::Loot::EnergyAmmo && LootIndex == 151)
          {
              {
                  std::string Text = "Energy Ammo";

                  // Calculate text size for centering
                  ImVec2 Size = ImGui::CalcTextSize(Text.c_str());
                  if (Cheat_Private::Loot::Icon)
                  {
                      Draw::menu->DrawRotatedImageWithBox(LootTexture::AmmoTexture::EnergyAmmoTexture, KboxX, KflippedBoxY, WammoBox.width, -WammoBox.height);

                  }

                  // Draw text if enabled
                  if (Cheat_Private::Loot::Text)
                  {
                      Draw::esp->draw_text_outline_font(
                          Spair.x - (Size.x / 2.0f), Spair.y - (Size.y / 2.0f),  // Use screen-space coordinates (Spair)
                          ImColor(
                              Cheat_Private::Loot::EnergyAmmoColor[0],
                              Cheat_Private::Loot::EnergyAmmoColor[1],
                              Cheat_Private::Loot::EnergyAmmoColor[2], 255.f),
                          Text.c_str(), 1);
                  }



              }
          }
          if (Cheat_Private::Loot::ShotgunAmmo && LootIndex == 152)
          {
              {
                  std::string Text = "Shotgun Ammo";

                  // Calculate text size for centering
                  ImVec2 Size = ImGui::CalcTextSize(Text.c_str());

                  // Draw text if enabled
                  if (Cheat_Private::Loot::Text)
                  {
                      Draw::esp->draw_text_outline_font(
                          Spair.x - (Size.x / 2.0f), Spair.y - (Size.y / 2.0f),  // Use screen-space coordinates (Spair)
                          ImColor(
                              Cheat_Private::Loot::ShotGunAmmoColor[0],
                              Cheat_Private::Loot::ShotGunAmmoColor[1],
                              Cheat_Private::Loot::ShotGunAmmoColor[2], 255.f),
                          Text.c_str(), 1);
                  }

                  if (Cheat_Private::Loot::Icon)
                      Draw::menu->DrawRotatedImageWithBox(LootTexture::AmmoTexture::ShotGunAmmoTexture, KboxX, KflippedBoxY, WammoBox.width, -WammoBox.height);


              }
          }
          if (Cheat_Private::Loot::LightAmmo && LootIndex == 150)
          {
              {
                  std::string Text = "Light Ammo";

                  // Calculate text size for centering
                  ImVec2 Size = ImGui::CalcTextSize(Text.c_str());

                  // Draw text if enabled
                  if (Cheat_Private::Loot::Text)
                  {
                      Draw::esp->draw_text_outline_font(
                          Spair.x - (Size.x / 2.0f), Spair.y - (Size.y / 2.0f),  // Use screen-space coordinates (Spair)
                          ImColor(
                              Cheat_Private::Loot::LightAmmoColor[0],
                              Cheat_Private::Loot::LightAmmoColor[1],
                              Cheat_Private::Loot::LightAmmoColor[2], 255.f),
                          Text.c_str(), 1);
                  }

                  if (Cheat_Private::Loot::Icon)
                      Draw::menu->DrawRotatedImageWithBox(LootTexture::AmmoTexture::LightAmmoTexture, KboxX, KflippedBoxY, WammoBox.width, -WammoBox.height);


              }

            

          }
          if (Cheat_Private::Loot::SniperAmmo && LootIndex == 154)
          {
              {
                  std::string Text = "Sniper Ammo";

                  // Calculate text size for centering
                  ImVec2 Size = ImGui::CalcTextSize(Text.c_str());

                  // Draw text if enabled
                  if (Cheat_Private::Loot::Text)
                  {
                      Draw::esp->draw_text_outline_font(
                          Spair.x - (Size.x / 2.0f), Spair.y - (Size.y / 2.0f),  // Use screen-space coordinates (Spair)
                          ImColor(
                              Cheat_Private::Loot::SniperAmmoColor[0],
                              Cheat_Private::Loot::SniperAmmoColor[1],
                              Cheat_Private::Loot::SniperAmmoColor[2], 255.f),
                          Text.c_str(), 1);
                  }

                  if (Cheat_Private::Loot::Icon)
                      Draw::menu->DrawRotatedImageWithBox(LootTexture::AmmoTexture::SniperAmmoTexture, KboxX, KflippedBoxY, WammoBox.width, -WammoBox.height);


              }
          }
          if (Cheat_Private::Loot::HeavyAmmo && LootIndex == 153)
          {
              {
                  std::string Text = "Heavy Ammo";

                  // Calculate text size for centering
                  ImVec2 Size = ImGui::CalcTextSize(Text.c_str());

                  // Draw text if enabled
                  if (Cheat_Private::Loot::Text)
                  {
                      Draw::esp->draw_text_outline_font(
                          Spair.x - (Size.x / 2.0f), Spair.y - (Size.y / 2.0f),  // Use screen-space coordinates (Spair)
                          ImColor(
                              Cheat_Private::Loot::HeavyAmmoColor[0],
                              Cheat_Private::Loot::HeavyAmmoColor[1],
                              Cheat_Private::Loot::HeavyAmmoColor[2], 255.f),
                          Text.c_str(), 1);
                  }

                  if (Cheat_Private::Loot::Icon)
                      Draw::menu->DrawRotatedImageWithBox(LootTexture::AmmoTexture::HeavyAmmoTexture, KboxX, KflippedBoxY, WammoBox.width, -WammoBox.height);


              }

              if (Cheat_Private::Loot::HeavyAmmo && LootIndex == 153)
              {
                  {
                      std::string Text = "Heavy Ammo";

                      // Calculate text size for centering
                      ImVec2 Size = ImGui::CalcTextSize(Text.c_str());

                      // Draw text if enabled
                      if (Cheat_Private::Loot::Text)
                      {
                          Draw::esp->draw_text_outline_font(
                              Spair.x - (Size.x / 2.0f), Spair.y - (Size.y / 2.0f),  // Use screen-space coordinates (Spair)
                              ImColor(
                                  Cheat_Private::Loot::HeavyAmmoColor[0],
                                  Cheat_Private::Loot::HeavyAmmoColor[1],
                                  Cheat_Private::Loot::HeavyAmmoColor[2], 255.f),
                              Text.c_str(), 1);
                      }

                      if (Cheat_Private::Loot::Icon)
                          Draw::menu->DrawRotatedImageWithBox(LootTexture::AmmoTexture::HeavyAmmoTexture, KboxX, KflippedBoxY, WammoBox.width, -WammoBox.height);


                  }
              }

             
          }



      }
     
      if (!Cheat_Private::Loot::BattleMode)
      {
          if ((Distance / 16) > Cheat_Private::Loot::lootDistance) return;
          int LootIndex = loot->GetIndex();
          Vector3 HeadPos = Pos;
          HeadPos.z += 25;
          // Calculate height and width for drawing
          float Height = HeadPos.y - Pos.y;
          float Width = Height / 2.0f;  // Use 2.0f to ensure float division

          // Convert world position to screen-space
          Vector3 Spair = W2S(Pos);
          if (Spair.Empty()) return;  // Return if position is not on screen
          //  ImGui::GetBackgroundDrawList()->AddText(ImVec2(Spair.x, Spair.y), ImColor(255, 255, 255, 255), std::string(std::to_string(LootIndex)).c_str());


          struct BoxDimensions {
              int width;
              int height;
              int yheight;
          };

          BoxDimensions weaponBox = { 55, 30, 35 };
          BoxDimensions ammoBox = { 35,15,11 }; // 35 15, 11
          BoxDimensions HealthBox = { 50,37,1 }; //50 37 1
          BoxDimensions WammoBox = { 30, 30, 35 };

          weaponBox.yheight = 45;
          ammoBox.yheight = 45;
          HealthBox.yheight = 45;
          WammoBox.yheight = 45;

          int boxX = Spair.x - (weaponBox.width / 2);
          int boxY = Spair.y + weaponBox.yheight;
          int flippedBoxY = boxY - weaponBox.height;

          int AboxX = Spair.x - (ammoBox.width / 2);
          int AboxY = Spair.y + ammoBox.yheight;
          int AflippedBoxY = AboxY - ammoBox.height;


          int BboxX = Spair.x - (HealthBox.width / 2);
          int BboxY = Spair.y + HealthBox.yheight;
          int BflippedBoxY = BboxY - HealthBox.height;

          int KboxX = Spair.x - (WammoBox.width / 2);
          int KboxY = Spair.y + WammoBox.yheight;
          int KflippedBoxY = KboxY - WammoBox.height;

          // Drawing logic for Med items
          if (Cheat_Private::Loot::Medic)
          {
              for (size_t MedicIndex = 0; MedicIndex < MedList.size(); MedicIndex++)  // Iterate through MedList
              {
                  auto MedicLoot = MedList[MedicIndex];

                  if (MedicLoot.first == LootIndex)  // If loot index matches
                  {
                      std::string Text = MedicLoot.second;

                      // Calculate text size for centering
                      ImVec2 Size = ImGui::CalcTextSize(Text.c_str());

                      // Draw text if enabled
                      if (Cheat_Private::Loot::Text)
                      {
                          Draw::esp->draw_text_outline_font(
                              Spair.x - (Size.x / 2.0f), Spair.y - (Size.y / 2.0f),  // Use screen-space coordinates (Spair)
                              ImColor(
                                  Cheat_Private::Loot::MedicaColor[0],
                                  Cheat_Private::Loot::MedicaColor[1],
                                  Cheat_Private::Loot::MedicaColor[2], 255.f),
                              Text.c_str(), 1);
                      }


                      if (Cheat_Private::Loot::Icon)
                      {

                          switch (MedicLoot.first)
                          {
                          case 202:
                              Draw::menu->DrawRotatedImageWithBox(LootTexture::MedTexture::SmallMedTexture, BboxX, BflippedBoxY, weaponBox.width, -HealthBox.height);

                              break;
                          case 201:
                              Draw::menu->DrawRotatedImageWithBox(LootTexture::MedTexture::LargeMedTexture, BboxX, BflippedBoxY, weaponBox.width, -HealthBox.height);
                              break;
                          case 335:
                              Draw::menu->DrawRotatedImageWithBox(LootTexture::MedTexture::EvoCacheTexture, BboxX, BflippedBoxY, weaponBox.width, -HealthBox.height);
                              break;
                          case 204:
                              Draw::menu->DrawRotatedImageWithBox(LootTexture::MedTexture::SmallShieldTexture, BboxX, BflippedBoxY, weaponBox.width, -HealthBox.height);
                              break;
                          case 203:
                              Draw::menu->DrawRotatedImageWithBox(LootTexture::MedTexture::LargeShieldTexture, BboxX, BflippedBoxY, weaponBox.width, -HealthBox.height);
                              break;
                          case 200:
                              Draw::menu->DrawRotatedImageWithBox(LootTexture::MedTexture::PhynioxTexture, BboxX, BflippedBoxY, weaponBox.width, -HealthBox.height);
                              break;
                          }
                      }
                  }
              }
          }
          if (Cheat_Private::Loot::LightWeapon)
          {
              for (size_t LightGunIndex = 0; LightGunIndex < LightGunList.size(); LightGunIndex++)  // Iterate through MedList
              {
                  auto LightGun = LightGunList[LightGunIndex];

                  if (LightGun.first == LootIndex)  // If loot index matches
                  {
                      std::string Text = LightGun.second;

                      // Calculate text size for centering
                      ImVec2 Size = ImGui::CalcTextSize(Text.c_str());

                      // Draw text if enabled
                      if (Cheat_Private::Loot::Text)
                      {
                          Draw::esp->draw_text_outline_font(
                              Spair.x - (Size.x / 2.0f), Spair.y - (Size.y / 2.0f),  // Use screen-space coordinates (Spair)
                              ImColor(
                                  Cheat_Private::Loot::LightWeaponColor[0],
                                  Cheat_Private::Loot::LightWeaponColor[1],
                                  Cheat_Private::Loot::LightWeaponColor[2], 255.f),
                              Text.c_str(), 1);
                      }


                      if (Cheat_Private::Loot::Icon)
                      {


                          switch (LightGun.first)
                          {
                          case 117:
                              Draw::menu->DrawRotatedImageWithBox(WeaponIcon::PistolICON::P2020Texture, AboxX, AflippedBoxY, ammoBox.width, -ammoBox.height);
                              break;
                          case 126:
                              Draw::menu->DrawRotatedImageWithBox(WeaponIcon::PistolICON::Re45Texture, AboxX, AflippedBoxY, ammoBox.width, -ammoBox.height);
                              break;
                          case 45:
                              Draw::menu->DrawRotatedImageWithBox(WeaponIcon::PistolICON::AlternatorTexture, AboxX, AflippedBoxY, ammoBox.width, -ammoBox.height);
                              break;
                          case 82:
                              Draw::menu->DrawRotatedImageWithBox(WeaponIcon::Rifle::CarbineTexture, boxX, flippedBoxY, weaponBox.width, -weaponBox.height);
                              break;
                          case 77:
                              Draw::menu->DrawRotatedImageWithBox(WeaponIcon::Rifle::SpitFireTexture, boxX, flippedBoxY, weaponBox.width, -weaponBox.height);
                              break;
                          case 40:
                              Draw::menu->DrawRotatedImageWithBox(WeaponIcon::Rifle::ScoutTexture, boxX, flippedBoxY, weaponBox.width, -weaponBox.height);
                              break;
                          }
                      }
                  }
              }
          }
          if (Cheat_Private::Loot::Shotgun)
          {
              for (size_t ShotgunIndex = 0; ShotgunIndex < ShotGunlist.size(); ShotgunIndex++)  // Iterate through MedList
              {
                  auto Shotgun = ShotGunlist[ShotgunIndex];

                  if (Shotgun.first == LootIndex)  // If loot index matches
                  {
                      std::string Text = Shotgun.second;

                      // Calculate text size for centering
                      ImVec2 Size = ImGui::CalcTextSize(Text.c_str());

                      // Draw text if enabled
                      if (Cheat_Private::Loot::Text)
                      {
                          Draw::esp->draw_text_outline_font(
                              Spair.x - (Size.x / 2.0f), Spair.y - (Size.y / 2.0f),  // Use screen-space coordinates (Spair)
                              ImColor(
                                  Cheat_Private::Loot::ShotGunColor[0],
                                  Cheat_Private::Loot::ShotGunColor[1],
                                  Cheat_Private::Loot::ShotGunColor[2], 255.f),
                              Text.c_str(), 1);
                      }


                      if (Cheat_Private::Loot::Icon)
                      {


                          switch (Shotgun.first)
                          {
                          case 98:
                              Draw::menu->DrawRotatedImageWithBox(WeaponIcon::ShotgunICON::MozambiqueTexture, AboxX, AflippedBoxY, ammoBox.width, -ammoBox.height);
                              break;
                          case 87:
                              Draw::menu->DrawRotatedImageWithBox(WeaponIcon::ShotgunICON::EVA8Texture, AboxX, AflippedBoxY, ammoBox.width, -ammoBox.height);
                              break;
                          case 93:
                              Draw::menu->DrawRotatedImageWithBox(WeaponIcon::ShotgunICON::peacekeeperTexture, AboxX, AflippedBoxY, ammoBox.width, -ammoBox.height);
                              break;
                          case 2:
                              Draw::menu->DrawRotatedImageWithBox(WeaponIcon::ShotgunICON::MastiffTexture, boxX, flippedBoxY, weaponBox.width, -weaponBox.height);
                              break;

                          }
                      }
                  }
              }
          }

          if (Cheat_Private::Loot::EnergyAmmo && LootIndex == 151)
          {
              {
                  std::string Text = "Energy Ammo";

                  // Calculate text size for centering
                  ImVec2 Size = ImGui::CalcTextSize(Text.c_str());
                  if (Cheat_Private::Loot::Icon)
                  {
                      Draw::menu->DrawRotatedImageWithBox(LootTexture::AmmoTexture::EnergyAmmoTexture, KboxX, KflippedBoxY, WammoBox.width, -WammoBox.height);

                  }

                  // Draw text if enabled
                  if (Cheat_Private::Loot::Text)
                  {
                      Draw::esp->draw_text_outline_font(
                          Spair.x - (Size.x / 2.0f), Spair.y - (Size.y / 2.0f),  // Use screen-space coordinates (Spair)
                          ImColor(
                              Cheat_Private::Loot::EnergyAmmoColor[0],
                              Cheat_Private::Loot::EnergyAmmoColor[1],
                              Cheat_Private::Loot::EnergyAmmoColor[2], 255.f),
                          Text.c_str(), 1);
                  }



              }
          }
          if (Cheat_Private::Loot::ShotgunAmmo && LootIndex == 152)
          {
              {
                  std::string Text = "Shotgun Ammo";

                  // Calculate text size for centering
                  ImVec2 Size = ImGui::CalcTextSize(Text.c_str());

                  // Draw text if enabled
                  if (Cheat_Private::Loot::Text)
                  {
                      Draw::esp->draw_text_outline_font(
                          Spair.x - (Size.x / 2.0f), Spair.y - (Size.y / 2.0f),  // Use screen-space coordinates (Spair)
                          ImColor(
                              Cheat_Private::Loot::ShotGunAmmoColor[0],
                              Cheat_Private::Loot::ShotGunAmmoColor[1],
                              Cheat_Private::Loot::ShotGunAmmoColor[2], 255.f),
                          Text.c_str(), 1);
                  }

                  if (Cheat_Private::Loot::Icon)
                      Draw::menu->DrawRotatedImageWithBox(LootTexture::AmmoTexture::ShotGunAmmoTexture, KboxX, KflippedBoxY, WammoBox.width, -WammoBox.height);


              }
          }
          if (Cheat_Private::Loot::LightAmmo && LootIndex == 150)
          {
              {
                  std::string Text = "Light Ammo";

                  // Calculate text size for centering
                  ImVec2 Size = ImGui::CalcTextSize(Text.c_str());

                  // Draw text if enabled
                  if (Cheat_Private::Loot::Text)
                  {
                      Draw::esp->draw_text_outline_font(
                          Spair.x - (Size.x / 2.0f), Spair.y - (Size.y / 2.0f),  // Use screen-space coordinates (Spair)
                          ImColor(
                              Cheat_Private::Loot::LightAmmoColor[0],
                              Cheat_Private::Loot::LightAmmoColor[1],
                              Cheat_Private::Loot::LightAmmoColor[2], 255.f),
                          Text.c_str(), 1);
                  }

                  if (Cheat_Private::Loot::Icon)
                      Draw::menu->DrawRotatedImageWithBox(LootTexture::AmmoTexture::LightAmmoTexture, KboxX, KflippedBoxY, WammoBox.width, -WammoBox.height);


              }



          }
          if (Cheat_Private::Loot::SniperAmmo && LootIndex == 154)
          {
              {
                  std::string Text = "Sniper Ammo";

                  // Calculate text size for centering
                  ImVec2 Size = ImGui::CalcTextSize(Text.c_str());

                  // Draw text if enabled
                  if (Cheat_Private::Loot::Text)
                  {
                      Draw::esp->draw_text_outline_font(
                          Spair.x - (Size.x / 2.0f), Spair.y - (Size.y / 2.0f),  // Use screen-space coordinates (Spair)
                          ImColor(
                              Cheat_Private::Loot::SniperAmmoColor[0],
                              Cheat_Private::Loot::SniperAmmoColor[1],
                              Cheat_Private::Loot::SniperAmmoColor[2], 255.f),
                          Text.c_str(), 1);
                  }

                  if (Cheat_Private::Loot::Icon)
                      Draw::menu->DrawRotatedImageWithBox(LootTexture::AmmoTexture::SniperAmmoTexture, KboxX, KflippedBoxY, WammoBox.width, -WammoBox.height);


              }
          }
          if (Cheat_Private::Loot::HeavyAmmo && LootIndex == 153)
          {
              {
                  std::string Text = "Heavy Ammo";

                  // Calculate text size for centering
                  ImVec2 Size = ImGui::CalcTextSize(Text.c_str());

                  // Draw text if enabled
                  if (Cheat_Private::Loot::Text)
                  {
                      Draw::esp->draw_text_outline_font(
                          Spair.x - (Size.x / 2.0f), Spair.y - (Size.y / 2.0f),  // Use screen-space coordinates (Spair)
                          ImColor(
                              Cheat_Private::Loot::HeavyAmmoColor[0],
                              Cheat_Private::Loot::HeavyAmmoColor[1],
                              Cheat_Private::Loot::HeavyAmmoColor[2], 255.f),
                          Text.c_str(), 1);
                  }

                  if (Cheat_Private::Loot::Icon)
                      Draw::menu->DrawRotatedImageWithBox(LootTexture::AmmoTexture::HeavyAmmoTexture, KboxX, KflippedBoxY, WammoBox.width, -WammoBox.height);


              }

              if (Cheat_Private::Loot::HeavyAmmo && LootIndex == 153)
              {
                  {
                      std::string Text = "Heavy Ammo";

                      // Calculate text size for centering
                      ImVec2 Size = ImGui::CalcTextSize(Text.c_str());

                      // Draw text if enabled
                      if (Cheat_Private::Loot::Text)
                      {
                          Draw::esp->draw_text_outline_font(
                              Spair.x - (Size.x / 2.0f), Spair.y - (Size.y / 2.0f),  // Use screen-space coordinates (Spair)
                              ImColor(
                                  Cheat_Private::Loot::HeavyAmmoColor[0],
                                  Cheat_Private::Loot::HeavyAmmoColor[1],
                                  Cheat_Private::Loot::HeavyAmmoColor[2], 255.f),
                              Text.c_str(), 1);
                      }

                      if (Cheat_Private::Loot::Icon)
                          Draw::menu->DrawRotatedImageWithBox(LootTexture::AmmoTexture::HeavyAmmoTexture, KboxX, KflippedBoxY, WammoBox.width, -WammoBox.height);


                  }
              }


          }
      
      }
   
    }

};

inline Loot loot;

// list

//med
//syringe : 202
//Med-Kit : 201
//Evo-Cache : 335
//Shield-Cell : 204
//Shield-Battery : 203
//Phoenix-Kit : 200