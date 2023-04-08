#include "rb.h"
#include <stdio.h>
#include <stdlib.h>

Arvore no_null;

void inicializar(Arvore *raiz) {
	*raiz = NULL;
	no_null = (Arvore) malloc(sizeof(struct no_rb));
	no_null->cor = DUPLO_PRETO;
	no_null->dado = 0;
	no_null->esq = NULL;
	no_null->dir = NULL;
}

int eh_raiz(Arvore elemento) {
	return (elemento->pai == NULL);
}

int eh_filho_esquerdo(Arvore elemento) {
	return (elemento->pai != NULL && elemento == elemento->pai->esq);
}
int eh_filho_direito(Arvore elemento) {
	return (elemento->pai != NULL && elemento == elemento->pai->dir);
}

Arvore eh_irmao(Arvore elemento) {
	//se ele eh o filho esquerdo, retorna o filho do nodo acima dele, a direita
	if(eh_filho_esquerdo(elemento))
		return elemento->pai->dir;
	else
		return elemento->pai->esq;
}

Arvore tio(Arvore elemento) {
	return eh_irmao(elemento->pai);
}


enum cor cor(Arvore elemento) {
	enum cor c;
	if(elemento == NULL)
		c = PRETO;
	else
		c = elemento->cor;
	return c;
}
	
int altura(Arvore a) {
	if(a == NULL) 
		return 0;
	else {
		int esq, dir;
		esq = altura(a->esq);
		dir = altura(a->dir);

		if(esq > dir)
			return (esq + 1);
		else
			return (dir + 1);
	}
}

int maior_elemento(Arvore raiz) {
	if(raiz == NULL)
		return -1;
	if(raiz->dir == NULL)
		return raiz->dado;
	else
		return maior_elemento(raiz->dir);
}

void imprimir(Arvore raiz) {
	if(raiz != NULL) {
		imprimir(raiz->esq);
		imprimir_elemento(raiz);
		imprimir(raiz->dir);
	}
}
void imprimir_elemento(Arvore raiz) {
	switch(raiz->cor) {
		case PRETO:
			printf("\x1b[30m[%d]\x1b[0m", raiz->dado);
			break;
		case VERMELHO:
			printf("\x1b[31m[%d]\x1b[0m", raiz->dado);
			break;
		case DUPLO_PRETO:
			printf("\x1b[32m[%d]\x1b[0m", raiz->dado);
			break;
	}
}


void inserir(Arvore *raiz, int valor) {
	Arvore aux, pai, novo;
	//utiliza-se *raiz por ser um ponteiro de um ponteiro
	aux = *raiz; 
	//esse pai serve para salvar o ponteiro acima do null, que eh onde iremos adicionar
	//o novo elemento, ent ele fica responsavel de fazer a conexão
	pai = NULL;

	/*navega na arvore ate encontrar a posicao vaga apropriada para o elemento
	nesta descida é necessário  manter o ponteiro para pai, pois apos
	encontar o NULL, não seria possivel vooltar*/
	while(aux != NULL) {
		pai = aux;
		//verificando para que lado devemos percorrer
		if(aux->dado > valor)
			aux = aux->esq;
		else
			aux = aux->dir;
	}

	novo = (Arvore) malloc(sizeof(no_rb));
	novo->dado = valor;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->pai = pai;
	novo->cor = VERMELHO;

	if(eh_raiz(novo)) {
		*raiz = novo;
	} else {
		if(valor > pai->dado)
			pai->dir = novo;
		else  
			pai->esq = novo; 
	}

	//essa eh a raiz de toda a arvore, não a raiz relativa;
	//apos inserido o elemento, precisamos verificar a cor dele e afins
	ajustar(raiz, novo);

}

void remover(Arvore *raiz, Arvore* raiz_relativa, int valor) {
	Arvore aux = *raiz_relativa;

	while(aux != NULL) {
		if(valor == aux->dado) {
			//sem filhos
			if(aux->esq == NULL && aux->dir == NULL) {
				//remover raiz sem filhos
				if(eh_raiz(aux)) {
					*raiz = NULL;
					break;
				}
				//sem filhos, mas nao raiz
				if(aux->cor == VERMELHO) {
					if(eh_filho_esquerdo(aux))
						aux->pai->esq = NULL;
					else
						aux->pai->dir = NULL;
					break;

				} else {
					/*se o elemento for preto, 
					precisa substituir pelo nonull */
					no_null->pai = aux->pai;

					if(eh_filho_esquerdo(aux))
						aux->pai->esq = no_null;
					else 
						aux->pai->dir = no_null;

					reajustar(raiz, no_null);
					break;
				}
			}
			//um filho

			//apenas o filho esquerdo
			if(aux->dir == NULL) {
				aux->esq->cor = PRETO;
				if(eh_raiz(aux)) {
					*raiz = aux->esq;
				} else {
					if(eh_filho_esquerdo(aux))
						aux->pai->esq = aux->esq;
					else 
						aux->pai->dir = aux->esq;
				}
				break;
			}
			//apenas filho direito
			if(aux->esq == NULL) {
				aux->dir->cor = PRETO;
				if(eh_raiz(aux)) {
					*raiz = aux->dir;
				} else {
					if(eh_filho_esquerdo(aux))
						aux->pai->esq = aux->dir;
					else
						aux->pai->dir = aux->dir;
				}
				break;
			}
			//dois filhos
			if(aux->dir != NULL && aux->esq != NULL) {
				aux->dado = maior_elemento(aux->esq);
				remover(raiz, &(aux->esq),aux->dado);
				break;
			}

		} else {
			if(valor > aux->dado)
				aux = aux->dir;
			else
				aux = aux->esq;
		}
	}
}

void reajustar(Arvore *raiz, Arvore elemento) {
	
	//caso 1: eh a raiz
	if(eh_raiz(elemento)) {
		elemento->cor = PRETO;

		return;
	}

	//caso 2: pai preto, irmao vermelho e sobrinhos preto
	if(cor(elemento->pai) == PRETO &&
	 cor(eh_irmao(elemento)) == VERMELHO &&
	 (cor(eh_irmao(elemento)->dir) == PRETO || eh_irmao(elemento)->dir == NULL) &&
	 (cor(eh_irmao(elemento)->esq) == PRETO || eh_irmao(elemento)->esq == NULL)) {
		if(eh_filho_esquerdo(elemento))
			rotacao_simples_esquerda(raiz, elemento);
		else 
			rotacao_simples_direita(raiz, elemento);

		elemento->pai->pai->cor = PRETO;
		elemento->pai->cor = VERMELHO;

		return;
	 }

	 //caso 3: pai, irmaos e sobrinhos pretos
	 if(cor(elemento -> pai) == PRETO && cor(eh_irmao(elemento)) == PRETO &&
		(cor(eh_irmao(elemento)-> dir)  == PRETO || eh_irmao(elemento) -> dir == NULL) && 
		(cor(eh_irmao(elemento) -> esq)  == PRETO || eh_irmao(elemento) -> esq == NULL)){	
		eh_irmao(elemento) -> cor = VERMELHO;
		retira_duplo_preto(raiz, elemento);
		reajustar(raiz, elemento->pai);

		return;
	}

	//caso 4: pai vermelho, irmao e sobrinhps preto
	if(cor(elemento -> pai) == VERMELHO && 
		(cor(eh_irmao(elemento)) == PRETO || eh_irmao(elemento) == NULL) &&
		(cor(eh_irmao(elemento)-> dir)  == PRETO || eh_irmao(elemento) -> dir == NULL) && (cor(eh_irmao(elemento) -> esq) == PRETO || eh_irmao(elemento) -> esq == NULL)){

			elemento -> pai -> cor = PRETO;
			eh_irmao(elemento) -> cor = VERMELHO;
			
			retira_duplo_preto(raiz, elemento); 

			return;

	}
	// CASO 5: irmão preto e um dos sobrinhos vermelho

	//caso 5a
	if(eh_filho_esquerdo(elemento) && cor(eh_irmao(elemento)) == PRETO &&
		(cor(eh_irmao(elemento) -> dir) == PRETO || eh_irmao(elemento) -> dir == NULL) && cor(eh_irmao(elemento) -> esq) == VERMELHO){
			
			rotacao_simples_direita(raiz, eh_irmao(elemento));
			eh_irmao(elemento) -> cor = PRETO;
			eh_irmao(elemento) -> dir -> cor = VERMELHO;
			
			reajustar(raiz, elemento);

			return;
		}

	//caso 5b
	if(eh_filho_direito(elemento) && cor(eh_irmao(elemento)) == PRETO &&
		(cor(eh_irmao(elemento) -> esq) == PRETO || eh_irmao(elemento) -> esq == NULL) 		
		&& cor(eh_irmao(elemento) -> dir) == VERMELHO) {
		
			rotacao_simples_esquerda(raiz, eh_irmao(elemento));
			eh_irmao(elemento) -> cor = PRETO;
			eh_irmao(elemento) -> esq -> cor = VERMELHO;
			
			reajustar(raiz, elemento);

			return;
	}

	//caso 6: irmao preto e um dos sobrinhos vermelho

	//caso 6a:
	if(eh_filho_esquerdo(elemento) && 
		cor(eh_irmao(elemento)) == PRETO && 
		cor(eh_irmao(elemento) -> dir) == VERMELHO) {
		
		enum cor cor_original_pai = cor(elemento -> pai);
		
		rotacao_simples_esquerda(raiz, elemento -> pai);
		
		elemento -> pai -> pai -> cor = cor_original_pai;
		elemento -> pai -> cor = PRETO;
		tio(elemento) -> cor = PRETO;		
		
		retira_duplo_preto(raiz, elemento);

		return;
	}

	//caso 6b
	if(eh_filho_direito(elemento) && 
		cor(eh_irmao(elemento)) == PRETO && 
		cor(eh_irmao(elemento) -> esq) == VERMELHO) {

		enum cor cor_original_pai = cor(elemento -> pai);
		
		rotacao_simples_direita(raiz, elemento -> pai);
		
		elemento -> pai -> pai -> cor = cor_original_pai;
		elemento -> pai -> cor = PRETO;
		tio(elemento) -> cor = PRETO;		
		
		retira_duplo_preto(raiz, elemento);

		return;
	}
}

void retira_duplo_preto(Arvore *raiz, Arvore elemento) {
	if(elemento == no_null) {
		if(eh_filho_esquerdo(elemento))
			elemento->pai->esq = NULL;
		else
			elemento->pai->dir = NULL;
	} else {
		elemento->cor = PRETO;
	}
}


void ajustar(Arvore* raiz, Arvore novo) {
	
	//se o pai e o elemento forem vermelhos, precisa ajustar
	while(cor(novo->pai) == VERMELHO && cor(novo) == VERMELHO) {
		//caso 1
		if(cor(tio(novo)) == VERMELHO){
			//tornando o tio e pai do elemento inseido preto
			tio(novo)->cor = PRETO;
			novo->pai->cor = PRETO;
			novo->pai->pai->cor = VERMELHO;

			//agr eu quero que verifique se o avo do elemento inserido
			//que se tornou vermelho, está na cor correta, ent eu atualizo
			novo = novo->pai->pai;

			continue;
		}
		//case 2a: rotacao simples direita
		if(eh_filho_esquerdo(novo) && eh_filho_esquerdo(novo->pai)) {
			//rotacao simples passando a raiz e o avo do elemento
			rotacao_simples_direita(raiz, novo->pai->pai);
			novo->pai->cor = PRETO;
			novo->pai->dir->cor = VERMELHO;

			continue;
		}
		//caso 2b: rotacao simples esquerda
		if(eh_filho_direito(novo) && eh_filho_direito(novo->pai)) {
			rotacao_simples_esquerda(raiz, novo->pai->pai);
			novo->pai->cor = PRETO;
			novo->pai->esq->cor = VERMELHO;

			continue;
		}
		//caso 3a: rotacao dupla direita
		if(eh_filho_direito(novo) && eh_filho_esquerdo(novo->pai)) {
			rotacao_simples_esquerda(raiz, novo->pai);
			rotacao_simples_direita(raiz, novo->pai);
			novo->dir->cor = VERMELHO;
			novo->esq->cor = VERMELHO;
			novo->cor = PRETO;

			continue;
		}
		//caso 3b: rotacao dupla esquerda
		if(eh_filho_esquerdo(novo) && eh_filho_direito(novo->pai)) {
            rotacao_simples_direita(raiz, novo->pai);
            rotacao_simples_esquerda(raiz, novo->pai);
            novo->dir->cor = VERMELHO;
            novo->esq->cor = VERMELHO;
            novo->cor = PRETO;
            
            continue;

		}
	}
	//Após todas as correções a raiz pode ter ficado na cor vermelha, portanto passamos ela novamente para cor preta
	(*raiz)->cor = PRETO;
}

/*
		(p)					(u)
	   /   \               /   \
	 (u)	(t3)  ==>	 (t1)	(p)
	/   \			            /  \   
 (t1)   (t2)		          (t2) (t3)                           
*/


void rotacao_simples_direita(Arvore *raiz, Arvore pivo) {
	Arvore p, u, t2;
	p = pivo;
	u = pivo->esq;
	t2 = u->dir;

	//para fazer a ligacao da raiz a sub-arvore com seu pai,
	//eh preciso saber se o pivo era um filho esquerdo ou direito

	int posicao_pivo_esq = eh_filho_esquerdo(pivo);
	//pois ele precisa ser inserido em um dos lados do pai

	//trocando o lado do t2
	p->esq = t2;

	//se ele n for null, precisa linká-lo novamente
	if(t2 != NULL) 
		t2->pai = pivo;

	//agora fazendo a rotação dos elementos restantes
	u->dir = pivo;
	u->pai = p->pai;
	p->pai = u;

	p->cor = VERMELHO;
	u->cor = PRETO;

	//testando se u eh raiz, pois se for, a raiz da arvore recebe ele
	if(eh_raiz(u))
		*raiz = u;

	//caso n seja, vamos descobrir se o pivo (valor que agr o u ocupa o lugar)
	//era filho esquerdo ou n para posicioná-lo corretamente
	//em relação ao pai
	else {
		if(posicao_pivo_esq)
			u->pai->esq = u;
		else
			u->pai->dir = u;
	}
}

/*
		(p)						(u)
	   /   \                   /   \
	 (t1)	(u)       ==>	 (p)	(t3)
	 	   /   \			/	\   
	 	(t2)   (t3)		  (t1)  (t2) 
  
*/
void rotacao_simples_esquerda(Arvore *raiz, Arvore pivo) {
	Arvore p, u, t2;
	p = pivo;
	u = p->dir;
	t2 = u->esq;

	int posicao_pivo_dir = eh_filho_direito(pivo);

	p->dir = t2;

	if(t2 != NULL)
		t2->pai = p;

	u->esq = p;
	u->pai = p->pai;
	p->pai = u;

	p->cor = VERMELHO;
	u->cor = PRETO;
	
	if(eh_raiz(u))
		*raiz = u;
	else {
		if(posicao_pivo_dir)
			u->pai->dir = u;
		else
			u->pai->esq = u;
	}
}

void preorder (Arvore raiz) {
  if (raiz != NULL) {
      imprimir_elemento(raiz);
      preorder (raiz->esq);
      preorder (raiz->dir);
    }
}