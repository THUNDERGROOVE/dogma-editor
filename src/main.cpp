/*
 * dogma-editor: main.cpp
 * Copyright Nick Powell 2019
 */

#include <map>
#include <stdio.h>
#include <unordered_map>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "Allocator.h"
#include "bulkdata.h"

#include "window.h"

#include <list>
#include <thread>

#include "dockspace.h"
#include "imgui_themer.h"
#include "parseargs.h"
#include "ccp_stuff.h"
#include "images.h"

loading_status_t *loading_status = NULL;
cache_collection cc;
bulkdata b;

stuff_package_t *resui = NULL;

void load_thread() {
  loading_status = new loading_status_t;

  memset(&b, 0, sizeof(b));

  bulkdata_init(&b);

  cc = cache_load_all(&b, loading_status);
  loading_status->done = false;
  __resui = open_stuff("resui.stuff");
  loading_status->label = "Loading resui.stuff...";
  loading_status->done = true;

    for (uint32_t i = 0; i < __resui->entry_num; i++) {
        stuff_entry_t *e = &__resui->entries[i];
        printf(" > %s\n", e->filename);
    }
};

std::list<edit_window *> window_list;

int main(int argc, char **argv) {
    // TODO(np): load in thread...


  bool dockspace = true;
  bool viewports = false;
  if (has_flag(argc, argv, "-viewports")) {
    printf("Enabling viewports\n");
    dockspace = false;
    viewports = true;
  }
  init_window(viewports);
  __themer->themes[0].apply();

  // ImGui::GetIO().Fonts->AddFontFromFileTTF("SourceSansPro-Regular.ttf", 16,
  // NULL);
  ImGui::GetIO().Fonts->AddFontDefault();
  static const ImWchar icon_ranges[] = {0xe000, 0xe0fe, 0x0};
  ImFontConfig config;
  config.MergeMode = true;
  config.OversampleH = 3;
  config.OversampleV = 1;
  config.PixelSnapH = true;
  config.GlyphOffset = ImVec2(0.0f, 3.0f);
  ImGui::GetIO().Fonts->AddFontFromFileTTF("OpenFontIcons.ttf", 15, &config,
                                           icon_ranges);

  std::thread t1(load_thread);
  t1.detach();

  while (!glfwWindowShouldClose(window)) {
    newframe();

    if (!loading_status->done) {
      if (ImGui::BeginPopupModal("loading_status", NULL,
                                 ImGuiWindowFlags_AlwaysAutoResize |
                                     ImGuiWindowFlags_Modal)) {
        ImGui::Text("%s", loading_status->label);
        ImGui::EndPopup();
      }
      ImGui::OpenPopup("loading_status");
      endframe();
      continue;
    }

    // ImGui::ShowDemoWindow();
    draw_dockspace(&dockspace);
    auto io = ImGui::GetIO();
    auto disp_size = io.DisplaySize;

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(disp_size.x, 45));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    if (ImGui::Begin("Tools", NULL,
                     ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove |
                         ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoDocking |
                         ImGuiWindowFlags_NoTitleBar)) {
        ImGui::PopStyleVar(2);

      ImGui::Text("Dirty records %d", cache_count_dirty(cc));
      ImGui::SameLine();

      ImVec4 green = __themer->themes[0].base_0B;
      ImVec4 red = __themer->themes[0].base_08;
      green.w = 1.0f;
      red.w = 1.0f;
      ImGui::PushStyleColor(ImGuiCol_Button, green);
      if (ImGui::Button(u8" Save dirty")) {
        save_all_dirty(&cc, &b);
      }
      ImGui::PopStyleColor();

      //img_t img = load_or_get_img(resui, "73_16_11");

      ImGui::SameLine();
      ImGui::PushStyleColor(ImGuiCol_Button, red);
      if (ImGui::Button(" Exit")) {
        close_window();
        bulkdata_shutdown(&b);
        continue;
      }
      ImGui::PopStyleColor();

      ImGui::End();
    }

    //ImGui::ShowFontSelector("Fonts");

    draw_main_window();
    draw_search_windows(&cc, &window_list);

    window_list_draw(&window_list, &cc);

    endframe();
  }
  shutdown_window();
  return 0;
}
