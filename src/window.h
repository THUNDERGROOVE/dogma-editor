#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <stdio.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

extern GLFWwindow *window;

void newframe();
void endframe();
void shutdown_window();
void init_window(bool viewports);
void close_window();

#endif

