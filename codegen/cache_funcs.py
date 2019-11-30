#!/usr/bin/env python2

from codegen.cache_types import write_header
from codegen.cache_types import tables

f = open("src/cache_funcs.cpp", "w")

write_header(f)

f.write('#include "cache_types.h"\n\n')
f.write('#include <string.h>\n\n')
f.write('#include "bulkdata.h"\n\n')
f.write('#include <list>\n\n')
f.write('#include "imgui.h"\n\n')

f.write("search_windows sw;\n\n")


for k, v in tables.iteritems():
    if v[0][1] != "INTEGER":
        print " >>>> WARN TABLE " + k + " IS NON INDEXABLE"
        continue
    f.write(k + " " + k + "_load_by(bulkdata *b, uint32_t " + v[0][0] + ") {\n")

    f.write("    char *err_msg = NULL;\n")
    f.write("    sqlite3_stmt *res;\n")


    f.write("    " + k + " t;\n")
    f.write("    memset(&t, 0, sizeof(t));\n")

    f.write('    char *stmt = (char *)"SELECT * from ' + k + ' where typeID = @id";\n');

    f.write("    int rc = sqlite3_prepare_v2(b->db, stmt, -1, &res, 0);\n");

    f.write("    if (rc == SQLITE_OK) {\n")
    f.write('        int idx = sqlite3_bind_parameter_index(res, "@id");\n')
    f.write('        sqlite3_bind_int(res, idx, ' + v[0][0] + ');\n')
    f.write("    } else {\n")
    f.write('        fprintf(stderr, "Failed to execute statement: %s", sqlite3_errmsg(b->db));\n')
    f.write("    }\n\n")
    f.write("    int step = sqlite3_step(res);\n")

    f.write("    if (step == SQLITE_ROW) {\n")

    i = 0
    for x in v:
        name = x[0]
        _type = x[1]
        if _type == "INTEGER":
            f.write("        t." + name + " = sqlite3_column_int(res, " + str(i) + ");\n")
        elif _type == "REAL":
            f.write("        t." + name + " = sqlite3_column_double(res, " + str(i) + ");\n")
        elif _type == "TEXT":
            f.write("        char *_v" + str(i) +" = (char *)sqlite3_column_text(res, " + str(i) + ");\n")
            f.write("        if (_v" + str(i) + " != NULL) {\n")
            f.write("            t." + name + " = strdup(_v" + str(i) + ");\n")
            f.write("        }\n")
        i = i + 1
    f.write("    }\n\n");
    f.write("    sqlite3_finalize(res);\n")
    f.write("    return t;\n")
    f.write("}\n\n")

print "Generating loadalls"

for k, v in tables.iteritems():
    if v[0][1] != "INTEGER":
        print " >>>> WARN TABLE " + k + " IS NON INDEXABLE"
        continue
    f.write("std::vector<" + k + "> " + k + "_load_all(bulkdata *b) {\n")
    f.write('    printf("Loading ' + k + '\\n");\n')

    f.write("    std::vector<" + k + "> out;\n")


    f.write("    sqlite3_stmt *res;\n")


    f.write("    " + k + " t;\n")
    f.write("    memset(&t, 0, sizeof(t));\n")

    f.write('    char *stmt = (char *)"SELECT * from ' + k + '";\n');

    f.write("    int rc = sqlite3_prepare_v2(b->db, stmt, -1, &res, 0);\n");

    f.write("    if (rc != SQLITE_OK) {\n")
    f.write('        fprintf(stderr, "Failed to execute statement: %s", sqlite3_errmsg(b->db));\n')
    f.write("    }\n\n")
    f.write("    int step = sqlite3_step(res);\n")

    f.write("    while(step != SQLITE_DONE && step != SQLITE_OK) {\n")
    f.write("        memset(&t, 0, sizeof(t));\n")
    f.write("        t.dirty = false;\n")
    f.write("        if (step == SQLITE_ROW) {\n")
    i = 0
    for x in v:
        name = x[0]
        _type = x[1]
        if _type == "INTEGER":
            f.write("        t." + name + " = sqlite3_column_int(res, " + str(i) + ");\n")
        elif _type == "REAL":
            f.write("        t." + name + " = sqlite3_column_double(res, " + str(i) + ");\n")
        elif _type == "TEXT":
            f.write("        int32_t _t" + str(i) +" = sqlite3_column_type(res, " + str(i) + ");\n")
            f.write("        char *_v" + str(i) +" = (char *)sqlite3_column_text(res, " + str(i) + ");\n")
            f.write("        if (_v" + str(i) + " != NULL) {\n")
            f.write("            t." + name + " = strdup(_v" + str(i) + ");\n")
            f.write("        } else { \n")
            f.write("            t." + name + " = NULL;\n")
            f.write("        }\n")
            f.write("        if (_t" + str(i) + " == SQLITE_NULL) {\n")
            f.write("            t." + name + " = NULL;\n")
            f.write("        }\n")

        i = i + 1
    f.write("        out.push_back(t);\n")
    f.write("        }\n")

    f.write("    step = sqlite3_step(res);\n")
    f.write("    }\n\n")

    f.write("    sqlite3_finalize(res);\n")
    f.write("    return out;\n")
    f.write("    }\n\n");

print "Generating cache_load_all"


f.write('#include <unistd.h>\n')

f.write("cache_collection cache_load_all(bulkdata *b, loading_status_t *t) {\n")
f.write("    cache_collection out;\n")
f.write("    t->done = false;\n")

for k, v in tables.iteritems():
    if v[0][1] != "INTEGER":
        print " >>>> WARN TABLE " + k + " IS NON INDEXABLE"
        continue
    f.write('    t->label = "Loading ' + k + '";\n')
    f.write("    out.cache_" + k + " = " + k + "_load_all(b);\n")
    #f.write("    sleep(1);")


f.write("    t->done = true;")
f.write("    return out;\n")
f.write("};\n\n")

f.write("uint32_t cache_count_dirty(cache_collection cc) {;\n")
f.write("    uint32_t c = 0;\n")
for k, v in tables.iteritems():
    if v[0][1] != "INTEGER":
        print " >>>> WARN TABLE " + k + " IS NON INDEXABLE"
        continue
    #f.write("    cc.cache_" + k)
    f.write("    for (uint32_t i = 0; i < cc.cache_" + k + ".size(); i++) {\n")
    f.write("        if (cc.cache_" + k + "[i].dirty) c += 1;\n")
    f.write("    }\n")
f.write("    return c;\n")
f.write("};\n\n")
