#include "header.h"
	
void traverse(link node/*, char* full*/) {
	if (node == NULL)
		return;
	traverse(node->l/*, full*/);
	visit(node->dir/*, full*/);
	traverse(node->r/*, full*/);
}

void visit(dir3 dir/*, char* full*/) {
	/*char* full_path = (char*)malloc(sizeof(char)*(strlen(dir->path)+strlen(full))+2);
	strcpy(full_path, full);
	strcat(full_path, "/");
	strcat(full_path, dir->path);*/
	printf("%s\n", dir->path);
}

/*---------------------------------------------------------------*/
/*Cria o node, coloca o left, right e height, atribui o directory*/
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

/*
link deleteR(link child, char* token) {
	if (h==NULL)
		return h;
	else if (strcmp(token, child->dir->path))
		child->l=deleteR(child->l, token);
	else if (strcmp(child->dir->path, token))
		child->r=deleteR(child->r, token);
	else {
		if (child->l != NULL && child->r != NULL){
			link aux = max(h->l);
			{dir3 x; x = child->dir; child->dir = aux->dir; aux->dir = x;}
			child->l = deleteR(child->l, child-> key(aux->item));
		} else {
			link aux = child;
			if (child->l == NULL && child->r == NULL)
				child = NULL;
			else if (child->l == NULL)
				child = child->r;
			else 
				child = child->l;
			deleteItem(aux->dir);
			free(aux);
		}
	}
	h=AVLbalance(h);
	return h;
}

link max(link h) {
	if (h == NULL || h->r == NULL)
		return h;
	else
		return max(h->r);
}*/
