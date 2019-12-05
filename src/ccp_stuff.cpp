#include "ccp_stuff.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>

stuff_package_t *__resui = NULL;

stuff_package_t *open_stuff(const char *filename) {
  FILE *f = fopen(filename, "rb");
  if (f == NULL) {
    return NULL;
  }

  stuff_package_t *s = (stuff_package_t *)calloc(1, sizeof(stuff_package_t));

  fread(&s->entry_num, sizeof(uint32_t), 1, f);
  s->entries = (stuff_entry_t *)calloc(s->entry_num, sizeof(stuff_entry_t));

  // Collect filenames
  for (uint32_t i = 0; i < s->entry_num; i++) {
    stuff_entry_t *e = &s->entries[i];
    fread(&e->data_length, sizeof(uint32_t), 1, f);
    fread(&e->filename_length, sizeof(uint32_t), 1, f);

    e->filename = (char *)calloc(1, e->filename_length + 1);
    e->data = (char *)calloc(1, e->data_length); // May as well allocate here

    fread(e->filename, sizeof(char), e->filename_length + 1,
          f); // Gotta eat that null
  }

  for (uint32_t i = 0; i < s->entry_num; i++) {
    stuff_entry_t *e = &s->entries[i];
    fread(e->data, sizeof(char), e->data_length, f);
  }

  return s;
}
void close_Stuff(stuff_package_t *s) {
  for (uint32_t i = 0; i < s->entry_num; i++) {
    stuff_entry_t *e = &s->entries[i];
    if (e->data != NULL) {
      free(e->data);
      e->data = NULL;
    }
    if (e->filename != NULL) {
      free(e->filename);
      e->filename = NULL;
    }
  }
  free(s->entries);
  s->entries = NULL;
  free(s);
  s = NULL;
}

stuff_entry_t *find_stuff_icon(stuff_package_t *s, const char *iconID) {
    std::string icon_path("res\\UI\\texture\\icons\\");
    icon_path.append(iconID);
    icon_path.append(".png");
    for (uint32_t i = 0; i < s->entry_num; i++) {
        stuff_entry_t *e = &s->entries[i];
        if (strcmp(e->filename, icon_path.c_str()) == 0) {
            return e;
        }
    }
    return NULL;
}
