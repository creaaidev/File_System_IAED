/*ist199281 Martim Rosa Monis 2oProjeto IAED */
#include "header.h"

dir3 terminate(int signal) {
	static dir3 root;
	if (signal == 0)
		root = malloc_dir("", NULL);
	else if (signal == 1)
		search_return(root->children, root, NULL);
	return root;
}

int main() {
	int i, quit_signal=0;
	char cmd_n[CMD_COUNT][10] = {{"help"},{"quit"},{"set"},{"print"},{"find"},{"list"},
				       {"search"},{"delete"}};
	char command[MAX_INPUT_SIZE];
	char path[MAX_INPUT_SIZE];
	char value[MAX_INPUT_SIZE];
	char* token;
	dir3 root = terminate(0);

	while (!quit_signal) {
		scanf("%s",command);
		
		for (i=0; i<CMD_COUNT; i++) {
			if (!strcmp(command, cmd_n[i])) {
				break;
			}
		}
		switch (i) {
			case 0: /* Help command */
				help();
				break;
			case 1: /* Quit command */
				quit_signal = 1;
				search_return(root->children, root, NULL);
				break;
			case 2: /* Set command */
				scanf(" %s %[^\n]", path, value);
				token = strtok(path,"/");
				root->children = set(root->children, root, token, value);
				break;
			case 3: /* Print command */
				print(root, root->path);
				break;
			case 4: /* Find command */
				scanf(" %s", path);
				token = strtok(path, "/");
				find(root->children, root, token);
				break;
			case 5: /* List command */
				if (getchar()!='\n') {
					scanf("%s", path);
					token = strtok(path, "/");
					list(root->children, token);
				} else { /* No given path */
					list(root->children, NULL);
				}
				break;
			case 6: /* Search command */
				scanf(" %[^\n]", value);
				if (search(root, root->path, value) == 0)
					printf("not found\n");
				break;
			case 7: /* Delete command */
				if (getchar()!='\n') { /* If path was given */
					scanf("%s", path);
					token = strtok(path, "/");
					search_return(root->children, root, token);
				} else { /* No given path */
					search_return(root->children, root, NULL);
					root = malloc_dir("", NULL);
				}
		}
	}
	return 0;
}
