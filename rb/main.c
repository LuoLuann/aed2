#include "rb.h"
#include "rb.c"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	Arvore rb;
	int v, op, h;
	inicializar(&rb);

	while(1) {
		scanf("%d", &op);
		switch(op) {
			case 1:
				scanf("%d", &v);
				inserir(&rb, v);
				break;
			case 2:
				scanf("%d", &v);
				remover(&rb, &rb, v);
				break;
			case 3:
				imprimir(rb);
				printf("\n");
				break;
			case 10:
				h = altura(rb);
				printf("%d \n", h);
				break;
			case 99:
				exit(0);
		}
	}

	return 0;
}