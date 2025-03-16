#include <stdio.h>
#include <stdlib.h>

typedef struct no_aux{
	int valor;
	struct no_aux* esq;
	struct no_aux* dir;
}No;

typedef No* Arvore;

typedef struct{
	Arvore* vet;
	int tam;
	int n_elem;
}Pilha;

void iniciaPilha(Pilha* ap_p, int tam){
	Arvore* novo = (Arvore*)malloc(sizeof(Arvore)*tam);
	ap_p->tam = tam;
	ap_p->n_elem = 0;
	ap_p->vet = novo;
}

void inserePilha(Pilha* ap_p, int valor){
	if(ap_p->n_elem >= ap_p->tam) return;
	Arvore novo = (Arvore) malloc(sizeof(No));
	novo->valor = valor;
	novo->esq = NULL;
	novo->dir = NULL;
	ap_p->vet[ap_p->n_elem] = novo;
	ap_p->n_elem = ap_p->n_elem + 1;
}

void criaArvore(Pilha* pil, Arvore* ap_a, int* vetor){
	int topo = 0, pos = 0;
	inserePilha(&(*pil), vetor[pos++]);
	topo++;
	while((pos < pil->tam) || topo > 1){
		if((pos < pil->tam) && (topo < 3 ||
					((pos % 2 != 0) && (((vetor[pos] == '*' || vetor[pos] == '/')
					 && (pil->vet[topo-2]->valor == '+'
						 || pil->vet[topo-2]->valor == '-' ||
						 pil->vet[topo-2]->valor == '%')) ||
						(vetor[pos] != '%' && pil->vet[topo-2]->valor == '%'))))){
			inserePilha(&(*pil), vetor[pos++]);
			topo++;
			inserePilha(&(*pil), vetor[pos++]);
			topo++;
		} else {
				pil->vet[topo-2]->dir = pil->vet[topo-1];
				pil->vet[topo-2]->esq = pil->vet[topo-3];
				pil->vet[topo-3] = pil->vet[topo-2];

				pil->vet[topo-1] = pil->vet[topo-2] = NULL;
				topo = topo - 2;
				pil->n_elem = pil->n_elem - 2;
		}
	}	
	(*ap_a) = pil->vet[0];
}

void imprimePrefixa(Arvore arv, int primeiro){
	if(arv == NULL){
		return;
	}else{
		if(arv->esq == NULL && arv->dir == NULL){
			if(primeiro){
				printf("%d", arv->valor);
			} else{
				printf(" %d", arv->valor);
			}
		} else{
			if(primeiro){
				printf("%c", arv->valor);
			} else{
				printf(" %c", arv->valor);
			}
		}
		imprimePrefixa(arv->esq, 0);
		imprimePrefixa(arv->dir, 0);
	}
}

void imprimePosfixa(Arvore arv, int* primeiro){
	if(arv == NULL){
		return;
	}else{
		imprimePosfixa(arv->esq, primeiro);
		imprimePosfixa(arv->dir, primeiro);

		if(*primeiro)
			*primeiro = 0;
		else
			printf(" ");
		if(arv->esq == NULL && arv->dir == NULL){
			printf("%d", arv->valor);
		} else{
			printf("%c", arv->valor);
		}
	}
}

void imprime(Arvore arv){
	imprimePrefixa(arv, 1);
	printf("\n");
	int primeiro = 1;
	imprimePosfixa(arv, &primeiro);
	printf("\n");
}

int calcula(Arvore arv){
	if(arv->esq == NULL && arv->dir == NULL){
		return arv->valor;
	}else{
		if(arv->valor == '+'){
			return calcula(arv->esq) + calcula(arv->dir);
		} else if(arv->valor == '*'){
			return calcula(arv->esq) * calcula(arv->dir);
		} else if(arv->valor == '/'){
			return calcula(arv->esq) / calcula(arv->dir);
		} else if(arv->valor == '-'){
			return calcula(arv->esq) - calcula(arv->dir);
		} else if(arv->valor == '%'){
			return calcula(arv->esq) % calcula(arv->dir);
		}
	}
}

int main(){
	Pilha pil;
	int num, cod_op, count = 0;
	int vet[20];
	char operador[2];
	Arvore arv = NULL;

	scanf("%d ", &num);
	//printf("%d", num);
	//inserePilha(&pil, num);
	vet[count++] = num;
	while(scanf("%s %d", operador, &num) == 2){
		//printf("%s", operador);
		//printf("%d", num);
		//inserePilha(&pil, num);
		cod_op = operador[0];
		//inserePilha(&pil, cod_op);
		vet[count++] = cod_op;
		vet[count] = num;
		count++;
	}

		iniciaPilha(&pil, count);
	criaArvore(&pil, &arv, vet);

	imprime(arv);
	int resultado = calcula(arv);
	printf("%d\n", resultado);
	/*for(int i = 0; i < count; i++){
		printf("%d, ", vet[i]);
	}*/
}
