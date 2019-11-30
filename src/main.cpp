/*
 * dogma-editor: main.cpp
 * Copyright Nick Powell 2019
 */

#include <stdio.h>
#include <map>
#include <unordered_map>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "bulkdata.h"
#include "Allocator.h"

#include "window.h"

#include <list>
#include <thread>

#include "imgui_themer.h"
#include "dockspace.h"
#include "parseargs.h"

loading_status_t *loading_status = NULL;
cache_collection cc;
bulkdata b;

void load_thread() {
    loading_status = new loading_status_t;


    memset(&b, 0, sizeof(b));

    bulkdata_init(&b);

    cc = cache_load_all(&b, loading_status);
};

std::list<edit_window*> window_list;

int main(int argc, char **argv) {

    bool dockspace = true;
    bool viewports = false;
    if (has_flag(argc, argv, "-viewports")) {
        printf("Enabling viewports\n");
        dockspace = false;
        viewports = true;
    }
    init_window(viewports);

    std::thread t1(load_thread);
    t1.detach();


    while (!glfwWindowShouldClose(window)) {
        newframe();

        //ImGui::ShowDemoWindow();
        draw_dockspace(&dockspace);


        if (!loading_status->done) {
            if (ImGui::BeginPopupModal("loading_status", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_Modal)) {
              ImGui::Text("%s", loading_status->label);
              ImGui::EndPopup();
            }
            ImGui::OpenPopup("loading_status");
            endframe();
            continue;
        }

        draw_main_window();
        draw_search_windows(&cc, &window_list);

        ImGui::Text("Window list count %d", window_list.size());
        ImGui::Text("Dirty records count %d", cache_count_dirty(cc));
        if (ImGui::Button("Save dirty")) {
            save_all_dirty(&cc, &b);
        }
        ImGui::Text("DB Handle: %p\n", b.db);

        ImGui::SameLine();
        if (ImGui::Button("Exit")) {
            close_window();
            bulkdata_shutdown(&b);
            continue;
        }

        window_list_draw(&window_list);

        endframe();
    }
    shutdown_window();
    return 0;
}
