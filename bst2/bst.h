#ifndef BST_H
#define BST_H

typedef struct node {
	int value;
	struct node *left, *right;
}node;

typedef node* Tree;

Tree insert(Tree a, int v);

void inOrder(Tree a);

Tree removeElement(Tree a, int v);

void posOrder(Tree a);

int height(Tree a);

#endif