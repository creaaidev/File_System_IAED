/*ist199281 Martim Rosa Monis 2oProjeto IAED */
#include "header.h"

int main() {
	int i, terminate=0;
	char cmd_n[CMD_COUNT][10] = {{"help"},{"quit"},{"set"},{"print"},{"find"},{"list"},
				       {"search"},{"delete"}};
	char command[MAX_INPUT_SIZE];
	char path[MAX_INPUT_SIZE];
	char value[MAX_INPUT_SIZE];
	char* token;
	static link root;
	root = NEW(malloc_dir(""), NULL, NULL);

	while (!terminate) {
		scanf("%s",command);
		
		for (i=0; i<CMD_COUNT; i++) {
			if (!strcmp(command, cmd_n[i])) {
				break;
			}
		}
		/* REMOVE BEFORE SHIPMENT */
		if (!strcmp(command, "debug")) {
				i = -1;
		}
		switch (i) {
			case 0:
				help();
				break;
			case 2:
				scanf(" %s %[^\n]", path, value);
				token = strtok(path,"/\n");
				set(root->children, root, token, value);
				break;
			case 3:
				print(root->dir);
				break;
			case 4:
				scanf(" %s", path);
				token = strtok(path, "/\n");
				find(root->children, token);
				break;
			case -1:
				debug(root->dir, root->children);
				break;
		}
	}
	return 0;
}
