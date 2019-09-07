#include "bulkdata.h"

#include "cache_types.h"

#include <string.h>

#include <stdio.h>
#include "sqlite3.h"

#include <vector>


uint32_t bulkdata_init(bulkdata *b) {
    int ret = sqlite3_open("bulkdata.db", &b->db);

    if (ret != SQLITE_OK) {
        return -1;
    }
    return 0;
}


std::vector<cacheInvTypes> search_invtype(bulkdata *b, const char *tn) {
    char *stmt = "SELECT  from cacheInvTypes where typeName like %@tn%";
    sqlite3_stmt *res;
    int rc = sqlite3_prepare_v2(b->db, stmt, -1, &res, 0);
    if (rc == SQLITE_OK) {
        int idx = sqlite3_bind_parameter_index(res, "@id");
        sqlite3_bind_text(res, idx, tn, strlen(tn), NULL);
    } else {
        fprintf(stderr, "Failed to execute statement: %s", sqlite3_errmsg(b->db));
    }

    int step = sqlite3_step(res);

    if (step == SQLITE_ROW) {

    
    }
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
