#include <stdio.h>
#include <stdlib.h>

int quantidadeDeLinhasArquivo(char *arquivo);
int find_previous_prime(int num);
int acharProximoPrimo(int num);
int is_prime(int num);
void hashDuplo2(int num, int vetor[], int tamanho);
int insereNoVetor(int vetor[], int posicao, int num);

int main(void) {
	int i; 
    int tamanhoDoVetor = quantidadeDeLinhasArquivo("1000.txt");
    tamanhoDoVetor = acharProximoPrimo(1.5 * tamanhoDoVetor);
    int vetor[tamanhoDoVetor];

    for(i = 0; i < tamanhoDoVetor; i++){
      vetor[i] = -1;
    }

    FILE *arquivo = fopen("1000.txt", "r");
    int valor, z = 0;

    while(fscanf(arquivo, "%d", &valor) == 1){
    	hashDuplo2(valor, vetor, tamanhoDoVetor);
      printf("[%d] %d\n", z, valor);
      z++;
    }


    printf("Valores no vetor:\n");
    	for (i = 0; i < tamanhoDoVetor; i++) {
        	if (vetor[i] != -1) {
            	printf("%d ", vetor[i]);
          	}
        }
        printf("\n");

 	fclose(arquivo);
	return 0; 
}

int quantidadeDeLinhasArquivo(char *arquivo) {
  FILE *file = fopen(arquivo, "r");

  int contador = 0;
  int valor;

  while (fscanf(file, "%d", &valor) == 1) {
    contador++;
  }

  fclose(file);

  return contador;
}

int insereNoVetor(int vetor[], int posicao, int num) {
  if (vetor[posicao] == -1) {
    vetor[posicao] = num;
    return 1;
  }
  return 0;
}

void hashDuplo2(int num, int vetor[], int tamanho) {
  int ondeParou, primoAnterior;

  int posicao = num % tamanho;

  if (insereNoVetor(vetor, posicao, num)) {
    return;
  } else {
    primoAnterior = find_previous_prime(num);
    posicao = primoAnterior - (num % primoAnterior);
    
    while (posicao) {
      if (posicao < 0) {
        primoAnterior = find_previous_prime(tamanho);
        posicao = primoAnterior - (num % primoAnterior);
        ondeParou = primoAnterior;
        if (insereNoVetor(vetor, posicao, num)) {
            return;
        }

        while (posicao > 0) {
          if (insereNoVetor(vetor, posicao, num)) {
            return;
          }

          primoAnterior = find_previous_prime(ondeParou);
          posicao = primoAnterior - (num % primoAnterior);
          ondeParou = primoAnterior;
        }
      } else {
        if (insereNoVetor(vetor, posicao, num)) {
          return;
        }
        primoAnterior = find_previous_prime(num);
        posicao = primoAnterior - (num % primoAnterior);
      }
    }
  }
}

int is_prime(int num) {
  int i;

  if (num <= 1) {
    return 0;
  }
  for (i = 2; i * i <= num; i++) {
    if (num % i == 0) {
      return 0;
    }
  }
  return 1;
}

int find_previous_prime(int num) {
  if (num <= 2) {
    return -1; // Não há primos anteriores a 2
  }
  num--;
  while (num >= 2) {
    if (is_prime(num)) {
      return num;
    }
    num--;
  }
  return -1; // Não foi encontrado nenhum primo anterior
}

int acharProximoPrimo(int num) {
  num++;

  while (!is_prime(num)) {
    num++;
  }

  return num;
}
