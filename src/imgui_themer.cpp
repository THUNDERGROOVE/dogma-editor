#include "imgui_themer.h"

imgui_themer_t *__themer = NULL;

static void init() __attribute__((constructor(101)));

static void init() { __themer = new imgui_themer_t; }

#define color(loc, from, alpha)                                                \
  style.Colors[loc] = ImVec4(this->from.x, this->from.y, this->from.z, alpha);

void imgui_theme_t::apply() {
  ImGuiStyle &style = ImGui::GetStyle();

  color(ImGuiCol_Text, text, 1.00f);

  color(ImGuiCol_Text, text, 1.00f);
  color(ImGuiCol_TextDisabled, text, 0.58f);
  color(ImGuiCol_WindowBg, body, 0.95f);
  color(ImGuiCol_ChildWindowBg, area, 0.58f);
  color(ImGuiCol_Border, body, 0.00f);
  color(ImGuiCol_BorderShadow, body, 0.00f);
  color(ImGuiCol_FrameBg, area, 1.00f);
  color(ImGuiCol_FrameBgHovered, head, 0.78f);
  color(ImGuiCol_FrameBgActive, head, 1.00f);
  color(ImGuiCol_TitleBg, area, 1.00f);
  color(ImGuiCol_TitleBgCollapsed, area, 0.75f);
  color(ImGuiCol_TitleBgActive, head, 1.00f);
  color(ImGuiCol_MenuBarBg, area, 0.47f);
  color(ImGuiCol_ScrollbarBg, area, 1.00f);
  color(ImGuiCol_ScrollbarGrab, head, 0.21f);
  color(ImGuiCol_ScrollbarGrabHovered, head, 0.78f);
  color(ImGuiCol_ScrollbarGrabActive, head, 1.00f);
  // style.Colors[ImGuiCol_ComboBg] = ImVec4( this->area.x, this->area.y,
  // this->area.z, 1.00f );
  color(ImGuiCol_CheckMark, head, 0.80f);
  color(ImGuiCol_SliderGrab, head, 0.50f);
  color(ImGuiCol_SliderGrabActive, head, 1.00f);
  color(ImGuiCol_Button, head, 0.50f);
  color(ImGuiCol_ButtonHovered, head, 0.86f);
  color(ImGuiCol_ButtonActive, head, 1.00f);
  color(ImGuiCol_Header, base_09, 0.76f);
  color(ImGuiCol_HeaderHovered, head, 0.86f);
  color(ImGuiCol_HeaderActive, base_09, 1.00f);
  // style.Colors[ImGuiCol_Column] = ImVec4( this->head.x, this->head.y,
  // this->head.z, 0.32f ); style.Colors[ImGuiCol_ColumnHovered] = ImVec4(
  // this->head.x, this->head.y, this->head.z, 0.78f );
  // style.Colors[ImGuiCol_ColumnActive] = ImVec4( this->head.x, this->head.y,
  // this->head.z, 1.00f );
  color(ImGuiCol_ResizeGrip, head, 0.15f);
  color(ImGuiCol_ResizeGripHovered, head, 0.78f);
  color(ImGuiCol_ResizeGripActive, head, 1.00f);
  // style.Colors[ImGuiCol_CloseButton] = ImVec4( this->text.x, this->text.y,
  // this->text.z, 0.16f ); style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(
  // this->text.x, this->text.y, this->text.z, 0.39f );
  // style.Colors[ImGuiCol_CloseButtonActive] = ImVec4( this->text.x,
  // this->text.y, this->text.z, 1.00f );
  color(ImGuiCol_PlotLines, text, 0.63f);
  color(ImGuiCol_PlotLinesHovered, head, 1.00f);
  color(ImGuiCol_PlotHistogram, text, 0.63f);
  color(ImGuiCol_PlotHistogramHovered, head, 1.00f);
  color(ImGuiCol_TextSelectedBg, head, 0.43f);
  color(ImGuiCol_PopupBg, pops, 0.92f);
  color(ImGuiCol_ModalWindowDarkening, area, 0.73f);

  // Tabs

  style.Colors[ImGuiCol_Tab] =
      ImLerp(style.Colors[ImGuiCol_Header],
             style.Colors[ImGuiCol_TitleBgActive], 0.80f);
  style.Colors[ImGuiCol_TabHovered] = style.Colors[ImGuiCol_HeaderHovered];
  style.Colors[ImGuiCol_TabActive] =
      ImLerp(style.Colors[ImGuiCol_HeaderActive],
             style.Colors[ImGuiCol_TitleBgActive], 0.60f);
  style.Colors[ImGuiCol_TabUnfocused] =
      ImLerp(style.Colors[ImGuiCol_Tab], style.Colors[ImGuiCol_TitleBg], 0.80f);
  style.Colors[ImGuiCol_TabUnfocusedActive] = ImLerp(
      style.Colors[ImGuiCol_TabActive], style.Colors[ImGuiCol_TitleBg], 0.40f);
}

imgui_themer_t::imgui_themer_t() { this->showing = false; }

void imgui_themer_t::add_theme(imgui_theme_t t) { this->themes.push_back(t); }

void imgui_themer_t::draw_selector() {
  if (ImGui::Begin("Theme Selector", &this->showing)) {
    for (uint32_t i = 0; i < this->themes.size(); i++) {
      imgui_theme_t t = this->themes[i];
      ImGui::PushID(i);
      if (ImGui::Button(t.name.c_str())) {
        t.apply();
      }
      ImGui::PopID();
    }
  }
  ImGui::End();
}
