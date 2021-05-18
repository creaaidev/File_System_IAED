#ifndef _HEADER_
/* Includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Defines */
#define NAME 2
#define ORDER 3
#define HELP "help: Imprime todos os comandos disponiveis."
#define QUIT "quit: Termina o programa."
#define SET "set: Adiciona ou modifica o valor a armazenar."
#define PRINT "print: Imprime todos os caminhos e valores."
#define FIND "find: Imprime o valor armazenado."
#define LIST "list: Lista todos os componentes imediatos de um sub-caminho."
#define SEARCH "search: Procura o caminho dado um valor."
#define DELETE "delete: Apaga um caminho e todos os subcaminhos."
#define CMD_COUNT 8
#define MAX_INPUT_SIZE 66536

/* Typedefs and structs */
typedef struct {
	Directory* curr;
	LinkedList* next;
} LLnode;

	/* structs for AVL tree */
typedef struct STnode* link; 

/* directory struct */
typedef struct {
	char* path;
	char* value;
	LLnode* first;
	LLnode* last;
} Directory;

struct STnode {
	Directory* dir; /* node's directory */
	link children; /* avl of children */
	link l, r;
	int height;
};

/* Prototypes */
void help();
void set(link, char*, char*);
char* readDir(char*);
char* malloc_char(char*);
link malloc_link();
Directory* malloc_dir();
char* strdup(char*);

void initR(link*);
link searchR(link, char*);
link insertR(link, Directory*);
/*int STcount(link);*/
/* void deleteR(link*, Key); fazer isto depois*/
/*void STsort(link,void (*visit)(Item));*/
/*void STfree(link*);*/
#endif
