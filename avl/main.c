#include "avl.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	Tree a;
	int value, option, bfControl, h;
	int decressed = 1;
	a  == NULL;
	//init(&a);

	while(1) {
		scanf("%d", &option);

		switch(option) {
			case 1:
				scanf("%d", &value);
				a = insert(a, value, &bfControl);
				break;
			case 3:
				show(a);
				printf("\n");
				break;
			case 2:
				scanf("%d", &value);
				a = removeElement(a, value, &bfControl);
				break;
			case 4:
				media(a);
				printf("\n");
				break;
			case 10:
				h = height(a);
				printf("%d", h);
				break;
			case 99:
				exit(0);
		}
	}
	return 0;
}