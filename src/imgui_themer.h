#ifndef __IMGUI_THEMER_H_
#define __IMGUI_THEMER_H_


#include <vector>
#include <string>

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"

static inline ImVec4 ImLerp(const ImVec4& a, const ImVec4& b, float t)          { return ImVec4(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t, a.w + (b.w - a.w) * t); }

struct imgui_theme_t {
  ImVec4 text;
  ImVec4 head;
  ImVec4 area;
  ImVec4 body;
  ImVec4 pops;
  ImVec4 title;

  ImVec4 base_00;
  ImVec4 base_01;
  ImVec4 base_02;
  ImVec4 base_03;
  ImVec4 base_04;
  ImVec4 base_05;
  ImVec4 base_06;
  ImVec4 base_07;
  ImVec4 base_08;
  ImVec4 base_09;
  ImVec4 base_0A;
  ImVec4 base_0B;
  ImVec4 base_0C;
  ImVec4 base_0D;
  ImVec4 base_0E;
  ImVec4 base_0F;


  std::string name;

  void apply();
};

class imgui_themer_t {
  public:
  imgui_themer_t();

  bool showing;
  std::vector<imgui_theme_t> themes;
  void add_theme(imgui_theme_t t);

  void draw_selector();

};

extern imgui_themer_t *__themer;


#endif // __IMGUI_THEMER_H_
