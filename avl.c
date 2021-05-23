#include "header.h"

/* Traverse InOrder */
void traverse(link node) {
	if (node == NULL)
		return;
	traverse(node->l);
	visit(node->dir);
	traverse(node->r);
}

void visit(dir3 dir) {
	printf("%s\n", dir->path);
}

link NEW(dir3 dir, link l, link r) {
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
	if (strcmp(v, h->dir->path) < 0) /* <0 v first */
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

/* Double Rotation Left Right */
link rotLR(link h) {
	if (h==NULL) return h;
	h->l=rotL(h->l);
	return rotR(h);
}

/* Double Rotation Right Left */
link rotRL(link h) {
	if (h==NULL) return h;
	h->r=rotR(h->r);
	return rotL(h);
}

/* Balance Factor */
int Balance(link h) {
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

link insertR(link h, dir3 directory) {
	if (h == NULL)
		return NEW(directory, NULL, NULL);
	if (strcmp(directory->path, h->dir->path) < 0)
		h->l = insertR(h->l, directory);
	else
		h->r = insertR(h->r, directory);
	h=AVLbalance(h);
	return h;
}

link max(link h) {
	if (h == NULL || h->r == NULL)
		return h;
	else
		return max(h->r);
}

/* Please understand that in order to avoid using Doubly Linked Lists I had to
   keep this function relatively big so as to catch all the edge cases */
void linked_target_delete(dir3 parent, char* path) {
	llnode aux = parent->first;
	llnode bye = NULL; /*In case the first is the wanted dir*/
	if (aux != NULL && !strcmp(aux->dir->path, path)) {
		if (parent->first == parent->last)
			parent->last = NULL;
		parent->first = parent->first->next;
		free(aux);
		return;
	}
	while (aux != NULL) {
		if (aux != parent->last) {
			if (!strcmp(aux->next->dir->path, path)) {
				bye = aux->next;
				aux->next = aux->next->next;
				if (bye == parent->last)
					parent->last = aux->next;
				free(bye);
				return;
			}
		} else {
			if (!strcmp(aux->dir->path, path)) {
				bye = aux;
				if (aux == parent->first) {
					parent->first = NULL;
				}
				parent->last = NULL;
				free(bye);
				return;
			}
		}
		aux = aux->next;
	}
}
/* This function is from the teacher's mostly, I just changed specific parts
   so as to work with my own code */
link deleteR(link h, char* path) {
	if (h == NULL)
		return h;
	else if (strcmp(path, h->dir->path) < 0)
		h->l = deleteR(h->l, path);
	else if (strcmp(h->dir->path, path) < 0)
		h->r = deleteR(h->r, path);
	else {
		if (h->l != NULL && h->r != NULL) {
			link aux = max(h->l);
			{dir3 x; x = h->dir; h->dir = aux->dir; aux->dir = x;}
			h->l = deleteR(h->l, aux->dir->path);
		}
		else {
			link aux = h;
			if (h->l == NULL && h->r == NULL)
				h = NULL;
			else if (h->l == NULL)
				h = h->r;
			else 
				h = h->l;
			linked_target_delete(aux->dir->parent, aux->dir->path); 
			clear_dir(aux->dir);
			free(aux);
		}
	}
	h = AVLbalance(h);
	return h;
}
