#include "header.h"                   

void help() {
    int i;
    char cmd_n[CMD_COUNT][10] = {{"help"},{"quit"},{"set"},{"print"},{"list"},
                       {"search"},{"delete"}};
    char cmd_d[CMD_COUNT][60] = {{HELP},{QUIT},{SET},{PRINT},{LIST},
                       {SEARCH},{DELETE}};
    for (i=0; i<CMD_COUNT; i++) {
        printf("%s: %s\n", cmd_n[i], cmd_d[i]);
    }
}
