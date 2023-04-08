#ifndef RB_H
#define RB_H

enum cor { VERMELHO, PRETO, DUPLO_PRETO };

typedef int tipo_dado;

typedef struct no_rb {
	tipo_dado dado;
	enum cor cor;
	struct no_rb *esq, *dir, *pai;
}no_rb;

typedef no_rb* Arvore;

//funcoes principais

void inicializar(Arvore *raiz);
void inserir(Arvore *raiz, int valor);
void remover(Arvore *raiz, Arvore* raiz_relativa, int valor);
int altura(Arvore raiz);
void imprimir(Arvore raiz);
void imprimir_elemento(Arvore raiz);

//funcoes auxiliares

enum cor cor(Arvore elemento);
int eh_raiz(Arvore elemento);
int eh_filho_esquerdo(Arvore elemento);
int eh_filho_direito(Arvore elemento);
int maior_elemento(Arvore raiz);
Arvore eh_irmao(Arvore elemento);
Arvore tio(Arvore elemento);
int maior(int a, int b);
int maior_elemento(Arvore raiz);
int menor_elemento(Arvore raiz);

//ajustes
void ajustar(Arvore *raiz, Arvore elemento);
void rotacao_simples_direita(Arvore *raiz, Arvore pivo);
void rotacao_simples_esquerda(Arvore *raiz, Arvore pivo);
void rotacao_dupla_direita(Arvore *raiz, Arvore pivo);
void rotacao_dupla_esquerda(Arvore *raiz, Arvore pivo);
void reajustar(Arvore *raiz, Arvore elemento);
void retira_duplo_preto(Arvore *raiz, Arvore elemento);
void preOrder(Arvore a);
#endif