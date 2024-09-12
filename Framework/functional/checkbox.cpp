#include "../settings/functions.h"

bool c_widget::checkbox(std::string_view label, bool* callback)
{
    struct c_checkbox
    {
        ImVec4 background = clr->c_element.widget_layout;
        ImVec4 text_colored = clr->c_text.text;
        ImVec4 circle = clr->c_element.mark_circle_filling;

        float circle_offset = 0;
    };

    ImGuiWindow* window = GetCurrentWindow();
    ImGuiContext& g = *GImGui;

    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label.data());

    const ImVec2 label_size = CalcTextSize(label.data(), NULL, true);
    const ImVec2 pos = window->DC.CursorPos;

    const float w = GetContentRegionAvail().x;
    const float h = 25;

    const ImRect clickable_rect(pos, pos + ImVec2(w, h));
    const ImRect rect(pos + ImVec2(w - 30, (h - 15) / 2), pos + ImVec2(w, (h + 15) / 2));

    ItemSize(clickable_rect, 0.f);
    if (!ItemAdd(clickable_rect, id)) return false;

    bool hovered, held, pressed = ButtonBehavior(clickable_rect, id, &hovered, &held);

    c_checkbox* state = gui->anim_container(&state, id);
    state->text_colored = ImLerp(state->text_colored, *callback ? clr->c_text.text_active : clr->c_text.text, gui->fixed_speed(set->c_element.speed_animation) );
    state->background = ImLerp(state->background, *callback ? clr->c_element.checkbox_layout_active : clr->c_element.widget_layout, gui->fixed_speed(set->c_element.speed_animation) );

    state->circle = ImLerp(state->circle, *callback ? clr->c_important.accent_clr : clr->c_element.mark_circle_filling, gui->fixed_speed(set->c_element.speed_animation) );
    state->circle_offset = ImLerp(state->circle_offset, *callback ? 20.f : 10.f, gui->fixed_speed(set->c_element.speed_animation) );

    if (pressed)
    {
        *callback = !(*callback);
        MarkItemEdited(id);
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
         state->circle_offset = 10.f;
     }

    return pressed;
}
