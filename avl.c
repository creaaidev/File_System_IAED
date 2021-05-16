#include "header.h"

struct STnode { Item item; link l, r; int height};
link NEW(Item item, link l, link r) {
	link x = (link)malloc(sizeof(struct STnode));
	x->item = item;
	x->l = l;
	x->r = r;
	x->height=1;
	return x;
}
int height(link h){
	if (h == NULL) 
		return 0;
	return h->height;
}

link rotL(link h)
{
int height_left, height_right;
link x = h->r;
h->r = x->l;
x->l = h;
