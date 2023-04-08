#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

Tree insert(Tree a, int v) {
	if(a == NULL) {
		Tree new = (Tree) malloc(sizeof(Tree));
		new->value = v;
		new->left = NULL;
		new->right = NULL;
		return new;
	}
	else {
		if(a->value > v) {
			a->left = insert(a->left, v);
		} else {
			a->right = insert(a->right, v);
		}
		return a;
	}
}

void inOrder(Tree a) {
	if(a != NULL){
		inOrder(a->left);
		printf("{%d}", a->value);
		inOrder(a->right);
	}
}

void posOrder(Tree a) {
	if(a != NULL) {
		posOrder(a->left);
		posOrder(a->right);
		printf("[%d] ", a->value);
	}
}

int height(Tree a){
	if(a != NULL) {
		int hleft, hright, max;
		max = hleft = hright = 0;
		
		hleft = height(a->left);
		hright = height(a->right);

		if(hleft > hright) {
			max = hleft + 1;
		}else {
			max = hright + 1;
		}
		return max;
	}else {
		return 0;
	}
}

Tree removeElement(Tree a, int v) {
	if(a == NULL) {
		return NULL;
	}

	if(a->value == v){
		//sem filhos
		if(a->left == NULL && a->right == NULL) {
			free(a);
			printf("\nElemento sem filhos removido\n");
			return NULL;
		} else {
			//2 filhos
			if(a->left != NULL && a->right != NULL) {
				Tree aux = a->right;
				while(aux->left != NULL){
					aux = aux->left;
				}
				a->value = aux->value;
				aux->value = v;
				a->right = removeElement(a->right, v);

				return a;

			}else {
				//1 filho
				Tree aux;
				if(a->left != NULL && a->right == NULL) {
					aux = a->left;
				}else {
					aux = a->right;
				}
				free(a);
				printf("elemento com 1 filho removido\n");
				return aux;
			}

		}
	} else {
		if(v < a->value){
			a->left = removeElement(a->left, v);
		} else {
			a->right = removeElement(a->right, v);
		}
		return a;
	}
}
	
