#include "../settings/functions.h"

static void color_edit_restore_hs(const float* col, float* H, float* S, float* V)
{
    ImGuiContext& g = *GImGui;

    if (*S == 0.0f || (*H == 0.0f && g.ColorEditSavedHue == 1))
        *H = g.ColorEditSavedHue;

    if (*V == 0.0f) *S = g.ColorEditSavedSat;
}

bool c_widget::hue_slider(std::string_view label, float col[4])
{
    struct hue_state
    {
        ImVec4 text;
        float hue, circle;
        float bar0_line_x;
    };

    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = GetCurrentWindow();

    ImDrawList* draw_list = window->DrawList;
    ImGuiStyle& style = g.Style;
    ImGuiIO& io = g.IO;

    ImVec2 pos = window->DC.CursorPos;

    float content = GetContentRegionAvail().x;
    float rect_height = 30.f;
    float hue_height = 2.f;

    const ImRect rect(pos + ImVec2(0, 6), pos + ImVec2(content, rect_height));
    const ImRect slider(pos + ImVec2(0, rect_height - 3), pos + ImVec2(content, rect_height - 1));

    ItemSize(ImRect(rect.Min, rect.Max + ImVec2(0, 5)));

    if (!ItemAdd(rect, GetID(label.data()))) return false;

    float H = col[0], S = col[1], V = col[2];
    float R = col[0], G = col[1], B = col[2];
    bool value_changed = false;

    ColorConvertRGBtoHSV(R, G, B, H, S, V);
    color_edit_restore_hs(col, &H, &S, &V);

    SetCursorScreenPos(ImVec2(pos.x, slider.GetCenter().y - rect_height / 2));
    InvisibleButton(label.data(), ImVec2(content, 15));

    if (IsItemActive())
    {
        float new_H = 1.f - ImSaturate((io.MousePos.x - pos.x) / (content - 1));
        float delta_H = new_H - H;
        if (abs(delta_H) > 0.5f) delta_H -= round(delta_H);
        H = fmod(H + delta_H * 0.5f + 1.0f, 1.0f);
        value_changed = true;
    }

    ColorConvertHSVtoRGB(H, S, V, col[0], col[1], col[2]);
    g.ColorEditSavedHue = H;
    g.ColorEditSavedSat = S;
    g.ColorEditSavedColor = ColorConvertFloat4ToU32(ImVec4(col[0], col[1], col[2], 1.f));

    const int style_alpha8 = IM_F32_TO_INT8_SAT(style.Alpha);
    const ImU32 col_hues[7] = { IM_COL32(255,0,0,style_alpha8), IM_COL32(255,0,255,style_alpha8), IM_COL32(0,0,255,style_alpha8),IM_COL32(0,255,255,style_alpha8), IM_COL32(0,255,0,style_alpha8), IM_COL32(255,255,0,style_alpha8), IM_COL32(255,0,0,style_alpha8) };

    hue_state* state = gui->anim_container(&state, GetID(label.data()));
    state->text = ImLerp(state->text, IsItemActive() ? clr->c_text.text_active : clr->c_text.text, gui->fixed_speed(set->c_element.speed_animation) );
    state->hue = ImLerp(state->hue, ImClamp(IM_ROUND(pos.x + (1.f - H) * content), pos.x + 4, pos.x + content - 4) - pos.x, gui->fixed_speed(set->c_element.speed_animation) );

    for (int i = 0; i < 6; ++i)
        draw->rect_filled_multi_color(draw_list, ImVec2(pos.x + i * (content / 6) - (i == 5 ? 1 : 0), slider.Min.y), ImVec2(pos.x + (i + 1) * (content / 6) + (i == 0 ? 1 : 0), slider.Max.y), col_hues[i], col_hues[i + 1], col_hues[i + 1], col_hues[i], 2.f, i == 0 ? ImDrawFlags_RoundCornersLeft : i == 5 ? ImDrawFlags_RoundCornersRight : ImDrawFlags_RoundCornersNone);
        draw->add_circle_filled(draw_list, ImVec2(state->hue + pos.x, slider.GetCenter().y), slider.GetHeight() + 3, gui->get_clr(ImColor(col[0], col[1], col[2], 1.f)));

        draw->render_text(set->c_font.inter_regular[0], window->DrawList, rect.Min, rect.Max, gui->get_clr(clr->c_text.text_active), "0-360", NULL, NULL, {1.0, 0.0}, NULL);
        draw->render_text(set->c_font.inter_regular[0], window->DrawList, rect.Min, rect.Max, gui->get_clr(state->text), label.data(), NULL, NULL, { 0.0, 0.0 }, NULL);

        if (var->c_selection.selection_alpha == 0)
        {
            state->hue = 0;
        }

    return value_changed;
}