/*ist199281 Martim Rosa Monis 2oProjeto IAED */
#include "header.h"

char* readDir(char* token) {
	char* dir;
	token = strtok(NULL, "/\n");
	dir = malloc_char(token); /* strlen path maybe */
	return dir;
}

int main() {
	int i, terminate=0;
	char cmd_n[CMD_COUNT][10] = {{"help"},{"quit"},{"set"},{"print"},{"list"},
				       {"search"},{"delete"}};
	/*char command[6];*/
	char input[MAX_INPUT_SIZE];
	char* token;
	char* value;

	while (!terminate) {
		fgets(input, MAX_INPUT_SIZE, stdin);
		token = strtok(input," \n");
		value = strtok(input," \n");
		
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
				token = strtok(NULL, " \n");
				value = strtok(NULL," \n");
				value = strtok(NULL, " \n");
				printf("%s\n", token);
				/*set(root, token);*/
				break;
		}
	}
	return 0;
}
