#ifndef __IMAGES_H_
#define __IMAGES_H_


#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "window.h"

#include "stb_image.h"
#include <map>
#include  "ccp_stuff.h"

struct img_t {
    GLuint tex;
    int width;
    int height;
};

img_t load_or_get_img(const char *iconID);

#endif // __IMAGES_H_
