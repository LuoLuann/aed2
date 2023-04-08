#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

int height(Tree a) {
	if(a == NULL) {
		return 0;
	} else {
		int left = height(a->left);
		int right = height(a->right);
	
		if(left > right)
			return left + 1;
		else 
			return right + 1;
		
	}
}
void pares(Tree a){
	return;
}
void impares(Tree a){
	if(a != NULL) {
		impares(a->left);
		if(a->value % 2 != 0) {
			printf("%d ", a->value);
		}
		impares(a->right);
	}
}
void media(Tree a) {
	float c = 0;
	float m  = 0;
	float sum = 0;
	if(a != NULL) {
		
		media(a->left);
		media(a->right);
		sum = sum + a->value;
		c++;
		
	}
	m = sum/c;
	printf("%f ", m);
}


void init(Tree *a) {
	*a = NULL;
} 

Tree insert(Tree a, int v, int *increase) {
	//caso base a raiz eh vazia, ent cria um novo no
	if(a == NULL) {
		Tree new = (Tree) malloc(sizeof(Tree));
		new->value = v;
		new->left = NULL;
		new->right = NULL;
		new->bf = 0;
		*increase = 1;

		return new;
		
	} //caso não esteja, buscar onde inserir
	else {
		//se o valor for maior que a raiz, add elemento a direita
		if(v > a->value) {
			a->right = insert(a->right, v, increase);

			//calcular os reajustes do fator de balanco
			if(*increase) {
				switch(a->bf){
					//arvore totalmente balancada e agr tem um fator no lado direito
					case 0:
						a->bf = 1;
					   *increase = 1;
					    break;
					
					//arvore tava pendendo pra esquerda, agr ficou equilibrada
					case -1:
						a->bf = 0;
						*increase = 0;
						break;

					//caso o fb no lado direito 1 e agr se torne 2, logo precisa ser balanceada
					case 1:
						//a->bf = 2;
						*increase = 0; 
						a = rotate(a);//como pendeu pra direita, rota para esquerda
						break;

				}
			}
		} 
		else {
			//elemento menor que a raiz, add elemento esquerda
			a->left = insert(a->left, v, increase);

			//calcular os reajustes do fator de balanco
			if(*increase) {
				switch(a->bf) {
					//arvore balanceada e agr pende 1 para direita
					case 0:
						a->bf = -1;
						*increase = 1;
						break;
					//arvore pende um para esquerda e agr equilibra
					case 1:
						a->bf = 0;
						*increase = 0;
						break;

					//pendia 1 para esquerda e agr desbalanceia
					case -1:
						//a->bf = -2;
						*increase = 0;
						a = rotate(a);
						break;

				}
			}
		}
	}
	return a;
}
Tree removeElement(Tree a, int v, int *decreased) {
//caso base: raiz vazia
	if(a == NULL) {
        *decreased = 0;
        return a;
    }
  //valor encontrado, hora de remover
  	if(a->value == v) {
    		if(a->left == NULL && a->right == NULL) {
    			free(a);
    			*decreased = 1;
    			return NULL;
    		}
    		//dois filhos
    		if(a->left != NULL && a->right != NULL) {
    			Tree aux = a->left;
    			//procura o sucesso para substituir o valor a ser removido
    			while(aux->right != NULL)
    				aux = aux->right;

    			a->value = aux->value;

    			a->left = removeElement(a->left, aux->value, decreased);

                switch(a->bf){
                        case 0:
                            a->bf = 1;
                            *decreased = 0;
                            break;
                        case -1:
                            a->bf = 0;
                            *decreased = 1;
                            break;
                        case 1:
                            *decreased = 1;
                            a = rotate(a);
                    }
                    return a;

    		}
    		else { //caso a raiz so tenha um filho
    			Tree aux;
    			*decreased = 1;
    			if(a->right != NULL && a->left == NULL){
    				aux = a->right;
    			}
    			else {
    				aux = a->left;
    				
    			}
    			free(a);
    			return aux;
    		} 
		}


		else {
			if(v > a->value) {
		    		a->right = removeElement(a->right, v, decreased);

		    		if(*decreased) 
		    		{
		    			switch(a->bf)
		    			{	
		    				//raiz pendendo esquerda, agr que removeu ela, gerou -2. Ou seja
		    					//rotacao
		    				case -1:
		    					a->bf = -2;
		    					if(a->left->bf == 0)
		    					{
		    						*decreased = 0;
		    					}
		    					else { 
		    						*decreased = 1; 
		    					}
		    					a = rotate(a);
		    					break;

		    				//raiz balanceadaaaaaaaa, agr pende pra esquerda
		    				case 0:
		    					a->bf = -1;
		    					*decreased = 0;
		    					break;

		    				//
		    				case 1:
		    					a->bf = 0;
		    					*decreased = 1;
		    					break;
		    			}
		    		}
		    	}
		    else {
		    		a->left = removeElement(a->left, v, decreased);

		    		if(*decreased) 
		    		{
		    			switch(a->bf) 
		    			{
		    				//raiz estava pendendo pra esquerda, agr equilibrou
		    				case -1:
		    					a->bf = 0;
		    					*decreased = 1;
		    					break;

		    				//a raiz estava balanceada, apos remover ela passa a pendera direita
		    				case 0:
		    					a->bf = 1;
		    					*decreased = 0;
		    					break;

		    				//a raiz pendia para direita, apos remover outro na esquerda, ela passa
		    					//a a pender 2. Logo precisa ser rotacionada
		    				case 1:
		    					a->bf = 2;
		    					if(a->right->bf == 0){
		    						*decreased = 0;
		    					}
		    					else { *decreased = 1; }

		    					a = rotate(a);//rotacao esquerda
		    					break;
		    			}
		    		}
		    	}
		}
		    	//valor a ser removido maior que a raiz
    	
	return a;

}
//chamar todas rotacoes
//e verificar qual o desbalanceamento atraves dos ifs
//e ajustar para cada caso especifico
Tree rotate(Tree a){
    if (a->bf > 0){
        if(a->right->bf >= 0){
            return single_left_rotation(a);
        }else{
            return complex_left_rotation(a);
        }
    }else{
        if (a->left->bf <= 0){
            return single_right_rotation(a);
        }else{
            return complex_right_rotation(a);
        }

    }
}

/*
		(p)						(u)
	   /   \                   /   \
	 (t1)	(u)       ==>	 (p)	(t3)
	 	   /   \			/	\   
	 	(t2)   (t3)		  (t1)  (t2) 
  
*/

Tree single_left_rotation(Tree a) {
	//quem ta desbalanceado eh p
	// bf(p) == 2, bf(u) == 1
	Tree p, u;
	p = a;
	u = p->right;

	//corrigindo fatores de balanco
	u->bf = 0;
	p->bf = 0;

	//rotacao
	p->right = u->left;
	u->left = p;

	return u;
}
/*
		(p)					(u)
	   /   \               /   \
	 (u)	(t3)  ==>	 (t1)	(p)
	/   \			            /  \   
 (t1)   (t2)		          (t2) (t3)                           
*/


Tree single_right_rotation(Tree a) {
	//bf(p) == -2, bf(u) == -1
	Tree p, u;

	p = a;
	u = p->left;

	//corrigindo fatores de balanco
	u->bf = 0;
	p->bf = 0;
	
	//rotação
	p->left = u->right;
	u->right = p;

	return u;
}

Tree single_left_rotation_remotion(Tree a) {
	Tree p, u;
	p = a;
	u = p->right;

	//corrigindo fatores de balanco
	u->bf = -1;
	p->bf = 1;

	p->right = u->left;
	u->left = p;

	return u;
}

Tree single_right_rotation_remotion(Tree a) {
	Tree p, u;
	p = a;
	u = p->left;

	//corrigindo fatores de balanco
	u->bf = 1;
	p->bf = -1;

	p->left = u->right;
	u->right = p;
	
	return u;
}	


/*
 /*  (p)             (p)             (v)
     / \             / \             / \
    t1 (u)     =>   t1 (v)    =>   (p) (u)
       / \             / \         / \  / \
     (v)  t4          t2 (u)      t1 t2 t3 t4
     / \                 / \
    t2  t3              t3  t4
 */

Tree complex_left_rotation(Tree a){
 	//fb(p) = 2, fb(u) = -1
    Tree p, u, v;

    p = a;
    u = p->right;
    v = u->left;

    //Rotação direita
    u->left = v->right;
    v->right = u;
    p->right = v;

    //Rotção esquerda
    p->right = v->left;
    v->left = p;
    
    //Atualizando os fatores de balanço
    if(v->bf==0){  
        u->bf = 0;
        v->bf = 0;
        p->bf=0;
    
    }    
    else if(v->bf==-1){  

        u->bf = 1;
        v->bf = 0;
        p->bf = 0;
    }   
     else{  
        u->bf = 0;
        v->bf = 0;
        p->bf =-1;
    }
   return v;
}


 /*   p               p               v
     / \             / \             / \
    u  t4     =>    v   t4    =>    u    p
   / \             / \             / \  / \
  t1  v           u  t3           t1 t2 t3 t4
     / \         / \
    t2  t3      t1  t2
 */


Tree complex_right_rotation(Tree a) {
	//fb(p) = -2, fb(u) = 1
	Tree p, u, v;

	p = a;
	u = p->left;
   v = u->right;

    // Rotação à esquerda    
    u->right = v->left;
    v->left = u;
    p->left = v;
    
    //Rotação á direita
    p->left=v->right;
    v->right = p;
    
    //Atualizando os fatores de balanço
    if(v->bf == 0){ 

        u->bf = 0;
        p->bf = 0;
        v->bf = 0;
    }
    else if(v->bf==-1){

        u->bf = 0;
        v->bf = 0;
        p->bf = 1;

    }
    else {

        u->bf = -1;
        v->bf = 0;
        p->bf = 0;

    }
    return v;
}


void show(Tree a) {
	//printf("(");
	if(a != NULL) {
		show(a->left);
		printf("valor: [%d] fator balanco: [%d] \n", a->value, a->bf);
		show(a->right);
	}
	//printf(")");
}