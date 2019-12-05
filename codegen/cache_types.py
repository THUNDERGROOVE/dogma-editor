#!/usr/bin/env python2

import sqlite3

def write_header(_f):
    _f.write("/* Generated by codegen.py\n")
    _f.write(" * DO NOT EDIT\n")
    _f.write(" */\n\n\n")

db = sqlite3.connect("bulkdata.db")

f = open("src/cache_types.h", "w")

write_header(f)

f.write("#ifndef __CACHE_TYPES__H__\n")
f.write("#define __CACHE_TYPES__H__\n\n")

f.write('#include <stdio.h>\n\n')
f.write('#include <stdlib.h>\n\n')
f.write('#include <vector>\n\n')
f.write('#include "bulkdata.h"\n\n')
f.write('#include <list>\n\n')

f.write("struct bulkdata;\n")
f.write("struct edit_window;\n")

f.write("struct loading_status_t {\n    char *label;\n    bool done;\n};\n")


cursor = db.cursor()
cursor.execute("SELECT * from sqlite_master WHERE type='table';")
tables = {}


for x in cursor.fetchall():
    schema = x[-1]
    schema = schema.split("(")[1]
    schema = schema.split(")")[0]
    schema = schema.split(",")
    schema = [c.strip(' ') for c in schema]
    n = []
    for b in schema:
       n.append((
           b.split(" ")[0],
           b.split(" ")[1]))
    schema = n
    tables[x[1]] = schema

for k, v in tables.iteritems():
    f.write("struct " + k + " {\n")

    for x in v:
        if x[1] == "INTEGER":
            f.write("    uint32_t ")
        if x[1] == "REAL":
            f.write("    float ")
        if x[1] == "TEXT":
            f.write("    char *")

        f.write(x[0]+ ";\n")

    f.write("\n    bool dirty;\n")

    f.write("};\n\n")


# f.write("enum cache_tag {\n")
# for k, v in tables.iteritems():
#     if v[0][1] != "INTEGER":
#         print " >>>> WARN TABLE " + k + " IS NON INDEXABLE"
#         continue
#     f.write("    tag_" + k + ",\n")
# f.write("};\n\n")

for k, v in tables.iteritems():
    if v[0][1] != "INTEGER":
        print " >>>> WARN TABLE " + k + " IS NON INDEXABLE"
        continue
    f.write(k + " " + k + "_load_by(bulkdata *b, uint32_t " + v[0][0] + ");\n")

for k, v in tables.iteritems():
    if v[0][1] != "INTEGER":
        print " >>>> WARN TABLE " + k + " IS NON INDEXABLE"
        continue
    f.write("std::vector<" + k + "> " + k + "_load_all(bulkdata *b);\n")

f.write("\n")
print "Generating cache struct"

f.write("struct cache_collection {\n")
for k, v in tables.iteritems():
    if v[0][1] != "INTEGER":
        print " >>>> WARN TABLE " + k + " IS NON INDEXABLE"
        continue
    f.write("    std::vector<" + k + "> cache_" + k + ";\n")

f.write("};\n\n")

f.write("cache_collection cache_load_all(bulkdata *b, loading_status_t *t);\n")
f.write("uint32_t cache_count_dirty(cache_collection cc);\n")

for k, v in tables.iteritems():
    if v[0][1] != "INTEGER":
        print " >>>> WARN TABLE " + k + " IS NON INDEXABLE"
        continue
    f.write("void " + k + "_draw_edit(std::list<edit_window *> *w, edit_window *e, cache_collection *cc);\n")

f.write("\n\n")

f.write("struct search_windows {\n")
for k, v in tables.iteritems():
    if v[0][1] != "INTEGER":
        print " >>>> WARN TABLE " + k + " IS NON INDEXABLE"
        continue
    f.write("bool show_" + k + "_search;\n")

f.write("};\n\n")

f.write("extern search_windows sw;\n\n")

f.write("void draw_main_window();\n\n")

f.write("void draw_search_windows(cache_collection *cc, std::list<edit_window *> *window_list);\n")

print "Generating individual draw search windows"
for k, v in tables.iteritems():
    if v[0][1] != "INTEGER":
        print " >>>> WARN TABLE " + k + " IS NON INDEXABLE"
        continue
    f.write("void draw_search_window_" + k + "(cache_collection *cc, std::list<edit_window *> *window_list);\n")


f.write("void window_list_draw(std::list<edit_window *> *window_list, cache_collection *cc);\n")

f.write("void save_all_dirty(cache_collection *cc, bulkdata *b);\n")

for k, v in tables.iteritems():
    if v[0][1] != "INTEGER":
        print " >>>> WARN TABLE " + k + " IS NON INDEXABLE"
        continue
    f.write("void "+ k + "_save_dirty(cache_collection *cc, bulkdata *b);\n");

for k, v in tables.iteritems():
    if v[0][1] != "INTEGER":
        print " >>>> WARN TABLE " + k + " IS NON INDEXABLE"
        continue
    f.write(k + "* cache_get_" + k + "_by_" + v[0][0] + "(cache_collection *cc, uint32_t ID);\n")

f.write("#endif\n")

f.close()

########################### END HEADER ###########################################
