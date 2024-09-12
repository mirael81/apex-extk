#include "settings/functions.h"
#include "shader/blur.hpp"

void c_gui::render()
{

	{
		ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(2000, 2000), ImColor(10, 10, 10, 200));
	/*	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(0, 0), ImVec2(2000, 2000), ImColor(10, 10, 10, 200));
		Draw::esp->draw_text_outline_font(5, 25, ImColor(255, 0, 0, 255), "[", .5f);*/

		Draw::esp->draw_text_outline_font(10, 25, ImColor(255, 255, 255, 255), "Apex Legends External Private Cheat",.5f);
		/*Draw::esp->draw_text_outline_font(10, 40, ImColor(255, 255, 255, 255), "Developed By l3g2nd",.5f);
		Draw::esp->draw_text_outline_font(10, 55, ImColor(255, 255, 255, 255), "Undetected : 7/20/2024",.5f);
		Draw::esp->draw_text_outline_font(10, 70, ImColor(255, 255, 255, 255), "TYPE=Private.Build", .5f);
		std::stringstream ss;
		ss << "r5apex.exe : 0x" << std::hex << std::uppercase << (uint64_t)sdk.R5Apex;
		Draw::esp->draw_text_outline_font(10, 85, ImColor(255, 255, 255, 255), ss.str().c_str(), .5f);
		Draw::esp->draw_text_outline_font(10, 100, ImColor(255, 255, 255, 255), std::string("Player Count : " + std::to_string(int(EntityCount))).c_str(), .5f);
		Draw::esp->draw_text_outline_font(135, 100, ImColor(255, 0, 0, 255), "]", .5f);*/

		//draw->add_image(GetBackgroundDrawList(), set->c_texture.background, { 0, 0 }, { 1920, 1080 }, { 0, 0 }, { 1, 1 }, gui->get_clr(clr->c_important.white_clr));

		gui->set_next_window_size(set->c_window.window_size);
		gui->begin( { "XEX" }, { 0 } );
		{
			const ImVec2 pos = GetWindowPos();
			const ImVec2 size = GetWindowSize();

			ImDrawList* draw_list = GetWindowDrawList();
			ImGuiStyle* style = &GetStyle();

			{
				style->WindowBorderSize = set->c_window.border_size;
				style->WindowRounding = set->c_window.rounding;
				style->WindowPadding = set->c_window.padding;

				style->ScrollbarSize = set->c_window.scrollbar_size;
				style->ItemSpacing = set->c_window.item_spacing;
			}

			draw->add_rect_filled(draw_list, pos, { pos.x + size.x, pos.y + size.y }, gui->get_clr(clr->c_window.layout), set->c_window.rounding);
			draw->add_rect_filled(draw_list, pos, { pos.x + 170, pos.y + size.y }, gui->get_clr(clr->c_window.border), set->c_window.rounding, ImDrawFlags_RoundCornersLeft);

			gui->begin_content("tab_bar", { 170, size.y }, { 15, 15 }, { 15, 15 });
			{

				for (int i = 0; i < var->c_selection.selection_icon.size(); i++)
					gui->selection(var->c_selection.selection_icon[i].data(), var->c_selection.selection_label[i].data(), i, var->c_selection.selection, { GetContentRegionAvail().x, 40 });

			}
			gui->end_content();

			gui->sameline(0, 0);

			var->c_selection.selection_alpha = ImClamp(var->c_selection.selection_alpha + (4.f * ImGui::GetIO().DeltaTime * (var->c_selection.selection == var->c_selection.selection_active ? 1.f : -1.f)), 0.f, 1.f);
			if (var->c_selection.selection_alpha == 0.f && var->c_selection.selection_add == 0.f) var->c_selection.selection_active = var->c_selection.selection;

			gui->push_style_var(ImGuiStyleVar_Alpha, var->c_selection.selection_alpha * style->Alpha);

			gui->begin_content("content", { GetContentRegionAvail().x, size.y}, {15, 15}, {15, 15});
			{

				if (var->c_selection.selection_active == 0)
				{
					gui->begin_child("Combat");
					{

						widget->checkbox("Aimbot", &Cheat_Private::Aimbot::VABot);
						widget->checkbox("PSilent (NOT SAFE)", &Cheat_Private::Aimbot::PSilent);
						widget->dropdown("Aimbot Key", &Cheat_Private::Settings::AimbotKeyINDEX, Cheat_Private::Settings::KeyText, Cheat_Private::Settings::KeyText.size());
						widget->checkbox("Fov Circle", &Cheat_Private::Aimbot::FovCircle);
						widget->checkbox("Target Line", &Cheat_Private::Aimbot::Snapline);
						widget->slider_float("Smothing", &Cheat_Private::Aimbot::SmoothingAmount, 1.f, 10.f);
						widget->slider_float("Fov Size", &Cheat_Private::Aimbot::FovCircleSize, 1.f, 500.f);
						widget->dropdown("Bone Selection", &Cheat_Private::Aimbot::TargetBone, Cheat_Private::Aimbot::BoneName, Cheat_Private::Aimbot::BoneName.size());
					}
					gui->end_child();
					gui->sameline();

					gui->begin_child("Recoil");
					{
						widget->checkbox("Rcs Control", &Cheat_Private::Aimbot::RcsControl);
						widget->slider_float("YAW", &yawSTR, 0.f, 1.f);
						widget->slider_float("PITCH", &pitchSTR, 0.f, 1.f);

					}
					gui->end_child();
					gui->begin_child("COLORS");
					{
						widget->color_picker("Fov Circle Color", Cheat_Private::Aimbot::FovCircleColor, true);
						widget->color_picker("Target Line Color", Cheat_Private::Aimbot::SnaplineColor, true);
					}
					gui->end_child();

				
				
					

						
				}
				else if (var->c_selection.selection_active == 1)
				{

					gui->begin_group();
					{

						gui->begin_child("DRAWING");
						{

							widget->checkbox("Box", &Cheat_Private::ESP::Box);
							widget->checkbox("Corner Box", &Cheat_Private::ESP::CornerBox);
							widget->checkbox("Filled Box", &Cheat_Private::ESP::Filledbox);
							widget->checkbox("Skeleton", &Cheat_Private::ESP::Skeleton);
							widget->checkbox("Seer Health", &Cheat_Private::ESP::SernEsp);
							widget->checkbox("In-Game Radar", &Cheat_Private::ESP::Radar);
							widget->checkbox("In-Game OFF Arrows", &Cheat_Private::ESP::FOVArrows);
							widget->slider_float("Radar Size", &Cheat_Private::ESP::RadarSize,0,10);
							widget->checkbox("In-Game Alert", &Cheat_Private::ESP::alert);

						}
						gui->end_child();

					}
					gui->end_group();

					gui->sameline();
					gui->begin_child("PLAYER INFO");
					{

						widget->checkbox("Distance", &Cheat_Private::ESP::Distance);
						widget->checkbox("Name", &Cheat_Private::ESP::Weapon);
						widget->checkbox("Level", &Cheat_Private::ESP::Level);
						widget->checkbox("Weapon", &Cheat_Private::ESP::Name);
						widget->checkbox("Weapon ICON", &Cheat_Private::ESP::WeaponICON);
						widget->checkbox("Operator", &Cheat_Private::ESP::Operator);
						widget->checkbox("Health", &Cheat_Private::ESP::Health);
						widget->checkbox("Shield", &Cheat_Private::ESP::Shield);
						widget->checkbox("Vis Check", &Cheat_Private::ESP::VisCheck);
						widget->checkbox("Ammo Counter", &Cheat_Private::Misc::AmmoCounter);

					}
					gui->end_child();


					gui->begin_child("COLORS");
					{
						widget->color_picker("Box Color", Cheat_Private::ESP::BoxColor, true);
						widget->color_picker("Distance Color", Cheat_Private::ESP::DistanceColor, true);
						widget->color_picker("Level Color", Cheat_Private::ESP::LevelColor, true);
						widget->color_picker("Weapon Color", Cheat_Private::ESP::NameColor, true);
						widget->color_picker("Weapon ICON Color", Cheat_Private::ESP::WeaponIconColor, true);
						widget->color_picker("Name Color", Cheat_Private::ESP::WeaponColor, true);
						widget->color_picker("Operator Color", Cheat_Private::ESP::OperatorColor, true);
						widget->color_picker("Vis Color", Cheat_Private::ESP::VisColor, true);
						widget->color_picker("Non-Vis Color", Cheat_Private::ESP::NonVisColor, true);
					}
					gui->end_child();
					gui->sameline();


					gui->begin_child("CHARACTER'S");
					{
						widget->checkbox("Homer J Simpson", &Cheat_Private::ESP::PeterGriffen);
						widget->checkbox("Legend's EKitten", &Cheat_Private::ESP::EKitten);

					}
					gui->end_child();
					
				}
				else if (var->c_selection.selection_active == 2)
				{

					gui->begin_group();
					{

						gui->begin_child("MOVEMENT");
						{

							widget->checkbox("Super-Glide", &Cheat_Private::Misc::SuperGlide);
							widget->checkbox("Super-Grapple", &Cheat_Private::Misc::AutoGrapple);
							widget->checkbox("Better-Movement (SAFE)", &Cheat_Private::Misc::BetterMovement);
							widget->checkbox("Bhop", &Cheat_Private::Misc::Bhop);
							widget->checkbox("Back-Track (SEMI SAFE)", &Cheat_Private::Misc::BackTrack);
							widget->slider_float("Back-Strack Strength", &Cheat_Private::Misc::BackTrackStrength, 0.f, 1.f);
							widget->checkbox("Fake Duck", &Cheat_Private::Misc::FakeDuck);
							widget->dropdown("Fake Duck Key", &Cheat_Private::Misc::FakeDuckKEY, Cheat_Private::Settings::KeyText, Cheat_Private::Settings::KeyText.size());
						}
						gui->end_child();
						gui->sameline();
				
						gui->begin_child("EXPLOITS");
						{
							widget->checkbox("Free-Cam", &Cheat_Private::Misc::Freecam);
							widget->checkbox("Kill-Sound", &Cheat_Private::Misc::KillSound);
							widget->checkbox("Fast-Fire", &Cheat_Private::Misc::Fakefire);
							widget->checkbox("Item Glow", &Cheat_Private::Misc::ItemGlow);
							widget->checkbox("Glow", &Cheat_Private::ESP::Glow);
							widget->color_picker("Glow Color", glowcolor, true);
							widget->checkbox("Weapon Glow", &Cheat_Private::Misc::WeaponGlow);
							widget->dropdown("Weapon Glow Type", &Cheat_Private::Misc::WeaponGlowIndex, Cheat_Private::Misc::WeaponGlowText, Cheat_Private::Misc::WeaponGlowText.size());
						}
						gui->end_child();
						gui->begin_child("SKIN CHANGER");
						{

							widget->checkbox("Skin-Changer", &Cheat_Private::Misc::SkinChanger);
							widget->slider_int("SKIN ID", &Cheat_Private::Misc::SkinID, 1, 12);
						}
						gui->end_child();



					}
					gui->end_group();
				}
				else if (var->c_selection.selection_active == 4)
				{

					gui->begin_group();
					{

						gui->begin_child("SETTINGS");
						{

							widget->slider_float("Draw Distance", &Cheat_Private::Settings::RenderDistance, 50, 500);
							widget->slider_int("Glow Distance", &glowtest, -25, 90);
						}
						gui->end_child();

						gui->sameline();
						gui->begin_child("FONT");
						{
							widget->dropdown("Font Selection", &FontList::FontIndex, FontList::FontText, FontList::FontText.size());
							widget->checkbox("Outline Text", &FontList::Outline);
						}
						gui->end_child();
					}
					gui->end_group();
				}
				else if (var->c_selection.selection_active == 3)
				{

					gui->begin_group();
					{

						gui->begin_child("CONFIG");
						{

							widget->dropdown("Config List",&Cheat_Private::Config::ConfigIndex, Cheat_Private::Config::ConfigName, Cheat_Private::Config::ConfigName.size());
							gui->selection(var->c_selection.selection_icon[0].data(), "Create Config", 1,Cheat_Private::Config::LoadConfig, {GetContentRegionAvail().x, 30});
							gui->selection(var->c_selection.selection_icon[1].data(), "Save Config", 2, Cheat_Private::Config::SaveConfig, { GetContentRegionAvail().x, 30 });
							gui->selection(var->c_selection.selection_icon[0].data(), "Load Config", 3,Cheat_Private::Config::RunConfig, {GetContentRegionAvail().x, 30});

							
						}
						gui->end_child();


					}
					gui->end_group();
				}
				else if (var->c_selection.selection_active == 5)
				{

					gui->begin_group();
					{

						gui->begin_child("Loot");
						{
							widget->checkbox("BattleMode", &Cheat_Private::Loot::BattleMode);
							widget->dropdown("BattleMode Key", &Cheat_Private::Loot::BattleIndex, Cheat_Private::Loot::KeyText, Cheat_Private::Loot::KeyText.size());
							widget->checkbox("Text", &Cheat_Private::Loot::Text);
							widget->checkbox("Icon", &Cheat_Private::Loot::Icon);
							widget->checkbox("Meds", &Cheat_Private::Loot::Medic);
							widget->checkbox("Shield", &Cheat_Private::Loot::Shield);
							widget->checkbox("Helmet", &Cheat_Private::Loot::Helmet);
							widget->checkbox("Light Weapon", &Cheat_Private::Loot::LightWeapon);
							widget->checkbox("Shotgun", &Cheat_Private::Loot::Shotgun);
							widget->checkbox("Light Ammo", &Cheat_Private::Loot::LightAmmo);
							widget->checkbox("Heavy Ammo", &Cheat_Private::Loot::HeavyAmmo);
							widget->checkbox("Sniper Ammo", &Cheat_Private::Loot::SniperAmmo);
							widget->checkbox("Shotgun Ammo", &Cheat_Private::Loot::ShotgunAmmo);
							widget->checkbox("Energy Ammo", &Cheat_Private::Loot::EnergyAmmo);
						}
						gui->end_child();

						gui->sameline();
						gui->begin_child("Color");
						{
							widget->color_picker("Med Color", Cheat_Private::Loot::MedicaColor, true);
							widget->color_picker("Light Weapon Color", Cheat_Private::Loot::LightWeaponColor, true);
							widget->color_picker("Shotgun Color", Cheat_Private::Loot::ShotGunColor, true);
							widget->color_picker("Shield Color", Cheat_Private::Loot::ShieldColor, true);
							widget->color_picker("Helmet Color", Cheat_Private::Loot::HelmetColor, true);
							widget->slider_float("Draw Distance", &Cheat_Private::Loot::lootDistance, 50, 500);


						}
						gui->end_child();

						gui->begin_child("Loot Exploits");
						{
							widget->checkbox("Change Loot Size", &Cheat_Private::Loot::ChangeLootSize);


						}
						gui->end_child();
					}
					gui->end_group();
					}

			

					

				

			}
			gui->end_content();

			gui->pop_style_var(1);

		}
		gui->end();

	}

}