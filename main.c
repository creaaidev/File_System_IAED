/*ist199281 Martim Rosa Monis 2oProjeto IAED */
#include "header.h"

int main() {
	int i, terminate=0;
	char cmd_n[CMD_COUNT][10] = {{"help"},{"quit"},{"set"},{"print"},{"list"},
				       {"search"},{"delete"}};
	char command[100];
	while (!terminate) {
		scanf("%s", command);
		for (i=0; i<CMD_COUNT; i++) {
			if (!strcmp(command, cmd_n[i])) {
				break;
			}
		}
		switch (i) {
			case 0:
				help();
		}
	}
	return 0;
}
