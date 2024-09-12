#include "../../imgui/imgui.h"

#include <D3DX11tex.h>
#pragma comment(lib, "D3DX11.lib")

class c_settings
{
public:

	struct
	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

		ImVec2 window_size = ImVec2(750, 500);
		ImVec2 padding = ImVec2(0, 0);
		ImVec2 item_spacing = ImVec2(4, 4);

		float scrollbar_size = 12.f;
		float border_size = 0.f;
		float rounding = 8.f;

	} c_window;

	struct
	{
		
		ImFont* inter_medium[3];
		ImFont* inter_regular[2];

		ImFont* icon[3];

	} c_font;

	struct
	{
		ImVec2 content_item_spacing = ImVec2(15, 15);
		ImVec2 content_window_padding = ImVec2(15, 15);

		ImVec2 child_item_spacing = ImVec2(15, 15);
		ImVec2 child_window_padding = ImVec2(15, 15);

		float rounding = 6.f;

	} c_child;

	struct
	{
		float rounding = 4.f;
		float speed_animation = 12.f;

	} c_element;

	struct
	{
		ID3D11ShaderResourceView* background = nullptr;

	} c_texture;

};

inline c_settings* set = new c_settings();

class c_colors
{
public:

	struct
	{
		ImVec4 accent_clr = ImColor(78, 78, 184, 255);

		ImVec4 white_clr = ImColor(255, 255, 255, 255);
		ImVec4 black_clr = ImColor(0, 0, 0, 255);

		ImVec4 col_bg_alpha_0 = ImColor(125, 125, 125, 255);
		ImVec4 col_bg_alpha_1 = ImColor(185, 185, 185, 255);

	} c_important;

	struct
	{
		ImVec4 layout = ImColor(0, 0, 0, 150);
		ImVec4 border = ImColor(0, 0, 0, 120);

	} c_window;

	struct
	{
		ImVec4 layout = ImColor(0, 0, 0, 120);

	} c_child;

	struct
	{
		ImVec4 mark_circle_filling = ImColor(64, 76, 96, 255);
		ImVec4 checkbox_layout_active = ImColor(33, 33, 57, 255);

		ImVec4 selection_layout = ImColor(33, 33, 42, 255);
		ImVec4 widget_layout = ImColor(24, 26, 36, 255);

		ImVec4 dropdown_selection_layout = ImColor(34, 36, 56, 255);

	} c_element;

	struct
	{
		ImVec4 text_active = ImColor(255, 255, 255, 255);
		ImVec4 text = ImColor(220, 220, 220, 255);

		ImVec4 text_selection = ImColor(126, 128, 152, 255);

	} c_text;

};

inline c_colors* clr = new c_colors();
