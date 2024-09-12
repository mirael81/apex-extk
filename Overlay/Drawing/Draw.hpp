#pragma once
#include <Windows.h>
#include <string>

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_win32.h"
#include "../../imgui/imgui_impl_dx11.h"

#include "../../Config/Config.hpp"
#include "../../utils/xor.hpp"

#define M_PI		3.14159265358979323846	
#define DEG2RAD(arg) arg * M_PI / 180.0
namespace FontList
{
	inline ImFont* Arial;
	inline ImFont* Calibri;
	inline ImFont* Ebrima;
	inline ImFont* Franklin_Gothic;
	inline ImFont* Pixel;
	inline std::vector<std::string> FontText = { "Arial", "Calibri", "Ebrima", "Franklin", "Pixel"};
	inline int FontIndex = 0;
	inline bool Outline = false;
	inline float FontSize = 17.f;
}

namespace Draw {
	inline bool toggled = false;
	class ESP {
	public:
		void AddLine(ImVec2 pos, ImVec2 size, ImU32 color, float thickness);
		void arc(float x, float y, float radius, float min_angle, float max_angle, ImColor col, float thickness);
		void DrawRoundBox(int x, int y, int w, int z, const ImU32 color, int Roundess);
		void HealthBar(ImVec2 Botton, float height, float health);
		void HealthBarOutline(ImVec2 Head, ImVec2 Org, int height, int width, float health);
		void HealthBarRound(ImVec2 Head, ImVec2 Org, int height, int width, float health);
		void DrawCorneredBox(int X, int Y, int W, int H, const ImU32& color, int thickness);
		void DeathBox(int X, int Y, int W, int H, const ImU32& color, int thickness);
		void DrawFilledBox(int X, int Y, int W, int H, const ImU32& color, int thickness);
		void DrawBox(int X, int Y, int W, int H, const ImU32 color, int thickness);
		void AddHexagon(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p5, const ImVec2& p6, ImU32 col, float thickness);
		void AddHexagonFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p5, const ImVec2& p6, ImU32 col);
		void DrawQuadFilled(ImVec2 p1, ImVec2 p2, ImVec2 p3, ImVec2 p4, ImColor color);
		void DrawHexagon(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p5, const ImVec2& p6, ImU32 col, float thickness);
		void DrawHexagonFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p5, const ImVec2& p6, ImU32 col);
		void SeerHealth(float x, float y, int shield, int max_shield, int armorType, int health);
		void draw_text_outline_font(float x, float y, ImColor color, const char* string, float size);
		void draw_text_outline_wFont(ImFont* font, float size, float x, float y, ImColor color, const char* string);
		void ShieldBar(ImVec2 Botton, float height, int Shield, int type, bool EnableHealth);


	}; inline ESP* esp = new ESP;

	class Menu : public ESP {
	public:
		int CurrentIndex = 1;
		ImVec2 Position = { 25,25 };
		 void DrawMenu(); // edit ur menu in this function*
		 void DrawRotatedImageWithBox(ImTextureID textureID, float x, float y, float width, float height);
		 void DrawRotatedImageWithBoxColor(ImTextureID textureID, float x, float y, float width, float height, ImColor tintColor);
		 void CreateMenu();
		 bool Didclick();
		 void CreateExtendedMenu();
		 void CreateTab(int Index, bool& Clicked, const char* str);
		 void Title(int index, const char* str, ImColor Color);
		 void GetIndex();
		 void Checkbox(int Index, bool& value, const char* str);
		 void Text(int Index, const char* str);
		 bool CheckIndex(int MaxIndex);
		 bool esp, aimbot, misc, help,settings;
		 bool GoBack = false;
	}; inline Menu* menu = new Menu;
}

