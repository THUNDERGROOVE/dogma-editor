#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <stdio.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include "bulkdata.h"
#include <list>

extern GLFWwindow *window;

typedef std::list<edit_window *> window_list_t;

void newframe();
void endframe();
void shutdown_window();
void init_window(bool viewports);
void close_window();
void window_list_push(window_list_t *window_list, edit_window *w);
bool check_window_open(window_list_t *window_list, edit_window *w);

#endif

