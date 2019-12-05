#!/usr/bin/

from codegen.cache_types import write_header
from codegen.cache_types import tables

f = open("src/cache_search.cpp", "w")
write_header(f)

f.write('#include "cache_types.h"\n\n')
f.write('#include <string.h>\n\n')
f.write('#include "bulkdata.h"\n\n')
f.write('#include <list>\n\n')
f.write('#include "window.h"\n')
f.write('#include "imgui.h"\n\n')


print "Generating individual draw search windows"
for k, v in tables.iteritems():
    if v[0][1] != "INTEGER":
        print " >>>> WARN TABLE " + k + " IS NON INDEXABLE"
        continue

    text_name = None
    for x in v:
        name = x[0]
        _type = x[1]
        if _type == "TEXT":
            if "name" or "Name" in name:
                text_name = name
                break

    f.write("void draw_search_window_" + k + "(cache_collection *cc, std::list<edit_window *> *window_list) {\n")
    f.write('    static char buffer[1024];\n')
    #f.write('    memset(buffer, 0, 1024);\n')
    f.write('    std::vector<' + k + ' *> results;\n')
    f.write('    ImGui::Begin("Search: ' + k + '");\n')
    f.write('    ImGui::InputText("' + k + '", buffer, 1024);\n')
    f.write('    if (strcmp(buffer, "") != 0) {\n\n')

    f.write('    for (uint32_t i = 0; i < cc->cache_' + k + '.size(); i++) {\n')
    f.write('        ' + k + ' *t = &cc->cache_' + k + '[i];\n')
    can_search = False
    for x in v:
        name = x[0]
        _type = x[1]
        if _type == "TEXT":
            if "name" or "Name" in name:
                f.write('        if (t->' + name + ' != NULL) {\n')
                f.write('        if (strstr(t->' + name + ', buffer) != NULL) {\n')
                f.write('        results.push_back(t);\n')
                f.write('        }\n\n')
                f.write('        }\n\n')
                can_search = True

    f.write("    }\n\n")

    if can_search:
        f.write('    ImGui::Text("Results: %d", results.size());\n')
    else:
        f.write('    for (uint32_t i = 0; i < cc->cache_' + k +'.size(); i++) {\n')
        f.write('        results.push_back(&cc->cache_' + k + '[i]);\n')
        f.write('    }\n')
        f.write('    ImGui::Text("This recordset is not searchable");\n')

    f.write("    ImGui::Separator();\n\n")

    f.write('    for (uint32_t i = 0; i < results.size(); i++) {\n')
    f.write('        ' + k + ' *t = results[i];')
    print k + " key type: " + v[0][1]
    if v[0][1] == "INTEGER" and text_name != None:
        f.write('    ImGui::PushID(i);\n')
        f.write('    if (ImGui::Button("Edit")) {\n')
        f.write('        printf("Opening window\\n");\n')
        f.write('        edit_window *w = (edit_window *)calloc(1, sizeof(edit_window));\n')
        f.write('        w->data = t;\n')
        f.write('        w->typeID = t->' + v[0][0] + ";\n")
        f.write('        w->show = true;\n')
        f.write('        w->tag = tag_' + k + ';\n')
        f.write('        window_list_push(window_list, w);\n')
        f.write('    }\n\n')
        f.write('    ImGui::SameLine();\n')
        f.write('    ImGui::Text("[%d] %s", t->' + v[0][0] + ', t->' + text_name + ');\n')
        f.write('    ImGui::PopID();\n')
        f.write("    ImGui::Separator();\n\n")
    elif v[0][1] == "INTEGER":
        f.write('    ImGui::PushID(i);\n')
        f.write('    if (ImGui::Button("Edit")) {\n')
        f.write('        edit_window *w = (edit_window *)calloc(1, sizeof(edit_window));\n')
        f.write('        w->data = t;\n')
        f.write('        w->typeID = t->' + v[0][0] + ';\n')
        f.write('        w->show = true;\n')
        f.write('        w->tag = tag_' + k + ';\n')
        f.write('        window_list_push(window_list, w);\n')
        f.write('    }\n\n')
        f.write('    ImGui::SameLine();\n')
        f.write('    ImGui::Text("[%d] <no name>", t->' + v[0][0] + ');\n')
        f.write('    ImGui::PopID();\n')
    else:
        f.write('    ImGui::Text("Not Supported");\n')

    f.write('    }\n')
    f.write('    }\n')
    f.write('    ImGui::End();\n')


    f.write("}\n\n")

print "Generating draw_search_windows()"
f.write("void draw_search_windows(cache_collection *cc, std::list<edit_window *> *window_list) {\n")
for k, v in tables.iteritems():
    if v[0][1] != "INTEGER":
        print " >>>> WARN TABLE " + k + " IS NON INDEXABLE"
        continue
    f.write("    if (sw.show_" + k + "_search) {\n")
    f.write("        draw_search_window_" + k + "(cc, window_list);")
    f.write("    }\n\n")

f.write("}\n\n")

print "Generating window_list_draw()"
f.write("void window_list_draw(std::list<edit_window *> *window_list, cache_collection *cc) {\n")

f.write("for (auto it = window_list->begin(); it != window_list->end(); it++) {\n")
f.write("    edit_window *w = *it;\n")
f.write("    if (w->show == false) {\n")
f.write("        it = window_list->erase(it);\n")
f.write('        printf("Closing edit window\\n");')
f.write('        continue;')
f.write("    }\n\n")
f.write("    switch (w->tag) {")
for k, v in tables.iteritems():
    if v[0][1] != "INTEGER":
        print " >>>> WARN TABLE " + k + " IS NON INDEXABLE"
        continue
    f.write("    case tag_" + k + ": {\n")
    f.write("        " + k + "_draw_edit(window_list, w, cc);\n")
    f.write("    } break;")
f.write("    }\n\n")
f.write("}\n\n")

f.write("}\n\n")

f.close()
