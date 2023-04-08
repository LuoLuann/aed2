#ifndef AVL_H
#define AVL_H

typedef struct node_avl {
	int value, bf;
	struct node_avl *left, *right;
}node_avl;

typedef node_avl* Tree;

void pares(Tree a);

void impares(Tree a);

void media(Tree a);

int height(Tree a);

void init(Tree *a);

Tree insert(Tree a, int v, int *increase);

Tree removeElement(Tree a, int v, int *decreased);

Tree rotate(Tree a);

Tree single_right_rotation(Tree a);

Tree single_left_rotation(Tree a);

Tree single_right_rotation_remotion(Tree a);

Tree single_left_rotation_remotion(Tree a);

Tree complex_right_rotation(Tree a);

Tree complex_left_rotation(Tree a);

void show(Tree a);

#endif