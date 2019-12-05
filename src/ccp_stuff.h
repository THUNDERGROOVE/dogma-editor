#ifndef __CCP_STUFF_H_
#define __CCP_STUFF_H_

#include <stdint.h>

// oh nice don't even have to pack this shit
struct stuff_entry_t {
    uint32_t data_length;
    uint32_t filename_length;
    char *filename;
    char *data;
};

struct stuff_package_t {
    uint32_t entry_num;
    stuff_entry_t *entries;
};

stuff_package_t *open_stuff(const char *filename);
void close_stuff(stuff_package_t *s);
stuff_entry_t *find_stuff_icon(stuff_package_t *s, const char *iconID);

extern stuff_package_t *__resui;

#endif // __CCP_STUFF_H_
