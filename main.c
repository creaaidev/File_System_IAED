/*ist199281 Martim Rosa Monis 2oProjeto IAED */
#include "header.h"

int main() {
	int i, terminate=0;
	char cmd_n[CMD_COUNT][10] = {{"help"},{"quit"},{"set"},{"print"},{"list"},
				       {"search"},{"delete"}};
	char input[MAX_INPUT_SIZE];
	char* dir;
	char* path;
	char* token;
	link root = NULL;

	while (!terminate) {
		fgets(input, MAX_INPUT_SIZE, stdin);
		token = strtok(input," \n");
		
		for (i=0; i<CMD_COUNT; i++) {
			if (!strcmp(token, cmd_n[i])) {
				break;
			}
		}
		switch (i) {
			case 0:
				help();
				break;
			case 2:
				token = strtok(NULL," \n");
				path = token;
				dir = (char*)malloc(sizeof(char)*strlen(path));

				token = strtok(NULL," \n");
				dir = strtok(path, "/\n");
				set(root, path, value);
				break;
		}
	}
	return 0;
}
