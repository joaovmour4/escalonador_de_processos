#include <stdio.h>

typedef struct {
	int prioridade;
	int tempo; // Tempo de execucao
	char tipo[1]; // C = CPU / I = I/O
}Processo;

Processo novo_processo(int prioridade, int tempo, char tipo[1]);

void main(){
	int i, j, tamanho=5, aux=0, prioridade, estouro=0;
	Processo fila[5];
	
	fila[0] = novo_processo(1, 4, "C");
	fila[1] = novo_processo(2, 6, "I");
	fila[2] = novo_processo(1, 4, "C");
	fila[3] = novo_processo(3, 6, "C");
	fila[4] = novo_processo(2, 6, "I");
	
	while(estouro != 5){
		prioridade = 0;
		for(j=0; j<5; j++){
			if(fila[j].prioridade > prioridade && fila[j].tempo != 0 && aux != j){
				aux = j;
				prioridade = fila[aux].prioridade;
			}
		}
		printf("Executando processo [%i]...\n", aux);
		
		if(fila[aux].tempo >= 2){
			fila[aux].tempo-= 2;
			printf("Execucao concluida, tempo de execucao restante: %i\n\n", fila[aux].tempo);
		}else{
			fila[aux].tempo --;
		}
		
		if(fila[aux].tempo == 0){
			estouro++;
			printf("Processo [%i] concluido\n\n", aux);
		}	
	}
	
	printf("Nao ha mais processos em fila! Finalizando...\n");	
}


Processo novo_processo(int prioridade, int tempo, char tipo[1]){
	Processo processo;
	processo.tempo = tempo;
	processo.tipo[0] = tipo[0];
	if(tipo[0] == 'C'){
		processo.prioridade = prioridade * 3;
	}else{
		processo.prioridade = prioridade;
	}
	
	return processo;
}
