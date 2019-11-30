#!/usr/bin/env python3


from codegen.cache_types import write_header
from codegen.cache_types import tables

f = open("src/cache_save.cpp", "w")
write_header(f)

f.write('#include "cache_types.h"\n\n')
f.write('#include <string.h>\n\n')
f.write('#include "bulkdata.h"\n\n')
f.write('#include <list>\n\n')
f.write('#include "imgui.h"\n\n')

f.write('#include <string>\n')

############### WORKING ON BELOW ##################
for k, v in tables.iteritems():
    if v[0][1] != "INTEGER":
        print " >>>> WARN TABLE " + k + " IS NON INDEXABLE"
        continue
    f.write("void " + k + "_save(" + k + " *data, bulkdata *b) {\n");
    f.write("    char *err_msg = NULL;\n")
    f.write("    sqlite3_stmt *res;\n")
    f.write('    std::string sql("update ' + k + ' SET ");\n')
    i = 0
    for x in v[:-1]:
        name = x[0]
        _type = x[1];
        f.write('    sql.append("' + name + ' = ");\n')
        if _type == "INTEGER":
            f.write("sql.append(std::to_string(data->" + name + "));\n")
        elif _type == "REAL":
            f.write("sql.append(std::to_string(data->" + name + "));\n")
        elif _type == "TEXT":
            f.write('sql.append("\'");\n')
            f.write("sql.append(data->" + name + ");\n")
            f.write('sql.append("\'");\n')
        f.write('sql.append(", ");\n')
    beef = v[-1]
    name = beef[0]
    _type = beef[1];
    f.write('    sql.append("' + name + ' = ");\n')
    if _type == "INTEGER":
        f.write("sql.append(std::to_string(data->" + name + "));\n")
    elif _type == "REAL":
        f.write("sql.append(std::to_string(data->" + name + "));\n")
    elif _type == "TEXT":
        f.write("sql.append(data->" + name + ");\n")

    f.write('   sql.append(" WHERE ' + v[0][0] + ' = ");\n')
    f.write('   sql.append(std::to_string(data->' + v[0][0] + '));\n')
    f.write('   sql.append(";");\n')
    f.write('   printf("%s\\n\\n", sql.c_str());\n')
    f.write('   printf("db handle %p\\n", b->db);\n')
    f.write("   uint32_t rc = sqlite3_exec(b->db, sql.c_str(), NULL, NULL, &err_msg);\n")
    f.write("   if (rc != SQLITE_OK) {\n")
    f.write('       printf("err: %s\\n", err_msg);\n')
    f.write("   }\n")
    f.write('   printf("err: %s %d\\n", err_msg, rc);\n')

    f.write("   data->dirty = false;\n")

    f.write("}\n")

f.write("void save_all_dirty(cache_collection *cc, bulkdata *b) {\n")
for k, v in tables.iteritems():
    if v[0][1] != "INTEGER":
        print " >>>> WARN TABLE " + k + " IS NON INDEXABLE"
        continue
    f.write("    " + k + "_save_dirty(cc, b);\n")
f.write("}\n\n")

for k, v in tables.iteritems():
    if v[0][1] != "INTEGER":
        print " >>>> WARN TABLE " + k + " IS NON INDEXABLE"
        continue
    f.write("void " + k + "_save_dirty(cache_collection *cc, bulkdata *b) {\n");
    f.write("    auto data = cc->cache_" + k + ";\n");
    f.write("    for (uint32_t i = 0; i < data.size(); i++) {")
    f.write("        if (data[i].dirty) {")
    f.write("            auto di = &data[i];\n")
    f.write('            printf("Saving dirty record %p\\n", di);\n')
    f.write("            " + k + "_save(di, b);\n")
    f.write("            cc->cache_" + k + "[i].dirty = false;\n")
    f.write("        }\n")
    f.write("    }\n")
    f.write("}\n")
