#include "bst.h"
#include "bst.c"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	tree a, aux;
	a = NULL;
	int option, value;

	while(1){
		scanf("%d", &option);
		switch(option) {
			case 1:
				scanf("%d", &value);
				a = insert(a, value);
				break;
			case 2:
				preOrder(a);
				printf("\n");
				break;
			case 3:
				inOrder(a);
				printf("\n");
				break;
			case 4:
				posOrder(a);
				printf("\n");
				break;
			case 5:
				scanf("%d", &value);
				a  = removeElement(a, value);
				//printf("elemento removido \n");
				break;
			case 6:
				scanf("%d", &value);
				aux = search(a, value);
				printf("[%d]", value);
				printf("\n");
				break;
			case 99:
				exit(1);
			}
		}
	return 0;
}