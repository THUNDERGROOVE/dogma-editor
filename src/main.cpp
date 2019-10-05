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

std::list<edit_window*> window_list;

int main(int argc, char **argv) {

    init_window();

    bulkdata b;
    memset(&b, 0, sizeof(b));

    bulkdata_init(&b);

    std::vector<cacheInvTypes *> results;
    char buffer[1024];
    memset(buffer, 0, 1024);

    cache_collection cc = cache_load_all(&b);

    b.inv_types.LoadCache(&b);

    while (!glfwWindowShouldClose(window)) {
        newframe();
        
        ImGui::Begin("Dogma Edit Test");
        ImGui::Text("InvCache Size: %d", b.inv_types.cache.size());
        ImGui::InputText("Inv Types: ", buffer, 1024);

        if (strcmp(buffer, "") != 0) {
            for (uint32_t i = 0; i < b.inv_types.cache.size(); i++) {
                cacheInvTypes *t = &b.inv_types.cache[i];
                if (strstr(t->typeName, buffer) != NULL) {
                    results.push_back(t);
                }
            }
            ImGui::Text("Results: %d", results.size());

            ImGui::Separator();

            for (uint32_t i = 0; i < results.size(); i++) {
                cacheInvTypes *t = results[i];
                ImGui::Text("[%d] %s", t->typeID, t->typeName);
                ImGui::SameLine();
                if (ImGui::Button(t->typeName)) {
                    printf("Opening edit window\n");
                    edit_window *w = calloc(1, sizeof(edit_window));
                    w->data = t;
                    w->typeID = t->typeID;
                    w->show = true;
                    w->tag = tag_cacheInvTypes;
                    window_list.push_back(w);
                }

                ImGui::Separator();
            }

            results.clear();


        }
        ImGui::End();

        for (auto it = window_list.begin(); it != window_list.end(); it++) {
            edit_window *w = *it;
            if (w->show == false) {
                it = window_list.erase(it);
                printf("Closing edit window\n");
                //free(it);
                continue;
            }
            //invTypeWindow(w);
            switch (w->tag) {
            case tag_cacheInvTypes:
                {
            cacheInvTypes_draw_edit(w);
                } break;
            }
        }

        endframe();
    }
    shutdown_window();
    return 0;
}
