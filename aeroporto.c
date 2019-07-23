/*
 * aeroporto.c
 *
 * Vinícius Chaves Nascimento
 * Rafael Sousa Aragão de Almeida
 *
 *
 */

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>




typedef struct dados{
	char nome[51], destino[51];
	unsigned int id;
}Dados;

typedef struct no{
	Dados info;
	struct no *prox;
}No;

typedef struct fila{
	unsigned int tamanho;
	No *inicio;
	No *fim;
}Fila;

Fila *inicializa (void){
	Fila *nova = (Fila *) malloc (sizeof (Fila));
	if (nova == NULL){
		printf ("Erro.\n");
		exit (1);
	}
	nova->inicio = NULL;
	nova->fim = NULL;
	nova->tamanho = 0;
	return nova;
}

int vazia (Fila *f){
	return (f->tamanho == 0);
}

Fila *insere (Fila *f, Dados info){
	No *novo = (No *) malloc (sizeof (No));
	novo->info = info;
	novo->prox = NULL;
	if (f->fim != NULL) f->fim->prox = novo;
	else f->inicio = novo;
	f->fim = novo;
	f->tamanho++;
	return f;
}

Dados retira (Fila *f){
	No *aux;
	Dados valor;
	if (vazia (f)) {
		printf("Fila vazia. \n");
		exit (1);
	}
	aux = f->inicio;
	valor = aux->info;
	f->inicio = aux->prox;
	f->tamanho--;
	if (f->inicio == NULL)
		f->fim = NULL;
	free(aux);
	return valor;
}

void imprime (Fila *f){
	No *aux = f->inicio;
	unsigned int i=1;
	while (aux != NULL){
		printf ("\n%d\nNome: %sDestino: %sId: %d\n", i, aux->info.nome, aux->info.destino, aux->info.id);
		aux = aux->prox;
		i++;
	}
}

void imprimeInicio (Fila *f){
	No *aux = f->inicio;
	printf ("\nNome: %sDestino: %sId: %d\n", aux->info.nome, aux->info.destino, aux->info.id);
}

int main (void){
	Fila *f = NULL;
	char id[31];
	Dados aux1, aux2;
	f = inicializa ();
	int comando = 0;
    do{
		printf ("AEROPORTO\n\nDigite o número correspondente à opção desejada.\n\n");
		printf ("1 - Listar o número de  aviões na fila de espera.\n");
		printf ("2 - Autorizar a decolagem do primeiro da fila de espera.\n");
		printf ("3 - Adicionar um avião à fila de espera.\n");
		printf ("4 - Listar os aviões da fila de espera.\n");
		printf ("5 - Listar as características do primeiro avião da fila de espera.\n");
		printf ("0 - Sair.\n\nOpção: ");
		scanf ("%d", &comando);
		switch (comando){
			case 1:
				if (!vazia (f)) printf ("\nExistem %d aviões na fila de espera.\n", f->tamanho);
				else printf ("\nNão existem aviões na fila de espera.\n");
				break;
			case 2:
				if (!vazia (f)){
					aux1 = retira (f);
					printf ("\nDecolagem do avião %s %d com destino a %s autorizada.\n", aux1.nome, aux1.id, aux1.destino);
				}
				else printf ("\nNão existem aviões na fila de espera.\n");
				break;
			case 3:
				printf ("\nPreencha as informações do avião.\n");
				printf ("Nome: ");
				__fpurge (stdin);
				fgets (aux2.nome,51,stdin);
				printf ("Destino: ");
				__fpurge (stdin);
				fgets (aux2.destino,51,stdin);
				printf ("Id: ");
				__fpurge (stdin);
				fgets (id,31,stdin);
				aux2.id = atoi (id);
				f  = insere (f,aux2);
				break;
			case 4:
				if (!vazia (f)) imprime (f);
				else printf ("\nNão existem aviões na fila de espera.\n");
				break;
			case 5:
				if (!vazia (f)) imprimeInicio (f);
				else printf ("\nNão existem aviões na fila de espera.\n");
				break;
			case 0:
				printf ("\nEncerrando programa...\n");
				break;
			default:
				printf ("\nOpção inválida.\n");
		}
    }while(comando != 0);
    return 0;
}
