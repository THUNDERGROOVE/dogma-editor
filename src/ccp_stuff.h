#ifndef __CCP_STUFF_H_
#define __CCP_STUFF_H_

#include <stdint.h>
#include <dirent.h>

#include "cache_types.h"

// oh nice don't even have to pack this shit
struct stuff_entry_t {
    uint32_t data_length;
    uint32_t filename_length;
    char *filename;
    char *data;
};

struct stuff_package_t {
    char *package_name;
    uint32_t entry_num;
    stuff_entry_t *entries;
};

struct stuff_group_t {
    uint32_t package_count;
    stuff_package_t *packages;
};

stuff_package_t *open_stuff(const char *filename);
void close_stuff(stuff_package_t *s);
stuff_group_t *open_stuff_group(const char *path, loading_status_t *status);
stuff_entry_t *find_stuff_icon(stuff_package_t *s, const char *iconID);
stuff_entry_t *find_stuff_icon_group(stuff_group_t *g, const char *iconID);

extern stuff_package_t *__resui;
extern stuff_group_t *__stuff;

#endif // __CCP_STUFF_H_
