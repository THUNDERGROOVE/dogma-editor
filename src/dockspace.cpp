#include "dockspace.h"

void draw_dockspace(bool *p_open) {
  if (*p_open) {
    static bool opt_fullscreen_persistant = true;
    bool opt_fullscreen = opt_fullscreen_persistant;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags =
        ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen) {
      ImGuiViewport *viewport = ImGui::GetMainViewport();
      ImGui::SetNextWindowPos(viewport->Pos);
      ImGui::SetNextWindowSize(viewport->Size);
      ImGui::SetNextWindowViewport(viewport->ID);
      ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
      ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
      window_flags |= ImGuiWindowFlags_NoTitleBar |
                      ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                      ImGuiWindowFlags_NoMove;
      window_flags |=
          ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
      window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", p_open, window_flags);
    ImGui::PopStyleVar();

    if (opt_fullscreen)
      ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO &io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
      ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
      dockspace_flags |= ImGuiDockNodeFlags_PassthruCentralNode;
      ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar()) {
      if (ImGui::BeginMenu("Docking")) {
        if (ImGui::MenuItem("Flag: NoSplit", "",
                            (dockspace_flags & ImGuiDockNodeFlags_NoSplit) !=
                                0))
          dockspace_flags ^= ImGuiDockNodeFlags_NoSplit;
        if (ImGui::MenuItem("Flag: NoResize", "",
                            (dockspace_flags & ImGuiDockNodeFlags_NoResize) !=
                                0))
          dockspace_flags ^= ImGuiDockNodeFlags_NoResize;
        if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "",
                            (dockspace_flags &
                             ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))
          dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode;
        if (ImGui::MenuItem("Flag: PassthruCentralNode", "",
                            (dockspace_flags &
                             ImGuiDockNodeFlags_PassthruCentralNode) != 0))
          dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode;
        if (ImGui::MenuItem(
                "Flag: AutoHideTabBar", "",
                (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))
          dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar;
        ImGui::Separator();
        if (ImGui::MenuItem("Close DockSpace", NULL, false, p_open != NULL))
          *p_open = false;
        ImGui::EndMenu();
      }

      ImGui::EndMenuBar();
    }

    ImGui::End();
  }
}
