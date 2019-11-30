#include "bulkdata.h"

#include "cache_types.h"

#include <string.h>

#include <stdio.h>
#include "sqlite3.h"

uint32_t bulkdata_init(bulkdata *b) {
    int ret = sqlite3_open("bulkdata.db", &b->db);

    if (ret != SQLITE_OK) {
        return -1;
    }
    return 0;
}

uint32_t bulkdata_shutdown(bulkdata *b) {
    sqlite3_close(b->db);
    b->db = NULL;
    return 0;
}


std::vector<uint32_t > collect_typeids(bulkdata *b) {
    std::vector<uint32_t> out;
    const char *stmt = "SELECT typeID from cacheInvTypes";

    sqlite3_stmt *res;
    int rc = sqlite3_prepare_v2(b->db, stmt, -1, &res, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(b->db));
    }

    int step = sqlite3_step(res);
    while (step != SQLITE_DONE && step != SQLITE_OK) {
        if (step == SQLITE_ROW) {
            uint32_t typeID = sqlite3_column_int(res, 0);
            printf("Got typeid: %d\n", typeID);
            out.push_back(typeID);
        }
        step = sqlite3_step(res);
    }

    return out;
}


std::vector<cacheInvTypes> search_invtype(bulkdata *b, const char *tn) {
    std::vector<cacheInvTypes> out;
    const char *stmt = "SELECT typeID from cacheInvTypes where typeName like '%adaptive%'";
    sqlite3_stmt *res;
    int rc = sqlite3_prepare_v2(b->db, stmt, -1, &res, 0);
    if (rc == SQLITE_OK) {
        //int idx = sqlite3_bind_parameter_index(res, "@tn");
        //sqlite3_bind_text(res, 0, tn, strlen(tn), NULL);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(b->db));
    }


    int step = sqlite3_step(res);
    while (step != SQLITE_DONE && step != SQLITE_OK) {
        if (step == SQLITE_ROW) {
            uint32_t typeID = sqlite3_column_int(res, 0);
            cacheInvTypes c = cacheInvTypes_load_by(b, typeID);
            out.push_back(c);
        }
        step = sqlite3_step(res);
    }
    printf("%d\n", out.size());
    return out;
}
/*
  cacheInvType tmp_load_invtype(bulkdata *b, uint32_t typeID) {
  char *err_msg = NULL;

  cacheInvType t;
  memset(&t, 0, sizeof(t));
  char *stmt = "SELECT * from cacheInvTypes where typeID = @id";

  sqlite3_stmt *res;

  int rc = sqlite3_prepare_v2(b->db, stmt, -1, &res, 0);

  if (rc == SQLITE_OK) {
  int idx = sqlite3_bind_parameter_index(res, "@id");
  sqlite3_bind_int(res, idx, typeID);
  } else {
  fprintf(stderr, "Failed to execute statement: %s", sqlite3_errmsg(b->db));
  }

  int step = sqlite3_step(res);

  if (step == SQLITE_ROW) {
  t.typeID = sqlite3_column_int(res, 0);
  t.groupID = sqlite3_column_int(res, 1);

  t.typeName = strdup(sqlite3_column_text(res, 2));
  t.description = strdup(sqlite3_column_text(res, 3));

  t.graphicID = sqlite3_column_int(res, 4);
  t.radius = sqlite3_column_double(res, 5);
  t.mass = sqlite3_column_double(res, 6);
  t.volume = sqlite3_column_double(res, 7);
  t.capacity = sqlite3_column_double(res, 8);
  t.portionSize = sqlite3_column_int(res, 9);
  t.raceID = sqlite3_column_int(res, 10);
  t.basePrice = sqlite3_column_double(res, 11);
  t.published = sqlite3_column_int(res, 12);
  t.marketGroupID = sqlite3_column_int(res, 13);
  t.chanceOfDuplicating = sqlite3_column_double(res, 14);
  t.soundID = sqlite3_column_double(res, 15);
  t.iconID = sqlite3_column_int(res, 16);
  t.dataID = sqlite3_column_int(res, 17);
  t.typeNameID = sqlite3_column_int(res, 18);
  t.descriptionID = sqlite3_column_int(res, 19);
  t.copyTypeID = sqlite3_column_int(res, 20);
  }

  sqlite3_finalize(res);

  return t;
  }
*/
