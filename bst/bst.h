#ifndef BST_H	
#define BST_H	


typedef struct no {
	int value;
	struct no *left, *right;
} no;

typedef no* tree;

tree insert(tree a, int v);

tree search(tree a, int v);

void preOrder(tree a);

void inOrder(tree a);

void posOrder(tree a);

tree removeElement(tree a, int v);

int summation(tree a);

#endif