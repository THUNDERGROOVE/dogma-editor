#include "images.h"



#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "ccp_stuff.h"

std::map<std::string, img_t> img_cache;

static bool LoadTextureFromMem(const char* buffer, uint32_t size, GLuint* out_texture, int* out_width, int* out_height) {
    // Load from file
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load_from_memory((const unsigned char *)buffer, size, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}

img_t load_or_get_img(stuff_package_t *s, const char *iconID) {
  if (img_cache.find(iconID) == img_cache.end()) {
      img_t t;
      memset(&t, 0, sizeof(t));
      stuff_entry_t *e = find_stuff_icon(s, iconID);
      if (e == NULL) {
          return t;
      }
      LoadTextureFromMem(e->data, e->data_length, &t.tex, &t.width, &t.height);
      img_cache[std::string(iconID)] = t;
  } else {
      return img_cache[iconID];
  }
}
