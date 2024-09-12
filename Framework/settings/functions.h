#define IMGUI_DEFINE_MATH_OPERATORS

#include "../../imgui/imgui.h"
#include "../../imgui/imgui_internal.h"

#include "variables.h"
#include "elements.h"
#include "settings.h"

#include <vector>
#include <sstream>
#include <string>
#include <tchar.h>

#include <D3DX11tex.h>
#pragma comment(lib, "D3DX11.lib")

#include "../../imgui/imgui_impl_win32.h"
#include "../../imgui/imgui_impl_win32.h"
#include "../../Hacks/Player.hpp"


 inline ID3D11Device* g_pd3dDevice = nullptr;
 inline ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
inline IDXGISwapChain* g_pSwapChain = nullptr;
inline bool                     g_SwapChainOccluded = false;
inline UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
inline ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

enum fade_direction : int
{
    vertically,
    horizontally,
    diagonally,
    diagonally_reversed,
};

enum interpolation_type {
    back,
    elastic,
};

#define PI 3.14159265359f

using namespace ImGui;

 inline D3DX11_IMAGE_LOAD_INFO info;
inline ID3DX11ThreadPump* pump;

class c_gui
{
public:

    template <typename T>
    T* anim_container(T** state_ptr, ImGuiID id)
    {
        T* state = static_cast<T*>(GetStateStorage()->GetVoidPtr(id));
        if (!state)
            GetStateStorage()->SetVoidPtr(id, state = new T());

        *state_ptr = state;
        return state;
    }

    ImU32                           get_clr(const ImVec4& col, float alpha = 1.f);

    float                           fixed_speed(float speed) { return speed / ImGui::GetIO().Framerate; };

    bool                            begin(std::string_view name, bool* p_open = nullptr, ImGuiWindowFlags flags = ImGuiWindowFlags_None);

    void                            end();

    void                            push_style_color(ImGuiCol idx, ImU32 col);

    void                            pop_style_color(int count = 1);

    void                            push_style_var(ImGuiStyleVar idx, float val);

    void                            push_style_var(ImGuiStyleVar idx, const ImVec2& val);

    void                            pop_style_var(int count = 1);

    void                            set_cursor_pos(const ImVec2& local_pos);

    void                            set_cursor_pos_x(float x);
                                    
    void                            set_cursor_pos_y(float y);

    ImVec2                          get_cursor_pos();

    float                           get_cursor_pos_x();

    float                           get_cursor_pos_y();

    void                            push_font(ImFont* font);

    void                            pop_font();

    void                            spacing();

    void                            sameline(float offset_from_start_x = 0.0f, float spacing_w = -1.0f);

    void                            set_next_window_pos(const ImVec2& pos, ImGuiCond cond = 0, const ImVec2& pivot = ImVec2(0, 0));

    void                            set_next_window_size(const ImVec2& size, ImGuiCond cond = 0);

    bool                            begin_child(std::string_view name, const ImVec2& size_arg = ImVec2(0, 0), ImGuiChildFlags child_flags = 0, ImGuiWindowFlags window_flags = 0);

    void                            end_child();

    void                            begin_group();

    void                            end_group();

    void                            begin_content(const char* id, const ImVec2& size_arg, const ImVec2& padding, const ImVec2& spacing, bool move = true);

    void                            end_content();

    bool                            selection(std::string_view icon, std::string_view label, int selection_id, int& selection_variable, const ImVec2& size);

    inline                          ImGuiWindow* get_current_window() { ImGuiContext& g = *GImGui; g.CurrentWindow->WriteAccessed = true; return g.CurrentWindow; };

    void                            new_frame();

    void                            end_frame();

    void                            render();
};
inline c_gui* gui = new c_gui();

class c_widget
{
public:

    bool                            checkbox(std::string_view label, bool* callback);

    bool                            checkbox_with_picker(std::string_view label, bool* callback, float col[4], bool alpha = true);

    bool                            slider_int(std::string_view label, int* v, int v_min, int v_max, const char* format = 0);

    bool                            slider_float(std::string_view label, float* v, float v_min, float v_max, const char* format = 0);

    bool                            color_picker(std::string_view label, float col[4], bool alpha);

    bool                            hue_slider(std::string_view label, float col[4]);

    bool                            dropdown(std::string_view label, int* current_item, std::vector<std::string>& items, int max_count);

    void                            multi_dropdown(std::string_view label, bool variable[], std::vector<std::string>& labels, int max_count);

    bool                            keybind(std::string_view label, int& key);

};

inline c_widget* widget = new c_widget();

class c_draw
{
public:

    void                            add_text(ImDrawList* draw_list, const ImFont* font, float font_size, const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end = NULL, float wrap_width = NULL, const ImVec4* cpu_fine_clip_rect = NULL);

    void                            render_text(ImFont* font, ImDrawList* draw_list, const ImVec2& pos_min, const ImVec2& pos_max, ImU32 color, const char* text, const char* text_display_end = NULL, const ImVec2* text_size_if_known = NULL, const ImVec2& align = { 0.5, 0.5 }, const ImRect* clip_rect = NULL);

    void                            rect_filled_multi_color(ImDrawList* draw, const ImVec2& p_min, const ImVec2& p_max, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left, float rounding = 0.f, ImDrawFlags flags = 0);

    void                            add_rect_filled(ImDrawList* draw_list, const ImVec2& p_min, const ImVec2& p_max, ImU32 col, float rounding = 0, ImDrawFlags flags = 0);

    void                            add_circle_filled(ImDrawList* draw_list, const ImVec2& center, float radius, ImU32 col, int num_segments = 0);

    void                            add_circle(ImDrawList* draw_list, const ImVec2& center, float radius, ImU32 col, int num_segments = 0, float thickness = 0);

    void                            add_rect(ImDrawList* draw_list, const ImVec2& p_min, const ImVec2& p_max, ImU32 col, float rounding, ImDrawFlags flags = 0, float tickness = 0);

    void                            fade_rect_filled(ImDrawList* draw, const ImVec2& pos_min, const ImVec2& pos_max, ImU32 col_one, ImU32 col_two, fade_direction direction, float rounding = 0.f, ImDrawFlags flags = 0);

    void                            render_text(ImDrawList* draw_list, ImFont* font, const ImVec2& pos_min, const ImVec2& pos_max, ImU32 color, const char* text, const char* text_display_end = NULL, const ImVec2* text_size_if_known = NULL, const ImVec2& align = ImVec2(0.f, 0.f), const ImRect* clip_rect = NULL);

    void                            radial_gradient(ImDrawList* draw_list, const ImVec2& center, float radius, ImU32 col_in, ImU32 col_out);

    void                            set_linear_color_alpha(ImDrawList* draw_list, int vert_start_idx, int vert_end_idx, ImVec2 gradient_p0, ImVec2 gradient_p1, ImU32 col0, ImU32 col1);

    void                            add_image(ImDrawList* draw_list, ImTextureID user_texture_id, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min, const ImVec2& uv_max, ImU32 col);

    void                            add_image_rounded(ImDrawList* draw_list, ImTextureID user_texture_id, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min, const ImVec2& uv_max, ImU32 col, float rounding = 0, ImDrawFlags flags = 0);

    void                            add_line(ImDrawList* draw, const ImVec2& p1, const ImVec2& p2, ImU32 col, float thickness = 0);
};

inline c_draw* draw = new c_draw();

class c_easing
{

public:

    float easing_value;

    float ease_in_elastic(float t) { const float c4 = (2 * PI) / 2;  return (t <= 0.01f) ? 0.0f : (t >= 0.60f) ? 1.0f : pow(2, -10 * t) * sin((t * 10 - 0.75) * c4) + 1; }

    float ease_in_back(float t) { const float c1 = 1.70158; const float c3 = c1 + 1; return 1 + c3 * pow(t - 1, 3) + c1 * pow(t - 1, 2); }

    struct easing_state {
        float animTime = 0.0f;
        bool reverse = false;
    };

    template <typename T>
    T im_ease(int animation_id, bool callback, T min, T max, float speed, interpolation_type type) {
        easing_state* state = gui->anim_container(&state, GetCurrentWindow()->GetID(animation_id));

        state->animTime = (callback != state->reverse) ? 0.0f : min(state->animTime + 0.1f * speed, 1.0f);
        state->reverse = callback;

        easing_value = (type == elastic) ? ease_in_elastic(state->animTime) : (type == back) ? ease_in_back(state->animTime) : 0;

        return callback ? easing_value * (max - min) + min : easing_value * (min - max) + max;
    }

    template <>
    ImVec2 im_ease<ImVec2>(int animation_id, bool callback, ImVec2 min, ImVec2 max, float speed, interpolation_type type) {
        easing_state* state = gui->anim_container(&state, GetCurrentWindow()->GetID(animation_id));

        state->animTime = (callback != state->reverse) ? 0.0f : min(state->animTime + 0.1f * speed, 1.0f);
        state->reverse = callback;

        easing_value = (type == elastic) ? ease_in_elastic(state->animTime) : (type == back) ? ease_in_back(state->animTime) : 0;

        ImVec2 result;
        result.x = callback ? easing_value * (max.x - min.x) + min.x : easing_value * (min.x - max.x) + max.x;
        result.y = callback ? easing_value * (max.y - min.y) + min.y : easing_value * (min.y - max.y) + max.y;
        return result;
    }
};

inline std::unique_ptr<c_easing> easing = std::make_unique<c_easing>();

struct add_item_state
{
    bool window_opened = false;
    float window_alpha = 0.f;
    bool window_hovered = false;
};

struct preview_box
{
    ImVec2 position;
    ImVec2 size;
};

enum preview_area
{
    area_top,
    area_bottom,
    area_left,
    area_right,
    area_none
};

enum item_position
{
    position_top,
    position_bottom,
    position_left,
    position_right
};

struct item_state
{
    std::string name;
    ImVec4 color;
    int position;
    ImVec2 location;
    bool swapped;
    bool active;
    ImRect rect = ImRect(ImVec2(0, 0), ImVec2(0, 0));
};

class esp_preview
{
public:

    std::vector<item_state> text =
    {
        { "NICKNAME", ImVec4(1.f, 1.f, 1.f, 1.f), position_top },

        { "MONEY", ImVec4(1.f, 1.f, 1.f, 1.f), position_right },
        { "SCOPE", ImVec4(1.f, 1.f, 1.f, 1.f), position_right },
        { "PING", ImVec4(1.f, 1.f, 1.f, 1.f), position_right },
        { "KD", ImVec4(1.f, 1.f, 1.f, 1.f), position_right },

        { "DISTANCE", ImVec4(1.f, 1.f, 1.f, 1.f), position_left },
        { "FLASH", ImVec4(1.f, 1.f, 1.f, 1.f), position_left },
        { "BLIND", ImVec4(1.f, 1.f, 1.f, 1.f), position_left },
        { "LC", ImVec4(1.f, 1.f, 1.f, 1.f), position_left },

        { "WEAPON", ImVec4(1.f, 1.f, 1.f, 1.f), position_bottom },
    };

    std::vector<item_state> bar =
    {
        { "HEALTH", ImVec4(132 / 255.f, 255 / 255.f, 152 / 255.f, 1.f), position_left },
        { "ARMOR", ImVec4(130 / 255.f, 150 / 255.f, 255 / 255.f, 1.f), position_right },
    };

    void initialize_preview(const ImVec2& pos, const ImVec2& size);
    void render_box(int type);
    void render_text(item_state& state);
    void render_bar(item_state& state);

private:
    preview_box box;
    ImRect area_rect[4];

    void fill_box(const ImVec2& pos, const ImVec2& size);
    void fill_areas();
    void fill_buffers();

    int texts_buffer[4] = { 0, 0, 0, 0 };
    int bars_buffer[4] = { 0, 0, 0, 0 };
    int hovered_area = area_none;

    float area_size = 80.f;
};

inline esp_preview* Prev = new esp_preview();
