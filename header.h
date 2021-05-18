#ifndef _HEADER_
/* Includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Defines */
#define NAME 2
#define ORDER 3
#define HELP "Imprime todos os comandos disponiveis."
#define QUIT "Termina o programa."
#define SET "Adiciona ou modifica o valor a armazenar."
#define PRINT "Imprime todos os caminhos e valores."
#define FIND "Imprime o valor armazenado."
#define LIST "Lista todos os componentes imediatos de um sub-caminho."
#define SEARCH "Procura o caminho dado um valor."
#define DELETE "Apaga um caminho e todos os subcaminhos."
#define CMD_COUNT 8
#define MAX_INPUT_SIZE 66536

/* Typedefs and structs */
	/* structs for AVL tree */
typedef struct STnode* link; 
	
/* directory struct */
typedef struct {
	char* path;
	char* value;
	int order;
	link children;
} Directory;

struct STnode {
	Directory* dir;
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
