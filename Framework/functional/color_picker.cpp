#include "../settings/functions.h"

void color_edit_restore_hs(const float* col, float* H, float* S, float* V)
{
    ImGuiContext& g{ *GImGui };

    if (*S == 0.0f || (*H == 0.0f && g.ColorEditSavedHue == 1)) *H = g.ColorEditSavedHue;
    if (*V == 0.0f) *S = g.ColorEditSavedSat;
}

void render_color_rect_alpha_checkboard(ImDrawList* draw_list, ImVec2 p_min, ImVec2 p_max, ImU32 col, float grid_step, ImVec2 grid_off, float rounding, ImDrawFlags flags)
{
    if ((flags & ImDrawFlags_RoundCornersMask_) == 0) flags = ImDrawFlags_RoundCornersDefault_;
    if (((col & IM_COL32_A_MASK) >> IM_COL32_A_SHIFT) < 0xFF)
    {
        ImU32 col_bg1 = GetColorU32(ImAlphaBlendColors(gui->get_clr(clr->c_important.col_bg_alpha_0), col));
        ImU32 col_bg2 = GetColorU32(ImAlphaBlendColors(gui->get_clr(clr->c_important.col_bg_alpha_1), col));

        draw->add_rect_filled(draw_list, p_min, p_max, col_bg1, rounding, flags);

        int yi = 0;
        for (float y = p_min.y + grid_off.y; y < p_max.y; y += grid_step, yi++)
        {
            float y1 = ImClamp(y, p_min.y, p_max.y), y2 = ImMin(y + grid_step, p_max.y);
            if (y2 <= y1)
                continue;
            for (float x = p_min.x + grid_off.x + (yi & 1) * grid_step; x < p_max.x; x += grid_step * 2.0f)
            {
                float x1 = ImClamp(x, p_min.x, p_max.x), x2 = ImMin(x + grid_step, p_max.x);
                if (x2 <= x1)
                    continue;
                ImDrawFlags cell_flags = ImDrawFlags_RoundCornersNone;
                if (y1 <= p_min.y) { if (x1 <= p_min.x) cell_flags |= ImDrawFlags_RoundCornersTopLeft; if (x2 >= p_max.x) cell_flags |= ImDrawFlags_RoundCornersTopRight; }
                if (y2 >= p_max.y) { if (x1 <= p_min.x) cell_flags |= ImDrawFlags_RoundCornersBottomLeft; if (x2 >= p_max.x) cell_flags |= ImDrawFlags_RoundCornersBottomRight; }

                cell_flags = (flags == ImDrawFlags_RoundCornersNone || cell_flags == ImDrawFlags_RoundCornersNone) ? ImDrawFlags_RoundCornersNone : (cell_flags & flags);
                draw->add_rect_filled(draw_list, ImVec2(x1, y1), ImVec2(x2, y2), col_bg2, rounding, cell_flags);
            }
        }
    }
    else
    {
        draw->add_rect_filled(draw_list, p_min, p_max, col, rounding, flags);
    }
}

float hue_bar(float col[4], float h, ImVec2 size, bool* value_changed) {

    ImGuiStyle& style = ImGui::GetStyle();
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    ImGuiIO& io = ImGui::GetIO();

    float w{ size.x };
    static float move;

    ImVec2 pos{ window->DC.CursorPos };
    ImRect rect(pos, pos + ImVec2(w, size.y));

    const ImU32 col_hues[6 + 1]{ IM_COL32(255, 0, 0, IM_F32_TO_INT8_SAT(style.Alpha)), IM_COL32(255, 255, 0, IM_F32_TO_INT8_SAT(style.Alpha)), IM_COL32(0, 255, 0, IM_F32_TO_INT8_SAT(style.Alpha)), IM_COL32(0, 255, 255, IM_F32_TO_INT8_SAT(style.Alpha)), IM_COL32(0, 0, 255, IM_F32_TO_INT8_SAT(style.Alpha)), IM_COL32(255, 0, 255, IM_F32_TO_INT8_SAT(style.Alpha)), IM_COL32(255, 0, 0, IM_F32_TO_INT8_SAT(style.Alpha)) };    const ImU32 col_midgrey = IM_COL32(128, 128, 128, IM_F32_TO_INT8_SAT(style.Alpha));

    for (int i = 0; i < 6; ++i)
        draw->rect_filled_multi_color(window->DrawList, ImVec2(pos.x + i * (size.x / 6) - (i == 5 ? 1 : 0), rect.Min.y), ImVec2(pos.x + (i + 1) * (size.x / 6) + (i == 0 ? 1 : 0), rect.Max.y), col_hues[i], col_hues[i + 1], col_hues[i + 1], col_hues[i], 100.f, i == 0 ? ImDrawFlags_RoundCornersLeft : i == 5 ? ImDrawFlags_RoundCornersRight : ImDrawFlags_RoundCornersNone);

    move = ImLerp(move, h, gui->fixed_speed(25.f));
    draw->add_circle_filled(window->DrawList, { rect.Min.x + rect.GetHeight() / 2 + (w - rect.GetHeight()) * move, rect.GetCenter().y }, rect.GetHeight() / 2 + 2, gui->get_clr(clr->c_important.white_clr), 100.f);

    ImGui::InvisibleButton("hue", rect.GetSize());
    if (IsItemActive()) {
        h = ImSaturate((io.MousePos.x - pos.x) / (rect.GetWidth() - 1));
        *value_changed = true;
    }

    return h;
}

bool alpha_bar(float col[4], float* a, ImVec2 size, bool actived, bool* value_changed) {

    if (!actived) return false;

    ImGuiStyle& style{ ImGui::GetStyle() };
    ImGuiWindow* window{ ImGui::GetCurrentWindow() };
    ImGuiIO& io{ ImGui::GetIO() };

    float w{ size.x };
    static float move;

    ImVec2 pos{ window->DC.CursorPos };
    ImRect rect(pos, pos + ImVec2(w, size.y));

    render_color_rect_alpha_checkboard(window->DrawList, rect.Min, rect.Max, 0, w / 35, ImVec2(0.0f, 0.0f), 100.f, NULL);
    move = ImLerp(move, *a, gui->fixed_speed(25.f));

    draw->rect_filled_multi_color(window->DrawList, rect.Min, rect.Max, ImColor{ col[0], col[1], col[2], 0.f }, ImColor{ col[0], col[1], col[2], GImGui->Style.Alpha }, ImColor{ col[0], col[1], col[2], GImGui->Style.Alpha }, ImColor{ col[0], col[1], col[2], 0.f }, 100.f);
    draw->add_circle_filled(window->DrawList, { rect.Min.x + rect.GetHeight() / 2 + (w - rect.GetHeight()) * move, rect.GetCenter().y }, rect.GetHeight() / 2 + 2, gui->get_clr(clr->c_important.white_clr), 100.f);

    ImGui::InvisibleButton("alpha", rect.GetSize());
    if (IsItemActive()) {
        *a = ImSaturate((io.MousePos.x - pos.x) / (rect.GetWidth() - 1));
        *value_changed = true;
    }
}

void color(float col[4], float h, float* s, float* v, const ImVec2& size_arg, bool* value_changed) {

    ImGuiStyle& style{ ImGui::GetStyle() };
    ImGuiWindow* window{ ImGui::GetCurrentWindow() };
    ImGuiIO& io{ ImGui::GetIO() };

    static ImVec2 move;

    ImVec2 pos{ window->DC.CursorPos };
    ImRect rect(pos, pos + size_arg);

    ImVec4 hue_color_f(1, 1, 1, style.Alpha); ImGui::ColorConvertHSVtoRGB(h, 1, 1, hue_color_f.x, hue_color_f.y, hue_color_f.z);
    ImU32 hue_color32 = ColorConvertFloat4ToU32(hue_color_f);

    draw->rect_filled_multi_color(window->DrawList, rect.Min, rect.Max, gui->get_clr(clr->c_important.white_clr), hue_color32, hue_color32, gui->get_clr(clr->c_important.white_clr), set->c_element.rounding);
    draw->rect_filled_multi_color(window->DrawList, rect.Min - ImVec2(1, 1), rect.Max + ImVec2(1, 1), 0, 0, gui->get_clr(clr->c_important.black_clr), gui->get_clr(clr->c_important.black_clr), set->c_element.rounding);

    ImVec2 cursor_pos;
    cursor_pos.x = ImClamp(IM_ROUND(rect.Min.x + ImSaturate(*s) * rect.GetWidth()), rect.Min.x + 2, rect.Max.x - 2);
    cursor_pos.y = ImClamp(IM_ROUND(rect.Min.y + ImSaturate(1 - *v) * rect.GetHeight()), rect.Min.y + 2, rect.Max.y - 2);

    auto circle_col{ ImColor(col[0], col[1], col[2], 1.f) };
    move = ImLerp(move, cursor_pos, gui->fixed_speed(25.f));

    draw->add_circle_filled(window->DrawList, move, 5, gui->get_clr(circle_col));
    draw->add_circle(window->DrawList, move, 5, ImColor(255, 255, 255, int(style.Alpha * 255)), 100.f, 2.f);

    ImGui::InvisibleButton("sv", rect.GetSize());
    if (IsItemActive())
    {
        *s = ImSaturate((io.MousePos.x - rect.Min.x) / (rect.GetWidth() - 1)) <= 0 ? 0.01f : ImSaturate((io.MousePos.x - rect.Min.x) / (rect.GetWidth() - 1));
        *v = (1.0f - ImSaturate((io.MousePos.y - rect.Min.y) / (rect.GetHeight() - 1))) <= 0 ? 0.01f : 1.0f - ImSaturate((io.MousePos.y - rect.Min.y) / (rect.GetHeight() - 1));

        *value_changed = true;
    }
}

bool c_widget::color_picker(std::string_view label, float col[4], bool alpha)
{
    struct c_edit
    {
        ImVec4 text{ clr->c_text.text };
        ImVec2 position{ 0, 0 };
        float alpha{ 0.f };
        bool pressed{ false }, hovered{ false };
    };

    ImGuiContext& g_1{ *GImGui };
    const ImGuiStyle& style = g_1.Style;
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    const ImGuiID id{ window->GetID(label.data()) };

    const ImVec2 pos{ GetCurrentWindow()->DC.CursorPos };
    const float width{ GetContentRegionAvail().x };
    const float box_size{ 20 }, rect_correct_size{ 25 };

    const ImVec2 rect_size{ ImVec2(box_size, box_size) };
    const ImRect rect(pos, pos + ImVec2(width, rect_correct_size));

    bool value_changed = false;
    float h = 1.f, s = 1.f, v = 1.f, r = col[0], g = col[1], b = col[2], a = col[3];

    ItemSize(rect, 0);
    if (!ItemAdd(rect, id)) { return false; }

    bool hovered, held, pressed{ ButtonBehavior(rect, id, &hovered, &held) };

    c_edit* state = gui->anim_container(&state, id);

    if (ItemHoverable(g_1.LastItemData.Rect, g_1.LastItemData.ID, NULL) && g_1.IO.MouseClicked[0] || state->pressed && g_1.IO.MouseClicked[0] && !state->hovered) state->pressed = !state->pressed;
    state->text = ImLerp(state->text, state->pressed ? clr->c_text.text_active : clr->c_text.text, gui->fixed_speed(8.f));
    state->alpha = ImLerp(state->alpha, state->pressed ? 1.f : 0.f, gui->fixed_speed(15.f));

    draw->render_text(set->c_font.inter_regular[0], window->DrawList, rect.Min, rect.Max, gui->get_clr(state->text), label.data(), NULL, NULL, { 0.0, 0.5 }, NULL);

    ColorConvertRGBtoHSV(r, g, b, h, s, v);
    color_edit_restore_hs(col, &h, &s, &v);

    ImVec4 col_rgb{ col[0], col[1], col[2], col[3] };
    render_color_rect_alpha_checkboard(window->DrawList, ImVec2(rect.Max.x - rect_size.x, rect.Min.y + (rect_correct_size - box_size) / 2), rect.Max - ImVec2(0, (rect_correct_size - box_size) / 2), gui->get_clr(col_rgb), ImMin(30, 30) / 2.99f, ImVec2(0.f, 0.f), set->c_element.rounding, NULL);

    if (state->alpha <= 0.01f) state->position = ImGui::GetMousePos();

    if (state->alpha > 0.01f)
    {
       gui->push_style_color(ImGuiCol_WindowBg, gui->get_clr(clr->c_element.widget_layout));
       gui->push_style_var(ImGuiStyleVar_Alpha, { state->alpha });
       gui->push_style_var(ImGuiStyleVar_ItemSpacing, { 10, 15 });
       gui->push_style_var(ImGuiStyleVar_WindowPadding, { 10, 10 });
       gui->push_style_var(ImGuiStyleVar_WindowRounding, { 8.f });
       gui->push_style_var(ImGuiStyleVar_WindowBorderSize, { 0 });

        gui->set_next_window_pos(state->position);
        gui->begin((std::stringstream{} << label << "picker").str().c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration);
        {
            state->hovered = IsWindowHovered();

            color(col, h, &s, &v, { 160, 160 }, &value_changed);

            h = hue_bar(col, h, { 160, 4 }, &value_changed);

            alpha_bar(col, &a, { 160, 4 }, alpha, &value_changed);
        }

        gui->end();

        gui->pop_style_var(5);
        gui->pop_style_color(1);

        ColorConvertHSVtoRGB(h, s, v, r, g, b);

        if (value_changed) {
            g_1.ColorEditSavedHue = h;
            g_1.ColorEditSavedSat = s;
            g_1.ColorEditSavedColor = ImGui::ColorConvertFloat4ToU32(ImVec4(col[0], col[1], col[2], 0));

            col[0] = r;
            col[1] = g;
            col[2] = b;
            col[3] = a;
        }
    }

    return{ true };
}

bool c_widget::checkbox_with_picker(std::string_view label, bool* callback, float col[4], bool alpha)
{
    struct c_checkbox
    {
        ImVec4 background = clr->c_element.widget_layout;
        ImVec4 text_colored = clr->c_text.text;
        ImVec4 circle = clr->c_element.mark_circle_filling;

        float circle_offset = 0;

        ImVec2 position{ 0, 0 };
        float alpha{ 0.f };
        bool pressed{ false }, hovered{ false };
    };

    ImGuiWindow* window = GetCurrentWindow();
    ImGuiContext& g_1 = *GImGui;

    const ImGuiStyle& style = g_1.Style;
    const ImGuiID id = window->GetID(label.data());

    const ImVec2 label_size = CalcTextSize(label.data(), NULL, true);
    const ImVec2 pos = window->DC.CursorPos;

    const float weight = GetContentRegionAvail().x;
    const float height = 25;

    const ImRect clickable_rect(pos, pos + ImVec2(weight, height));
    const ImRect rect(pos + ImVec2(weight - 60, (height - 15) / 2), pos + ImVec2(weight - 30, (height + 15) / 2));

    bool value_changed = false;
    float h = 1.f, s = 1.f, v = 1.f, r = col[0], g = col[1], b = col[2], a = col[3];

    ItemSize(clickable_rect, 0.f);
    if (!ItemAdd(clickable_rect, id)) return false;

    bool hovered, held, pressed = ButtonBehavior(clickable_rect, id, &hovered, &held);

    c_checkbox* state = gui->anim_container(&state, id);

    if (ItemHoverable(g_1.LastItemData.Rect, g_1.LastItemData.ID, NULL) && g_1.IO.MouseClicked[1] || state->pressed && g_1.IO.MouseClicked[0] && !state->hovered) state->pressed = !state->pressed;

    state->text_colored = ImLerp(state->text_colored, *callback ? clr->c_text.text_active : clr->c_text.text, gui->fixed_speed(set->c_element.speed_animation));
    state->background = ImLerp(state->background, *callback ? clr->c_element.checkbox_layout_active : clr->c_element.widget_layout, gui->fixed_speed(set->c_element.speed_animation));

    state->circle_offset = ImLerp(state->circle_offset, *callback ? 20.f : 10.f, gui->fixed_speed(set->c_element.speed_animation));
    state->circle = ImLerp(state->circle, *callback ? clr->c_important.accent_clr : clr->c_element.mark_circle_filling, gui->fixed_speed(set->c_element.speed_animation));

    state->alpha = ImLerp(state->alpha, state->pressed ? 1.f : 0.f, gui->fixed_speed(15.f));

    if (pressed)
    {
        *callback = !(*callback);
        MarkItemEdited(id);
    }

    ImVec4 col_rgb{ col[0], col[1], col[2], col[3] };
    render_color_rect_alpha_checkboard(window->DrawList, ImVec2(clickable_rect.Max.x - 18, clickable_rect.Min.y + (height - 18) / 2), clickable_rect.Max - ImVec2(0, (height - 18) / 2), gui->get_clr(col_rgb), ImMin(30, 30) / 2.99f, ImVec2(0.f, 0.f), set->c_element.rounding, NULL);

    ColorConvertRGBtoHSV(r, g, b, h, s, v);
    color_edit_restore_hs(col, &h, &s, &v);

    if (state->alpha <= 0.01f) state->position = ImGui::GetMousePos();

    if (state->alpha > 0.01f)
    {
        gui->push_style_color(ImGuiCol_WindowBg, gui->get_clr(clr->c_element.widget_layout));
        gui->push_style_var(ImGuiStyleVar_Alpha, { state->alpha });
        gui->push_style_var(ImGuiStyleVar_ItemSpacing, { 10, 15 });
        gui->push_style_var(ImGuiStyleVar_WindowPadding, { 10, 10 });
        gui->push_style_var(ImGuiStyleVar_WindowRounding, { 8.f });
        gui->push_style_var(ImGuiStyleVar_WindowBorderSize, { 0 });

        gui->set_next_window_pos(state->position);
        gui->begin((std::stringstream{} << label << "picker").str().c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration);
        {
            state->hovered = IsWindowHovered();

            color(col, h, &s, &v, { 160, 160 }, &value_changed);

            h = hue_bar(col, h, { 160, 4 }, &value_changed);

            alpha_bar(col, &a, { 160, 4 }, alpha, &value_changed);
        }

        gui->end();

        gui->pop_style_var(5);
        gui->pop_style_color(1);

        ColorConvertHSVtoRGB(h, s, v, r, g, b);

        if (value_changed) {
            g_1.ColorEditSavedHue = h;
            g_1.ColorEditSavedSat = s;
            g_1.ColorEditSavedColor = ImGui::ColorConvertFloat4ToU32(ImVec4(col[0], col[1], col[2], 0));

            col[0] = r;
            col[1] = g;
            col[2] = b;
            col[3] = a;
        }
    }

    draw->add_rect_filled(window->DrawList, rect.Min, rect.Max, gui->get_clr(state->background), 100.f);

    draw->add_circle_filled(window->DrawList, { rect.Min.x + state->circle_offset, rect.GetCenter().y }, 10.f, gui->get_clr(state->background), 100.f);
    draw->add_circle_filled(window->DrawList, { rect.Min.x + state->circle_offset, rect.GetCenter().y }, 6.f, gui->get_clr(state->circle), 100.f);

    draw->render_text(window->DrawList, set->c_font.inter_regular[0], clickable_rect.Min, clickable_rect.Max, gui->get_clr(state->text_colored), label.data(), NULL, NULL, { 0.0, 0.5 });

    if (var->c_selection.selection_alpha == 0)
    {
        state->background = clr->c_element.widget_layout;
        state->text_colored = clr->c_text.text;
        state->circle = clr->c_element.mark_circle_filling;
        state->circle_offset = 0.f;
    }

    return pressed;
}
