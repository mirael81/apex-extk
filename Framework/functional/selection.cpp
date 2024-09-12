#include "../settings/functions.h"

bool c_gui::selection(std::string_view icon, std::string_view label, int selection_id, int& selection_variable, const ImVec2& size)
{
    struct c_page
    {
        ImVec4 icon{ clr->c_text.text };
        ImVec4 text{ clr->c_text.text };

        float alpha{ 1.f };
    };

    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems) return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id{ window->GetID(selection_id) };

    const bool selected{ selection_id == selection_variable };
    const float padding{ 20 };

    const ImVec2 pos{ window->DC.CursorPos };

    const ImRect rect(pos, pos + size);

    ItemSize(rect, 0);
    if (!ItemAdd(rect, id)) { return false; }

    bool hovered, held, pressed{ ButtonBehavior(rect, id, &hovered, &held) };
    if (pressed) selection_variable = selection_id;

    c_page* state{ gui->anim_container(&state, id) };
    state->alpha = ImLerp(state->alpha, selected ? 1.f : 0.f, gui->fixed_speed(set->c_element.speed_animation) );
    state->text = ImLerp(state->text, selected ? clr->c_text.text_active : clr->c_text.text_selection, gui->fixed_speed(set->c_element.speed_animation) );
    state->icon = ImLerp(state->icon, selected ? clr->c_important.accent_clr : clr->c_text.text_selection, gui->fixed_speed(set->c_element.speed_animation) );

    draw->add_rect_filled(window->DrawList, rect.Min, rect.Max, gui->get_clr(clr->c_element.selection_layout, state->alpha), set->c_element.rounding);

    draw->render_text(window->DrawList, set->c_font.icon[2], rect.Min, rect.Min + ImVec2(size.y, size.y), gui->get_clr(state->icon), icon.data(), NULL, NULL, {0.5, 0.5}, NULL);
    draw->render_text(window->DrawList, set->c_font.inter_regular[1], rect.Min + ImVec2(size.y, 0), rect.Max, gui->get_clr(state->text), label.data(), NULL, NULL, {0.0, 0.57}, NULL);

    return{ pressed };
}