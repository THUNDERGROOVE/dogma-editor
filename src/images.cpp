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

static img_t load_or_get_img2(const char *iconID) {
  if (img_cache.find(iconID) == img_cache.end()) {
      img_t t;
      memset(&t, 0, sizeof(t));
      stuff_entry_t *e = find_stuff_icon_group(__stuff, iconID);
      if (e == NULL) {
          return t;
      }
      LoadTextureFromMem(e->data, e->data_length, &t.tex, &t.width, &t.height);
      img_cache[std::string(iconID)] = t;
  } else {
      return img_cache[iconID];
  }
}

std::vector<std::string> split(std::string str,std::string sep){
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    std::vector<std::string> arr;
    current=strtok(cstr,sep.c_str());
    while(current!=NULL){
        arr.push_back(current);
        current=strtok(NULL,sep.c_str());
    }
    return arr;
}

img_t load_or_get_img(const char *iconID) {
    std::string ID(iconID);
    std::vector<std::string> bits = split(iconID, "_");

    // @TODO(NP): unsafe
    if (bits[0][0] == '0') {
        bits[0] = std::string(&bits[0].c_str()[1]);
    }

    if (bits[1][0] == '0') {
        bits[1] = std::string(&bits[1].c_str()[1]);
    }

    std::string _16(bits[0] + "_16_" + bits[1]);
    std::string _32(bits[0] + "_32_" + bits[1]);
    std::string _64(bits[0] + "_64_" + bits[1]);
    std::string _128(bits[0] + "_128_" + bits[1]);

    img_t out;
    memset(&out, 0, sizeof(out));

    out = load_or_get_img2(_16.c_str());
    if (out.tex != 0) {
        return out;
    }

    out = load_or_get_img2(_32.c_str());
    if (out.tex != 0) {
        return out;
    }

    out = load_or_get_img2(_64.c_str());
    if (out.tex != 0) {
        return out;
    }

    out = load_or_get_img2(_128.c_str());
    if (out.tex != 0) {
        return out;
    }

    return out;
}
