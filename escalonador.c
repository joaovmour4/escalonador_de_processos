#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

typedef struct{
	int id;
	char tipo;
	int prioridade_estatica;
	int prioridade_dinamica;
	int tempo;
}Processo;

typedef struct no{
	Processo processo;
	struct no *proximo;
}No;

void inserir_na_fila(No **fila, Processo processo);
void inserir_na_lista(No **lista, Processo processo);

void listar_prontos(No *no);
void listar_em_espera(No *no);

No *remover_da_fila(No **fila);
No *remover_da_lista(No **lista);

int tamanho(No *no);

void alterar_prioridades(No **lista, No **fila);

Processo criar_processo(char tipo, int tempo);

int main(){
	srand(time(NULL));
	No *exe, *r, *lista_prontos = NULL, *fila_de_espera = NULL;
	
	Processo p1 = criar_processo('C', 2);
	Processo p2 = criar_processo('I', 4);
	Processo p3 = criar_processo('C', 2);
	Processo p4 = criar_processo('I', 4);
	Processo p5 = criar_processo('C', 2);
	Processo p6 = criar_processo('I', 4);
	
	inserir_na_lista(&lista_prontos, p1);
	inserir_na_lista(&lista_prontos, p2);
	inserir_na_lista(&lista_prontos, p3);
	inserir_na_lista(&lista_prontos, p4);
	inserir_na_lista(&lista_prontos, p5);
	inserir_na_lista(&lista_prontos, p6);
	
	
	do{
		if(fila_de_espera && fila_de_espera->processo.tempo == 0){
			r = remover_da_fila(&fila_de_espera);
			if(r)
				inserir_na_lista(&lista_prontos, r->processo);
		}
			
		
		exe = remover_da_lista(&lista_prontos);

		alterar_prioridades(&lista_prontos, &fila_de_espera);

		printf("Em execucao: Processo [%i]\tTipo: %c\tPrioridade: %i\n\n", exe->processo.id, exe->processo.tipo, exe->processo.prioridade_dinamica);
		
		listar_prontos(lista_prontos);
		listar_em_espera(fila_de_espera);
				
		Sleep(200);
		system("cls");
		
		printf("Em execucao: Processo [ ]\tTipo: \n\n");
		
		if(exe->processo.tipo == 'I')
			inserir_na_fila(&fila_de_espera, exe->processo);
		else
			inserir_na_lista(&lista_prontos, exe->processo);
			
		listar_prontos(lista_prontos);
		listar_em_espera(fila_de_espera);
		

		Sleep(1000);
		system("cls");
		
	}while(1);
	
	return 0;
}


Processo criar_processo(char tipo, int tempo){
	Processo processo;
	processo.id = rand()%100;
	processo.tipo = tipo;
	processo.prioridade_estatica = 1 + (rand()%5);
	processo.prioridade_dinamica = processo.prioridade_estatica;
	processo.tempo = tempo;
	
	return processo;
}


void inserir_na_fila(No **fila, Processo processo){
	No *aux, *novo = malloc(sizeof(No));
	
	processo.tempo = 3;
	if(novo){
		novo->processo = processo;
		novo->proximo = NULL;
		if(*fila == NULL)
			*fila = novo;
		else{
			aux = *fila;
			while(aux->proximo)
				aux = aux->proximo;
			aux->proximo = novo;
		}
		
	}else{
		printf("\nErro na alocacao!\n");
	}
	
}

void inserir_na_lista(No **lista, Processo processo){
	No *aux, *novo = malloc(sizeof(No));
	processo.prioridade_dinamica = processo.prioridade_estatica; // Reseta a prioridade do processo
	
	if(novo){
		novo->processo = processo;
		if(*lista == NULL){
			novo->proximo = NULL;
			*lista = novo;
		}else if(novo->processo.prioridade_dinamica > (*lista)->processo.prioridade_dinamica){
			novo->proximo = *lista;
			*lista = novo;
		}else{
			aux = *lista;
			while(aux->proximo && novo->processo.prioridade_dinamica < aux->proximo->processo.prioridade_dinamica)
				aux = aux->proximo;
			novo->proximo = aux->proximo;
			aux->proximo = novo;
		}
	}else
		printf("Erro na alocacao!\n");
}

void listar_prontos(No *no){
	printf("\tProntos:\n");
	while(no){
		printf("\t\tProcesso [%i]\tTipo: %c\tPrioridade: %i\n", no->processo.id, no->processo.tipo, no->processo.prioridade_dinamica);
		no = no->proximo;
	}
}

void listar_em_espera(No *no){	
	printf("\n\n\n\tEm espera:\n");
	while(no){
		printf("\t\tProcesso [%i]\tTipo: %c\n", no->processo.id, no->processo.tipo);
		no = no->proximo;
	}
	printf("\n\n\n");
}

No *remover_da_fila(No **fila){
	No *remover = NULL;
	
	if(*fila){
		remover = *fila;
		*fila = remover->proximo;
	}
	return remover;	
}

No *remover_da_lista(No **lista){
	No *remover = NULL;
	
	if(*lista){
		remover = *lista;
		*lista = remover->proximo;
	}
	return remover;	
}

int tamanho(No *no){
	int len=0;
	while(no){
		len++;
		no = no->proximo;
	}
	return len;
}

void alterar_prioridades(No **lista, No **fila){
	No *aux = *lista, *aux1 = *fila;
	
	while(aux){
		aux->processo.prioridade_dinamica++;
		aux = aux->proximo;
	}
	
	while(aux1){
		if(aux1->processo.tempo != 0) // Se o tempo restante na fila não for 0, decresce um segundo de espera
			aux1->processo.tempo--;
		aux1 = aux1->proximo;
	}
}




