#include "../settings/functions.h"

const char* keys[] =
{
    "None",
    "Mouse 1",
    "Mouse 2",
    "CN",
    "Mouse 3",
    "Mouse 4",
    "Mouse 5",
    "-",
    "Back",
    "Tab",
    "-",
    "-",
    "CLR",
    "Enter",
    "-",
    "-",
    "Shift",
    "CTL",
    "Menu",
    "Pause",
    "Caps",
    "KAN",
    "-",
    "JUN",
    "FIN",
    "KAN",
    "-",
    "Escape",
    "CON",
    "NCO",
    "ACC",
    "MAD",
    "Space",
    "PGU",
    "PGD",
    "End",
    "Home",
    "Left",
    "Up",
    "Right",
    "Down",
    "SEL",
    "PRI",
    "EXE",
    "PRI",
    "INS",
    "Delete",
    "HEL",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "WIN",
    "WIN",
    "APP",
    "-",
    "SLE",
    "Num 0",
    "Num 1",
    "Num 2",
    "Num 3",
    "Num 4",
    "Num 5",
    "Num 6",
    "Num 7",
    "Num 8",
    "Num 9",
    "MUL",
    "ADD",
    "SEP",
    "MIN",
    "Delete",
    "DIV",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "F11",
    "F12",
    "F13",
    "F14",
    "F15",
    "F16",
    "F17",
    "F18",
    "F19",
    "F20",
    "F21",
    "F22",
    "F23",
    "F24",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "NUM",
    "SCR",
    "EQU",
    "MAS",
    "TOY",
    "OYA",
    "OYA",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "Shift",
    "Shift",
    "Ctrl",
    "Ctrl",
    "Alt",
    "Alt"
};

bool c_widget::keybind(std::string_view label, int& key)
{
    struct c_keybind
    {
        ImVec4 text{ clr->c_text.text };
        float slow{ 0 };
    };

    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems) return false;

    ImGuiContext& g = *GImGui;
    ImGuiIO& io = g.IO;
    const ImGuiStyle& style = g.Style;

    const ImGuiID id = window->GetID(label.data());

    const ImVec2 pos = window->DC.CursorPos;
    const float width = GetContentRegionAvail().x;
    const float rect_size{ 25.f };

    const ImRect total_bb(pos, pos + ImVec2(width, rect_size));
    const ImRect clickable_bb(pos, pos + ImVec2(width, rect_size));

    ItemSize(total_bb, 0.f);
    if (!ItemAdd(total_bb, id, &total_bb)) return false;

    char buf_display[64] = "None";

    bool value_changed = false;
    int k = key;

    std::string active_key = "";
    active_key += keys[key];

    if (key != 0 && g.ActiveId != id) {
        strcpy_s(buf_display, active_key.c_str());
    }
    else if (g.ActiveId == id) {
        strcpy_s(buf_display, "...");
    }

    bool hovered = ItemHoverable(clickable_bb, id, 0);

    if (hovered && io.MouseClicked[0])
    {
        if (g.ActiveId != id) {
            memset(io.MouseDown, 0, sizeof(io.MouseDown));
            memset(io.KeysDown, 0, sizeof(io.KeysDown));
            key = 0;
        }
        ImGui::SetActiveID(id, window);
        ImGui::FocusWindow(window);
    }
    else if (io.MouseClicked[0]) {

        if (g.ActiveId == id) ImGui::ClearActiveID();
    }

    if (g.ActiveId == id) {
        for (auto i = 0; i < 5; i++) {
            if (io.MouseDown[i]) {
                switch (i) {
                case 0:
                    k = 0x01;
                    break;
                case 1:
                    k = 0x02;
                    break;
                case 2:
                    k = 0x04;
                    break;
                case 3:
                    k = 0x05;
                    break;
                case 4:
                    k = 0x06;
                    break;
                }
                value_changed = true;
                ImGui::ClearActiveID();
            }
        }
        if (!value_changed) {
            for (auto i = 0x08; i <= 0xA5; i++) {
                if (io.KeysDown[i]) {
                    k = i;
                    value_changed = true;
                    ImGui::ClearActiveID();

                }
            }
        }

        if (IsKeyPressedMap(ImGuiKey_Escape)) {
            key = 0;
            ImGui::ClearActiveID();
        }
        else {
            key = k;
        }
    }

    c_keybind* state = gui->anim_container(&state, id);

    ImRect clickable(ImVec2(total_bb.Max.x - (CalcTextSize(buf_display).x + 20), total_bb.Min.y), total_bb.Max);

    state->slow = ImLerp(state->slow, clickable.Min.x - total_bb.Min.x, gui->fixed_speed(20.f));
    state->text = ImLerp(state->text, g.ActiveId == id ? clr->c_text.text_active : clr->c_text.text, g.IO.DeltaTime * 6.f);

    draw->add_rect_filled(window->DrawList, ImVec2(state->slow + total_bb.Min.x, clickable.Min.y), clickable.Max, gui->get_clr(clr->c_element.widget_layout), set->c_element.rounding);

    draw->render_text(set->c_font.inter_regular[0], window->DrawList, clickable.Min, clickable.Max, gui->get_clr(clr->c_text.text_active), buf_display, NULL, NULL, { 0.5, 0.5 }, NULL);
    draw->render_text(set->c_font.inter_regular[1], window->DrawList, total_bb.Min, total_bb.Max, gui->get_clr(state->text), label.data(), NULL, NULL, { 0.0, 0.5 }, NULL);

    return value_changed;
}