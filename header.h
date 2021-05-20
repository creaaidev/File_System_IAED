#ifndef _HEADER_
/* Includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Defines */
#define NAME 2
#define ORDER 3
#define HELP "help: Imprime todos os comandos disponiveis.\n"
#define QUIT "quit: Termina o programa.\n"
#define SET "set: Adiciona ou modifica o valor a armazenar.\n"
#define PRINT "print: Imprime todos os caminhos e valores.\n"
#define FIND "find: Imprime o valor armazenado.\n"
#define LIST "list: Lista todos os componentes imediatos de um sub-caminho.\n"
#define SEARCH "search: Procura o caminho dado um valor.\n"
#define DELETE "delete: Apaga um caminho e todos os subcaminhos.\n"
#define CMD_COUNT 8
#define MAX_INPUT_SIZE 66536

/* Typedefs and structs */
typedef struct Directory* dir3;
typedef struct STnode* link; 
typedef struct LinkedList* llnode;

struct LinkedList{
	dir3 dir;
	llnode next;
};
	
/* structs for AVL tree */

/* directory struct */
struct Directory {
	char* path;
	char* value;
	llnode first;
	llnode last;
	link children; /* avl of children */
};

struct STnode {
	dir3 dir; /* node's directory */
	link l, r;
	int height;
};

/* Prototypes */
void help();
link set(link, dir3, char*, char*);
char* readDir(char*);
char* malloc_char(char*);
link malloc_link();
dir3 malloc_dir(char*);
char* strdup(char*);
void insert_llist(dir3, dir3);
void print(dir3, char*);
void find(link, dir3, char*);
void list(link, char*, char*);
int search(dir3, char*, char*);

void traverse(link, char*);
void visit(dir3, char*);
link NEW(dir3, link, link);
link searchR(link, char*);
link insertR(link, dir3);
/*int STcount(link);*/
/* void deleteR(link*, Key); fazer isto depois*/
/*void STsort(link,void (*visit)(Item));*/
/*void STfree(link*);*/
#endif
