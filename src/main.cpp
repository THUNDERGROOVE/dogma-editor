/*
 * dogma-editor: main.cpp
 * Copyright Nick Powell 2019
 */

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "bulkdata.h"


static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

static void invTypeWindow(cacheInvTypes *t) {
    char title_buf[1024];
    snprintf(title_buf, 1024, "Type: %s", t->typeName);
    ImGui::Begin(title_buf);
    ImGui::Text("typeID: %d", t->typeID);
    ImGui::Separator();
    ImGui::Text("typeName: %s", t->typeName);
    ImGui::Separator();
    ImGui::Text("groupID: %d", t->groupID);
    ImGui::Separator();
    ImGui::Text("typeName: %s", t->typeName);
    ImGui::Separator();
    ImGui::TextWrapped("description: %s", t->description);
    ImGui::Separator();
    ImGui::Text("graphicID: %d", t->graphicID);
    ImGui::Separator();
    ImGui::Text("radius: %f", t->radius);
    ImGui::Separator();
    ImGui::Text("mass: %f", t->mass);
    ImGui::Separator();
    ImGui::Text("volume: %f", t->volume);
    ImGui::Separator();
    ImGui::Text("capacity: %f", t->capacity);
    ImGui::Separator();
    ImGui::Text("portionSize: %d", t->portionSize);
    ImGui::Separator();
    ImGui::Text("raceID: %d", t->raceID);
    ImGui::Separator();
    ImGui::Text("basePrice: %f", t->basePrice);
    ImGui::Separator();
    ImGui::Text("published: %d", t->published);
    ImGui::Separator();
    ImGui::Text("marketGroupID: %d", t->marketGroupID);
    ImGui::Separator();
    ImGui::Text("chanceOfDuplicating: %f", t->chanceOfDuplicating);
    ImGui::Separator();
    ImGui::Text("soundID: %d", t->soundID);
    ImGui::Separator();
    ImGui::Text("iconID: %d", t->iconID);
    ImGui::Separator();
    ImGui::Text("dataID: %d", t->dataID);
    ImGui::Separator();
    ImGui::Text("typeNameID: %d", t->typeNameID);
    ImGui::Separator();
    ImGui::Text("descriptionID: %d", t->descriptionID);
    ImGui::Separator();
    ImGui::Text("copyTypeID: %d", t->copyTypeID);

    ImGui::End();
}

int main(int argc, char **argv) {

    bulkdata b;
    memset(&b, 0, sizeof(b));

    bulkdata_init(&b);

    cacheInvTypes t = cacheInvTypes_load_by(&b, 462);
    
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(1280, 720, argv[0], NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    bool err = gl3wInit() != 0;
    
    if (err) {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        invTypeWindow(&t);

        {
            ImGui::Begin("Dogma Edit Test");
            ImGui::Text("Inv Types: ");


            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
