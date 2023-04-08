#include "bst.h"
#include <stdio.h>
#include <stdlib.h>



tree insert(tree a, int v) {
	//caso base da recursão
	//inserir numa (sub) arvore vazia
	if(a == NULL) {
		//alocar espaço para o no
		tree no = (tree) malloc(sizeof(no));
		//inicializar os valores das variaveis membro
		no->value = v;
		no->left = NULL;
		no->right = NULL;
		return no;
	} else {
		//se o valor que eu quero inserir for menor que a raiz
		//relativa (a->value), inserir na sub arvore a esquerda
		if(a->value > v) {
			a->left = insert(a->left, v);
		}else {
			a->right = insert(a->right, v);
		}
		return a;
	}
}

tree search(tree a, int v) {
	//caso base: vazia ou com um elemento
	if(a == NULL || a->value == v) {
		return a;
	}
	//procurando nos filhos
	else {
		if(v > a->value) {
			return search(a->right, v);
		}
		else {
			return search(a->left, v);
		}
	}
}
void preOrder(tree a) {
	if(a != NULL) {
		printf("[%d]", a->value);
		preOrder(a->left);
		preOrder(a->right);
	}
}
void inOrder(tree a) {
	if(a != NULL) {
		inOrder(a->left);
		printf("[%d]", a->value);
		inOrder(a->right);
	}
}
void posOrder(tree a) {
	if(a != NULL) {
		printf("[%d]", a->value);
		posOrder(a->right);
		posOrder(a->left);

	}
}

tree removeElement(tree a, int v) {
	//caso base da arvore vazia
	if(a == NULL) {
		return NULL;
	} else {
		//procurar pelo no para remover
		if(a->value == v) {
			//remover no sem filhos
			if(a->left == NULL && a->right == NULL) {
				free(a);
				printf("elemento sem filhos removido\n");
				return NULL;
			} else {
			//remover nos com filhos
				//com dois filhos
				if(a->left != NULL && a->right != NULL) {
					//usando um aux que vai salvar o valor a esquerda
					//ou seja, indo para a sub arvore a esquerda, logo escolhendo 
					//o valor maior a direta dessa subarvore
					tree aux = a->left;

					//procurando o valor mais a direita da subarvore a esquerda
					while(aux->right != NULL){
						aux = aux->right;
					}
					//agr passando o conteudo do no mais a direita para o no
					//que queremos remover
					a->value = aux->value;
					//passando o valor do no que queremos remover para o no mais a direita
					aux->value = v;
					a->left = removeElement(a->left, v);

					return a;
					
				} else {
					
					tree aux;
					if(a->left != NULL && a->right == NULL) {
						aux = a->left;
					} else {
						aux = a->right;
					}
					free(a);
					printf("elemento com um filho removido\n");
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
} 

int summation(tree a) {
	if(a == NULL) {
		return 0;
	} else {
		int sum = a->value + summation(a->left) + summation(a->right);
		return sum;
	}
	/*com tenario
		return (a==NULL)? 0: a->value + summation(a->left) + summation(a->right);
	*/
}

// void remove(tree a, int v) {
// 	//
// }