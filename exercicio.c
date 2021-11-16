#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tipoAluno{
	int ra;
	char nome[30];
	float n1, n2, n3 ,n4;
	float media;
	
}tipoAluno;

typedef struct tipoNo{
	tipoAluno dado;
	struct tipoNo *prox;
}tipoNo;

typedef struct tipoLista{
	tipoNo *prim;
}tipoLista;

void criaLista(tipoLista *pLista){
	pLista->prim = NULL;
	
}

float media(tipoLista *pLista){
	tipoNo *aux;
	int cont = 0;
	float soma = 0;
	aux = pLista->prim;
	
	while(aux != NULL){
		soma = soma + aux->dado.media;
		cont++;
		aux = aux->prox;
	}
	if(cont>0){
		soma = soma/cont;
	}
	return soma;
}

void insereElementoLista(tipoLista *pLista, tipoAluno *al){
	tipoNo *aux;
	aux = (tipoNo *) malloc(sizeof(tipoNo));
	aux->dado = *al;
	aux->prox = pLista->prim;
	pLista->prim = aux;
}

void mostraAluno(tipoAluno al){
	printf("\n\n\tALUNO");
	printf("\n\tRA: %d", al.ra);
	printf("\n\tNome: %s", al.nome);
	printf("\n\tNota 1: %.2f", al.n1);
	printf("\n\tNota 2: %.2f", al.n2);
	printf("\n\tNota 3: %.2f", al.n3);
	printf("\n\tNota 4: %.2f", al.n4);
	al.media = (al.n1 + al.n2 + al.n3 + al.n4)/4;
	printf("\n\tMedia: %.2f", al.media);
	printf("\n-------------------------------------");
}

tipoAluno *buscaElementoNaLista(tipoLista *pLista, int ra){
	tipoNo *aux;
	
	aux = pLista->prim;
	
	while(aux){
		if( ra == aux->dado.ra){
			return &(aux->dado);
		}
		aux = aux -> prox;
	}
	return NULL;
}

int removeElementoDaLista(tipoLista *pLista, int raT){
	tipoNo *aux, *pont;
	if(pLista->prim){
		if(raT == pLista->prim->dado.ra){
			pont = pLista->prim;
			pLista->prim = pont->prox;
			free(pont);
			return 1;
		}
		aux = pLista->prim;
		while(aux->prox){
			if(raT == aux->prox->dado.ra){
				pont = aux->prox;
				aux->prox = pont->prox;  
				free(pont);
				return 1;
			}			
			aux = aux -> prox;
		}
	}
return 0;
}

void mostraLista(tipoLista *pLista){
	tipoNo *aux;
	
	aux = pLista->prim;
	
	while(aux != NULL){
		mostraAluno(aux->dado);
		aux = aux -> prox;
	}	
}



int main(){
	
	tipoAluno aluno;
	tipoAluno *pontAluno;
	int rem;
	int raP;
	tipoLista l;
	int opcao;
	int proc;
	float m;
	
	criaLista(&l);
	
	do{
		printf("\n1 - Cadastrar Aluno\n2 - Listar Alunos\n3 - Buscar Aluno pelo RA\n4 - Remover Aluno pelo RA\n5 - Exibir Media da Turma\n6 - Sair\nOpcao: ");
		scanf("%d", &opcao);
		
		switch(opcao){
			case 1:
				printf("\n\nRA: ");
				scanf("%d", &aluno.ra);
				getchar();
				printf("\nNome: ");
				gets(aluno.nome);
				printf("\nNota 1: ");
				scanf("%f", &aluno.n1);
				
				printf("\nNota 2: ");
				scanf("%f", &aluno.n2);
				
				printf("\nNota 3: ");
				scanf("%f", &aluno.n3);
				
				printf("\nNota 4: ");
				scanf("%f", &aluno.n4);
	
				aluno.media = (aluno.n1 + aluno.n2 + aluno.n3 + aluno.n4)/4;
				insereElementoLista(&l, &aluno);
				
				break;
			case 2:
				mostraLista(&l);
				break;
			case 3:
				printf("\nInsira o RA a ser buscado: ");
				scanf("%d", &raP);
				pontAluno = buscaElementoNaLista(&l, raP);
					if(pontAluno != NULL){
						printf("\nEncontrando na Lista: ");
						mostraAluno(*pontAluno);
					}else{
						printf("\nNao encontrou!\n\n");
					}		
				//buscar pelo ra
				//informar 4 notas e media do aluno
				break;
			case 4:
				printf("\nInsira o RA a ser removido: ");
				scanf("%d", &proc);
				removeElementoDaLista(&l, proc);
				if(rem){
					printf("\nElemento removido com sucesso!");
				}else{
					printf("\nElemento nao encontrado!");
				}
				break;
			case 5:
				m = media(&l);
				printf("\mMedia da turma: %.2f\n", m);
				printf("\n-------------------------");
				//exibir media da turma
				break;
			case 6:
				//sair
				break;
			default:
				if(opcao != 6){
					printf("\nOpcao invalida! Escolha outra.");
				}
		}
	}while(opcao != 6);
	
	return 0;
	
}


