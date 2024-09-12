#include "../../imgui/imgui.h"
#include <vector>
#include <string>

class c_variable
{
public:

	// ESP PREVIEW

	struct
	{
		ImGuiWindowFlags preview_flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove;

		int box_c = 1;
		const char* box_type[2] = { "Default", "Corner" };

		ImVec4 corner_color = ImColor(78, 78, 91);

		bool flags = true;
		bool bars = true;
		bool esp_preview = true;

		int corner_set = 1;
		std::vector<std::string> corner_list = { "Corner", "Box" };

		float texts_spacing = 15.f;
		float bars_spacing = 10.f;
		float box_padding = 10.f;

		float anim_speed = 25.f;

	} c_preview;

	// AIMBOT

	struct
	{

		std::vector<std::string> selection_icon = {"", "", "", "", "", ""};
		std::vector<std::string> selection_label = { "Aimbot", "Visuals", "Misc", "Config", "Settings", "Loot"};

		int selection = 0, selection_active = 0;
		float selection_alpha = 1, selection_add;

	} c_selection;

	struct
	{
		bool enable_aimbot = true;
		bool disable_aimbot_while_flashed = false;
		bool disable_aimbot_through_smoke = false;

		float kill_delay = 0.5;

		float mouse_look_x = 0.5;
		float mouse_look_y = 0.5;

	} c_aimbot;

	struct
	{
		bool enable_triggerbot = true;
		bool disable_trigger_while_flashed = false;
		bool disable_trigger_through_smoke = false;

	} c_trigger;

	struct
	{
		bool enable_recoil = true;

		int pitch_recoil = 90;
		int yaw_recoil = 10;

		float smooth_recoil = 0.5;

	} c_recoil;

	struct
	{
		bool enable_assist = true;
		bool only_clicked = false;

		int speed_assist_x = 0;

	} c_assist;

	// VISUALS

	struct
	{
		bool through_walls = false;
		bool enable_esp = true;

		int bullet_selection = 0;
		std::vector<std::string> bullet_list = {"Disabled", "Line", "Beom"};

		bool in_game_radar = false;

		bool dormant = false;
	    float dormant_color[4] = { 0.5f, 0.9f, 0.2f, 1.f };

		bool offscreen_esp = false;

		bool shared_esp = false;
		float shared_color[4] = { 1.0f, 1.0f, 0.0f, 1.f };

		int sound_selection = 0;
		std::vector<std::string> sound_list = { "Select", "Enable", "Disable" };

		int offscreen_selection = 0;
		std::vector<std::string> offscreen_list = { "Select", "Enable", "Disable" };

	} c_esp;
};

inline c_variable* var = new c_variable();
