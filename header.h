/* Includes */
#include <stdio.h>
#include <string.h>

/* Defines */
#define HELP "Imprime todos os comandos disponiveis."
#define QUIT "Termina o programa."
#define SET "Adiciona ou modifica o valor a armazenar."
#define PRINT "Imprime todos os caminhos e valores."
#define LIST "Lista todos os componentes imediatos de um sub-caminho."
#define SEARCH "Procura o caminho dado um valor."
#define DELETE "Apaga um caminho e todos os subcaminhos."
#define CMD_COUNT 7
#include "Item.h"

/* Typedefs and structs */
	/* directory struct */
typedef struct {
	char* path;
	int order;
} Directory;
	/* structs for AVL tree */
typedef struct STnode* link;
void STinit(link*);
int STcount(link);
Item STsearch(link,Key);
void STinsert(link*,Item);
void STdelete(link*,Key);
void STsort(link,void (*visit)(Item));
void STfree(link*);

/* Prototypes */
void help();
