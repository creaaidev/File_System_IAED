#include "header.h"
	
/* maybe it doesnt have any arguments */

	/* AVL for alphabetical order */
link NEW(Directory* dir, link l, link r) {
	link x = malloc_link();
	x->dir = dir;
	x->l = l;
	x->r = r;
	x->height=1;
	return x;
}

link searchR(link h, char* v) {
	if (h == NULL)
		return NULL;
	if (!strcmp(v, h->dir->path))
		return h;
	if (strcmp(v, h->dir->path) < 0)
		return searchR(h->l, v);
	else
		return searchR(h->r, v);
}

int height(link h){
	if (h == NULL) 
		return 0;
	return h->height;
}

link rotL(link h) {
	int height_left, height_right;
	link x = h->r;
	h->r = x->l;
	x->l = h;
	
	height_left = height(h->l); height_right = height(h->r);
	h->height = height_left > height_right ? height_left + 1 :
		height_right + 1;
	height_left = height(x->l); height_right = height(x->r);
	x->height = height_left > height_right ? height_left + 1 :
		height_right + 1;
	return x;
}

link rotR(link h) {
	int height_left, height_right;
	link x = h->l;
	h->l = x->r;
	x->r = h;

	height_left = height(h->l); height_right = height(h->r);
	h->height = height_left > height_right ? height_left + 1 :
		height_right + 1;

	height_left = height(x->l); height_right = height(x->r);
	x->height = height_left > height_right ? height_left + 1 :
		height_right + 1;
	return x;
}

void update_height(link h) {
	int height_left = height(h->l);
	int height_right = height(h->r);
	h->height = height_left >
	height_right ? height_left + 1 :
		height_right + 1;
}

link rotLR(link h) { /*rotação dupla esquerda direita*/
	if (h==NULL) return h;
	h->l=rotL(h->l);
	return rotR(h);
}

link rotRL(link h) { /*rotacao dupla direita esquerda*/
	if (h==NULL) return h;
	h->r=rotR(h->r);
	return rotL(h);
}

int Balance(link h) {/*Balance factor*/
	if(h == NULL) return 0;
	return height(h->l)-height(h->r);
}

link AVLbalance(link h) {
	int balanceFactor;
	if (h==NULL) return h;
	balanceFactor= Balance(h);
	if(balanceFactor>1) {
		if (Balance(h->l)>=0) h=rotR(h);
		else h=rotLR(h);
	}
	else if(balanceFactor<-1){
		if (Balance(h->r)<=0) h = rotL(h);
		else h = rotRL(h);
	} else
		update_height(h);
	return h;
}

link insertR(link h, Directory* dir) {
	if (h == NULL)
		return NEW(dir, NULL, NULL);
	if (strcmp(dir->path, h->dir->path) < 0)
		h->l = insertR(h->l, dir);
	else
		h->r = insertR(h->r, dir);
	h=AVLbalance(h);
	return h;
}
/* tenho de fazer isto depois
link deleteR(link h, Key k) {
	if (h==NULL) return h;
	else if (less(k, key(h->item))) h->l=deleteR(h->l,k);
	else if (less(key(h->item), k)) h->r=deleteR(h->r,k);
	else {
		if (h->l !=NULL && h->r !=NULL){
			link aux=max(h->l);
			{Item x; x=h->item; h->item=aux->item; aux->item=x;}
			h->l= deleteR(h->l, key(aux->item));
		} else {
			link aux=h;
			if (h->l == NULL && h->r == NULL) h=NULL;
			else if (h->l==NULL) h=h->r;
			else h=h->l;
			deleteItem(aux->item);
			free(aux);
		}
	}
	h=AVLbalance(h);
	return h;
}*/
