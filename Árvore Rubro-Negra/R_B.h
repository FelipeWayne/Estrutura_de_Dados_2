/*UNIVERSIDADE FEDERAL DA FRONTEIRA SUL
 PROFESSOR: RICARDO PARIZOTTO
 MATÉRIA: ESTRUTURA DE DADOS II
 ALUNO: FELIPE AUGUSTO DA SILVA
 EMAIL: felipeaugustosilva94@gmail.com
 DESENVOLVIDO NO AMBIENTE LINUX */


/*TRABALHO 1 - RED/BLACK TREE */

#include <stdio.h>
#include <stdlib.h>

typedef struct  RNnodo RNtree;

struct RNnodo {
  int key;
  int red; /* se red=0 então o nodo é preto */
  struct RNnodo* esq;
  struct RNnodo* dir;
  struct RNnodo* pai;
};

// declarar o nodo NULL (sentinela)
static RNtree* NodoNULL = NULL;



// Definições das Funções
RNtree* Insere(RNtree* t, int key);
int Consulta(int X, RNtree* T );
RNtree* Remove(RNtree* t, int key);
void Destroi(RNtree* t);

// Funções Auxiliares
RNtree* VerificaRN(RNtree* t, int key);
RNtree* RotacaoDuplaDir( RNtree* t );
RNtree* RotacaoDuplaEsq( RNtree* t );
RNtree* RotacaoSimplesEsq(RNtree* t);
RNtree* RotacaoSimplesDir(RNtree* t);
void Desenha(RNtree* t , int nivel);
RNtree* Maior(RNtree* t);
RNtree* Menor(RNtree* t);
