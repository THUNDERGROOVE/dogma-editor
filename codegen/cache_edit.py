#!/usr/bin/env python3

from codegen.cache_types import write_header
from codegen.cache_types import tables

f = open("src/cache_edit.cpp", "w")

write_header(f)

f.write('#include "cache_types.h"\n\n')
f.write('#include <string.h>\n\n')
f.write('#include "bulkdata.h"\n\n')
f.write('#include <list>\n\n')
f.write('#include "imgui.h"\n\n')
f.write('#include "dogma-operand.h"\n\n')

print "Generating ImGui edit windows"

for k, v in tables.iteritems():
    if v[0][1] != "INTEGER":
        print " >>>> WARN TABLE " + k + " IS NON INDEXABLE"
        continue
    f.write("void " + k + "_draw_edit(std::list<edit_window *> *window_list, edit_window *e, cache_collection *cc) {\n")
    f.write("    " + k + "*d = (" + k + "*)e->data;\n\n")

    f.write("    char title_buf[1024];\n")
    f.write('    snprintf(title_buf, 1024, "Editing object: %p", d);\n')
    f.write("    ImGui::Begin(title_buf, &e->show);\n")

    for x in v:
        name = x[0]
        _type = x[1]
        if _type == "INTEGER":
            f.write('    ImGui::InputInt("' + name + '", (int *)&d->' + name + ');\n')
            if name == "operandID":
                f.write('    ImGui::Text("%s", operand_id_strings[d->operandID]);\n')
            if "TypeID" in name or "typeID" in name:
                f.write('    ImGui::SameLine();\n')
                f.write('    ImGui::PushID(1000000 + d->' + name + ');\n')
                f.write('    if (ImGui::Button("Edit/Lookup")) {\n')
                f.write('        cacheInvTypes *tt = cache_get_cacheInvTypes_by_typeID(cc, d->' + name + ');\n')
                f.write('        edit_window *w = (edit_window *)calloc(1, sizeof(edit_window));\n')
                f.write('        w->data = tt;\n')
                f.write('        w->typeID = tt->typeID;\n')
                f.write('        w->show = true;\n')
                f.write('        w->tag = tag_cacheInvTypes;\n')
                f.write('        window_list->push_back(w);\n')
                f.write('    }\n')
                f.write('    ImGui::PopID();\n')
        elif _type == "REAL":
            f.write('    ImGui::InputFloat("' + name + '", &d->' + name + ');\n')
        elif _type == "TEXT":
            f.write('    ImGui::Text("' + name + ':");\n')
            f.write('    ImGui::Text("%s", d->' + name + ');\n')
        f.write('    ImGui::Separator();\n')

    f.write('    ImGui::Checkbox("dirty", &d->dirty);\n')

    f.write('    if (ImGui::Button("Mark Dirty")) {\n');
    f.write('        d->dirty = true;\n')
    f.write("    }\n\n")



    f.write('    ImGui::End();\n')
    f.write("}\n\n")

print "Generate main window"


#f.write("bool show_" + k + "_search;\n")
f.write("void draw_main_window() {\n")
f.write('    bool tmp = true;')
for k, v in tables.iteritems():
    if v[0][1] != "INTEGER":
        print " >>>> WARN TABLE " + k + " IS NON INDEXABLE"
        continue
    f.write('    ImGui::Begin("Bulkdata recordsets", &tmp);\n')
    f.write('    if(ImGui::Button("Edit ' + k + '")) {')
    f.write("        sw.show_" + k + "_search = !sw.show_" + k + "_search;\n\n")
    f.write("    }\n\n")
    f.write('    ImGui::End();\n')


f.write("}\n\n")
