#include "../settings/functions.h"

bool begin_child_ex(const char* name, ImGuiID id, const ImVec2& size_arg, ImGuiChildFlags child_flags, ImGuiWindowFlags window_flags)
{
    struct c_child
    {
        float state = 0;
        float slow = 0;
    };

    ImGuiContext& g = *GImGui;
    ImGuiWindow* parent_window = g.CurrentWindow;
    IM_ASSERT(id != 0);

    const ImGuiChildFlags ImGuiChildFlags_SupportedMask_ = ImGuiChildFlags_Border | ImGuiChildFlags_AlwaysUseWindowPadding | ImGuiChildFlags_ResizeX | ImGuiChildFlags_ResizeY | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_FrameStyle;
    IM_UNUSED(ImGuiChildFlags_SupportedMask_);

#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    if (window_flags & ImGuiWindowFlags_AlwaysUseWindowPadding) child_flags |= ImGuiChildFlags_AlwaysUseWindowPadding;
#endif

    if (child_flags & ImGuiChildFlags_AutoResizeX) child_flags &= ~ImGuiChildFlags_ResizeX;
    if (child_flags & ImGuiChildFlags_AutoResizeY) child_flags &= ~ImGuiChildFlags_ResizeY;

    window_flags |= ImGuiWindowFlags_ChildWindow | ImGuiWindowFlags_NoTitleBar;
    window_flags |= (parent_window->Flags & ImGuiWindowFlags_NoMove);

    if (child_flags & (ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysAutoResize)) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
    if ((child_flags & (ImGuiChildFlags_ResizeX | ImGuiChildFlags_ResizeY)) == 0) window_flags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;

    g.NextWindowData.Flags |= ImGuiNextWindowDataFlags_HasChildFlags;
    g.NextWindowData.ChildFlags = child_flags;

    const ImVec2 size_avail = GetContentRegionAvail();
    const ImVec2 size_default((child_flags & ImGuiChildFlags_AutoResizeX) ? 0.0f : size_avail.x, (child_flags & ImGuiChildFlags_AutoResizeY) ? 0.0f : size_avail.y);
    float bar_height{ 35 };

    c_child* state = gui->anim_container(&state, id);

    ImVec2 size = size_arg;
    if (size.x <= 0) size.x = (GetContentRegionMax().x - set->c_child.content_window_padding.x - set->c_window.scrollbar_size) / 2;
    if (size.y <= 0) size.y = state->state + set->c_child.child_window_padding.y * 2;

    SetNextWindowSize(size);
    SetNextWindowPos(parent_window->DC.CursorPos + ImVec2(0, bar_height));

    draw->add_rect_filled(parent_window->DrawList, parent_window->DC.CursorPos, parent_window->DC.CursorPos + ImVec2(size.x, bar_height), gui->get_clr(clr->c_child.layout), set->c_child.rounding, ImDrawFlags_RoundCornersTop);
    
    draw->rect_filled_multi_color(parent_window->DrawList, parent_window->DC.CursorPos, parent_window->DC.CursorPos + ImVec2(size.x / 2, bar_height), gui->get_clr(clr->c_important.accent_clr, 0.f), gui->get_clr(clr->c_important.accent_clr, 0.3f), gui->get_clr(clr->c_important.accent_clr, 0.3f), gui->get_clr(clr->c_important.accent_clr, 0.f), set->c_child.rounding, ImDrawFlags_RoundCornersTopLeft);
    draw->rect_filled_multi_color(parent_window->DrawList, parent_window->DC.CursorPos + ImVec2(size.x / 2, 0), parent_window->DC.CursorPos + ImVec2(size.x, bar_height), gui->get_clr(clr->c_important.accent_clr, 0.3f), gui->get_clr(clr->c_important.accent_clr, 0.f), gui->get_clr(clr->c_important.accent_clr, 0.0f), gui->get_clr(clr->c_important.accent_clr, 0.3f), set->c_child.rounding, ImDrawFlags_RoundCornersTopRight);

    draw->add_rect_filled(parent_window->DrawList, parent_window->DC.CursorPos + ImVec2(0, bar_height + 1), parent_window->DC.CursorPos + ImVec2(size.x, size.y + bar_height), gui->get_clr(clr->c_child.layout), set->c_child.rounding, ImDrawFlags_RoundCornersBottom);
    draw->render_text(parent_window->DrawList, set->c_font.inter_medium[1], parent_window->DC.CursorPos, parent_window->DC.CursorPos + ImVec2(size.x, bar_height), gui->get_clr(clr->c_text.text_active), name, 0, 0, {0.5, 0.5});


    const char* temp_window_name;

    if (name)
        ImFormatStringToTempBuffer(&temp_window_name, NULL, "%s/%s_%08X", parent_window->Name, name, id);
    else
        ImFormatStringToTempBuffer(&temp_window_name, NULL, "%s/%08X", parent_window->Name, id);

    const bool ret = gui->begin(temp_window_name, NULL, window_flags);

    ImGuiWindow* child_window = g.CurrentWindow;
    child_window->ChildId = id;

    state->slow = ImLerp(state->slow, child_window->ContentSize.y, gui->fixed_speed(set->c_element.speed_animation) );
    state->state = state->slow;

    if (child_window->BeginCount == 1) parent_window->DC.CursorPos = child_window->Pos;

    const ImGuiID temp_id_for_activation = ImHashStr("##Child", 0, id);
    if (g.ActiveId == temp_id_for_activation) ClearActiveID();
    
    if (g.NavActivateId == id && !(window_flags & ImGuiWindowFlags_NavFlattened) && (child_window->DC.NavLayersActiveMask != 0 || child_window->DC.NavWindowHasScrollY))
    {
        FocusWindow(child_window);
        NavInitWindow(child_window, false);
        SetActiveID(temp_id_for_activation, child_window);
        g.ActiveIdSource = g.NavInputSource;
    }
    return ret;
}

bool c_gui::begin_child(std::string_view name, const ImVec2& size_arg, ImGuiChildFlags child_flags, ImGuiWindowFlags window_flags)
{
    ImGuiID id = GetCurrentWindow()->GetID(name.data());

    push_style_var(ImGuiStyleVar_WindowPadding, set->c_child.content_window_padding);
    push_style_var(ImGuiStyleVar_ItemSpacing, set->c_child.content_item_spacing);

    return begin_child_ex(name.data(), id, size_arg, child_flags, window_flags | ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
}

void c_gui::end_child()
{
    ImGuiContext& g = *GImGui;
    ImGuiWindow* child_window = g.CurrentWindow;

    pop_style_var(2);

    IM_ASSERT(g.WithinEndChild == false);
    IM_ASSERT(child_window->Flags & ImGuiWindowFlags_ChildWindow);

    g.WithinEndChild = true;
    ImVec2 child_size = child_window->Size;
    gui->end();

    if (child_window->BeginCount == 1)
    {
        ImGuiWindow* parent_window = g.CurrentWindow;
        ImRect bb(parent_window->DC.CursorPos, parent_window->DC.CursorPos + child_size);

        ItemSize(child_size);

        if (child_window->Flags & ImGuiWindowFlags_NavFlattened) parent_window->DC.NavLayersActiveMaskNext |= child_window->DC.NavLayersActiveMaskNext;

        if (g.HoveredWindow == child_window)  g.LastItemData.StatusFlags |= ImGuiItemStatusFlags_HoveredWindow;
    }
    g.WithinEndChild = false;
    g.LogLinePosY = -FLT_MAX;
}







bool begin_def_child_ex(const char* name, ImGuiID id, const ImVec2& size_arg, ImGuiChildFlags child_flags, ImGuiWindowFlags window_flags)
{
    ImGuiContext& g = *GImGui;
    ImGuiWindow* parent_window = g.CurrentWindow;
    IM_ASSERT(id != 0);

    const ImGuiChildFlags ImGuiChildFlags_SupportedMask_ = ImGuiChildFlags_Border | ImGuiChildFlags_AlwaysUseWindowPadding | ImGuiChildFlags_ResizeX | ImGuiChildFlags_ResizeY | ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_FrameStyle;
    IM_UNUSED(ImGuiChildFlags_SupportedMask_);

#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    if (window_flags & ImGuiWindowFlags_AlwaysUseWindowPadding) child_flags |= ImGuiChildFlags_AlwaysUseWindowPadding;
#endif

    if (child_flags & ImGuiChildFlags_AutoResizeX) child_flags &= ~ImGuiChildFlags_ResizeX;
    if (child_flags & ImGuiChildFlags_AutoResizeY) child_flags &= ~ImGuiChildFlags_ResizeY;

    window_flags |= ImGuiWindowFlags_ChildWindow | ImGuiWindowFlags_NoTitleBar;
    window_flags |= (parent_window->Flags & ImGuiWindowFlags_NoMove);

    if (child_flags & (ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysAutoResize)) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
    if ((child_flags & (ImGuiChildFlags_ResizeX | ImGuiChildFlags_ResizeY)) == 0) window_flags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;

    g.NextWindowData.Flags |= ImGuiNextWindowDataFlags_HasChildFlags;
    g.NextWindowData.ChildFlags = child_flags;

    const ImVec2 size_avail = GetContentRegionAvail();
    const ImVec2 size_default((child_flags & ImGuiChildFlags_AutoResizeX) ? 0.0f : size_avail.x, (child_flags & ImGuiChildFlags_AutoResizeY) ? 0.0f : size_avail.y);
    const ImVec2 size = CalcItemSize(size_arg, size_default.x, size_default.y);

    gui->set_next_window_size(size);

    //  draw->add_rect(GetForegroundDrawList(), parent_window->DC.CursorPos, parent_window->DC.CursorPos + size, gui->get_clr(clr->c_important.accent_clr), 0.f);

    const char* temp_window_name;

    if (name)
        ImFormatStringToTempBuffer(&temp_window_name, NULL, "%s/%s_%08X", parent_window->Name, name, id);
    else
        ImFormatStringToTempBuffer(&temp_window_name, NULL, "%s/%08X", parent_window->Name, id);

    const bool ret = gui->begin(temp_window_name, NULL, window_flags);

    ImGuiWindow* child_window = g.CurrentWindow;
    child_window->ChildId = id;

    if (child_window->BeginCount == 1) parent_window->DC.CursorPos = child_window->Pos;

    const ImGuiID temp_id_for_activation = ImHashStr("##Child", 0, id);
    if (g.ActiveId == temp_id_for_activation) ClearActiveID();

    if (g.NavActivateId == id && !(window_flags & ImGuiWindowFlags_NavFlattened) && (child_window->DC.NavLayersActiveMask != 0 || child_window->DC.NavWindowHasScrollY))
    {
        FocusWindow(child_window);
        NavInitWindow(child_window, false);
        SetActiveID(temp_id_for_activation, child_window);
        g.ActiveIdSource = g.NavInputSource;
    }
    return ret;
}

bool begin_def_child(std::string_view name, const ImVec2& size_arg, ImGuiChildFlags child_flags, ImGuiWindowFlags window_flags)
{
    ImGuiID id = GetCurrentWindow()->GetID(name.data());
    return begin_def_child_ex(name.data(), id, size_arg, child_flags, window_flags);
}

void end_def_child()
{
    ImGuiContext& g = *GImGui;
    ImGuiWindow* child_window = g.CurrentWindow;

    IM_ASSERT(g.WithinEndChild == false);
    IM_ASSERT(child_window->Flags & ImGuiWindowFlags_ChildWindow);

    g.WithinEndChild = true;
    ImVec2 child_size = child_window->Size;
    gui->end();

    if (child_window->BeginCount == 1)
    {
        ImGuiWindow* parent_window = g.CurrentWindow;
        ImRect bb(parent_window->DC.CursorPos, parent_window->DC.CursorPos + child_size);
        ItemSize(child_size);

        if (child_window->Flags & ImGuiWindowFlags_NavFlattened) parent_window->DC.NavLayersActiveMaskNext |= child_window->DC.NavLayersActiveMaskNext;

        if (g.HoveredWindow == child_window)  g.LastItemData.StatusFlags |= ImGuiItemStatusFlags_HoveredWindow;
    }
    g.WithinEndChild = false;
    g.LogLinePosY = -FLT_MAX;
}

void c_gui::begin_content(const char* id, const ImVec2& size_arg, const ImVec2& padding, const ImVec2& spacing, bool move)
{
    push_style_var(ImGuiStyleVar_WindowPadding, padding);
    push_style_var(ImGuiStyleVar_ItemSpacing, spacing);

    begin_def_child_ex(id, GetCurrentWindow()->GetID(id), size_arg, move ? (ImGuiChildFlags_None, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_AlwaysUseWindowPadding) : (ImGuiChildFlags_None, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoMove), 0);
}

void c_gui::end_content()
{
    end_def_child();
    pop_style_var(2);
}
