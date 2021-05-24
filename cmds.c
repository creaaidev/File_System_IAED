#include "header.h"   

/* Help: Prints all available commands */
void help() {
    int i;
    char cmd[CMD_COUNT][80] = {{HELP},{QUIT},{SET},{PRINT},{FIND},{LIST},
                       {SEARCH},{DELETE}};
    for (i=0; i<CMD_COUNT; i++) {
        printf("%s", cmd[i]);
    }
}

/* Print: Prints all existing paths and values */
void print(dir3 dir_parent, char* top) {
	llnode aux = NULL;
	char* new_top;
	for (aux=dir_parent->first; aux != NULL; aux=aux->next) {
		new_top = malloc_char(strlen(top)+strlen(aux->dir->path)+1);
		strcpy(new_top, top);
		strcat(new_top, "/");
		strcat(new_top, aux->dir->path);
		if (aux->dir->value != NULL)
			printf("%s %s\n", new_top, aux->dir->value);
		print(aux->dir, new_top);
		free(new_top);
	}
}

/* Find: Prints the value of a given path */
void find(link child, dir3 parent, char* token) {
	link node = NULL;
	if (token == NULL) {
		if (parent->value != NULL) /* Path has a value so print it */
			printf("%s\n", parent->value);
		else 					   /* If the path doesn't have a value */
			printf("no data\n");
	} else {
		node = searchR(child, token);
		if (node != NULL) {
			find(node->dir->children, node->dir, readDir(token));
		} else { /* If the path wasn't found/doesn't exist */
			printf("not found\n");
		}
	}
	return;
}

/* Set: Adds or modifies a path(and it's value) */
link set(link child, dir3 parent, char* path, char* valor) {
	char* aux;
	dir3 new_dir = NULL;
	link node = child;
	
	if (path != NULL) {
		if (searchR(child, path) == NULL) {/*If the current dir doesn't exist*/
			new_dir = malloc_dir(path, parent); /*Make the directory*/
			insert_llist(parent, new_dir);/*Insert it on parent's linked list*/
			node = insertR(child, new_dir); /*Insert it on parent's AVL tree*/
			
			if (child == NULL)
				child = node;
			new_dir->children = set(new_dir->children, new_dir, readDir(path),
																		valor);
			return node;
		} else { /*If the current dir exists*/
			node = searchR(child, path);
			node->dir->children = set(node->dir->children, node->dir, 
														readDir(path), valor);
			return child;
		}
	} else {
		if (parent->value != NULL) {/*If there was an allocated value,free it*/
			aux = parent->value;
			free(aux);
		}
		parent->value = strdup(valor); /*Allocate the new value*/
		return parent->children;
	}
}

/* List: Prints all the direct children of a path */
void list(link child, char* path) {
	link node = NULL;
	if (path != NULL) {
		node = searchR(child, path);
		if (node == NULL) { /*The given path doesn't exist, wasn't found*/
			printf("not found\n");
			return;
		}
		list(node->dir->children, readDir(path));
	} else { /* Reached the given path(children) */
		traverse(child); /* Traverse the children of the given path */
	}
}

/* Search: Searches a path/directory from a given value */
int search(dir3 dir_master, char* top, char* valor) {
	llnode aux = NULL;
	char* new_top;
	int ret_val;
	for (aux=dir_master->first; aux != NULL; aux=aux->next) {
		new_top = malloc_char(strlen(top)+strlen(aux->dir->path)+1);
		strcpy(new_top, top);
		strcat(new_top, "/");
		strcat(new_top, aux->dir->path);
		if (aux->dir->value != NULL && !strcmp(aux->dir->value, valor)) {
			printf("%s\n", new_top);
			free(new_top);
			return 1; /* Directory was found, set return value to 1 to stop */
		}
		ret_val = search(aux->dir, new_top, valor);
		free(new_top);
		if (ret_val == 1) /* If return value was 1, quit */
			return 1;
	}
	return 0; /* No directory was found with the given value */
}

/* Delete function, different name to avoid confusion with deleteR(AVL)
   search_return: Deletes a directory and all of it's sub-directories */
void search_return(link child, dir3 p, char* token) {
	link aux = NULL;
	if (token != NULL) {
		if (searchR(child, token) == NULL) {
			printf("not found\n");
			return;
		} else {
			aux = searchR(child, token);
			search_return(aux->dir->children, aux->dir, readDir(token));
		}
	} else {
		terminator(child);
		if (p->parent != NULL)
			p->parent->children = deleteR(p->parent->children, p->path);
		else {
			clear_dir(p);
		}
	}
}

/* Auxiliary Function to delete a directory */
void clear_dir(dir3 dir) {
	llnode aux = dir->first;
	llnode bye = NULL;
	
	free(dir->path);    /* clear the path and value strings */
	if (dir->value != NULL)
		free(dir->value);
	
	while (aux != NULL) { /* clear the linked list */
		bye = aux;
		aux = aux->next;
		free(bye);
	}
	free(dir);			/* free the directory struct */
}

/* Auxiliary function to delete all the children of a directory */
void terminator(link node) {
	if (node == NULL) {
		return;
	}
	terminator(node->l);
	terminator(node->r);
	terminator(node->dir->children);
	clear_dir(node->dir);
	free(node);
}
