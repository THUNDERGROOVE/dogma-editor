#include "parseargs.h"

bool has_flag(int argc, char** argv, char *arg) {
    for (uint32_t i = 0; i < argc; i++) {
        if (strcmp(argv[i], arg) == 0) {
            return true;
        }
    }
    return false;
}
