#include "bst.c"
#include "bst.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	Tree a;
	a = NULL;
	int value, option, h;

	while(1) {
		scanf("%d", &option);
		switch(option){
			case 1:
				scanf("%d", &value);
				a = insert(a, value);
				break;
			case 3:
				inOrder(a);
				printf("\n");
				break;
			case 2:
				scanf("%d", &value);
				a = removeElement(a, value);
				break;
			case 4:
				posOrder(a);
				printf("\n");
				break;
			case 10:
				h = height(a);
				printf("%d", h);
				break;
			case 99:
				exit(1);
		}
	}
}