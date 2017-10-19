/*UNIVERSIDADE FEDERAL DA FRONTEIRA SUL
 PROFESSOR: RICARDO PARIZOTTO
 MATÉRIA: ESTRUTURA DE DADOS II
 ALUNO: FELIPE AUGUSTO DA SILVA
 EMAIL: felipeaugustosilva94@gmail.com
 DESENVOLVIDO NO AMBIENTE LINUX */


/*TRABALHO 1 - RED/BLACK TREE */

#include <stdio.h>
#include <stdlib.h>
#include "R_B.c"

RNtree* aleatorios(RNtree* arv );


int main(int argc, char *argv[]) {
	int n, num;
	RNtree* arv = NULL;

	//Menu Principal
  while ( 1 ) {
    printf("\n        Menu Principal\n\n");

		printf("1 - Inserir elemento na Arvore\n" );
    printf("2 - Inserir elementos aleatorios\n" );
    printf("3 - Remover elemento da Arvore\n" );
    printf("4 - Imprimir elementos da Arvore\n" );
    printf("5 - Pesquisar elemento na Arvore\n" );
    printf("0 - Para finalizar o programa\n" );
    printf("Digite uma opção: ");
    scanf(" %d", &n );

    switch ( n ) {
      case 1:
				printf("\n\nElemento que será inserido: ");
				scanf(" %d", &num );
        arv = Insere(arv,num);
				printf("\nElemento inserido com sucesso!\n\n" );
      break;

			case 2:
				arv = aleatorios( arv );
			break;

      case 3:
			printf("\n\nElemento que será removido: ");
			scanf(" %d", &num );
			arv = Remove(arv, num);
			printf("\nElemento removido com sucesso!\n\n" );

      break;

      case 4:
				Desenha(arv,0);
      break;

      case 5:
			printf("\n\nElemento que será pesquisado: ");
			scanf(" %d", &num );
			if( Consulta(num,arv) ) {
				printf("\nElemento %d encontrado na árvore\n", num );
			} else {
				printf("\nElemento %d não encontrado na árvore\n", num );
			}

      break;

      case 0:
        return 0;
      break;

      default:
        printf("Opção Invalida\n");
      break;
    }
  }

  return 0;
}


RNtree* aleatorios(RNtree* arv ) {
	int n, i, valor;

	printf("\nQuantos elementos deseja inserir: " );
	scanf(" %d", &n );

	for (i = 0; i < n; i++) {
		valor = (rand() % 100);
		printf(" %d", valor );
		arv = Insere(arv, valor);
	}
	printf("\n\n" );

	return arv;
}
