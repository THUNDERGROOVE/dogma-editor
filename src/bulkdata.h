#ifndef __BULKDATA_H__
#define __BULKDATA_H__

#include <stdint.h>

#include "sqlite3.h"

#include "cache_types.h"

struct bulkdata {
    sqlite3 *db;
};

uint32_t bulkdata_init(bulkdata *b);


#endif
