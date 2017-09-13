/*UNIVERSIDADE FEDERAL DA FRONTEIRA SUL
 PROFESSOR: RICARDO PARIZOTTO
 MATÉRIA: ESTRUTURA DE DADOS II
 ALUNO: FELIPE AUGUSTO DA SILVA
 EMAIL: felipeaugustosilva94@gmail.com
 DESENVOLVIDO NO AMBIENTE LINUX */


/*TRABALHO 1 - BINARY SEARCH TREE */

#include <stdlib.h>
#include <stdio.h>


//Declaração de estrutura da Arvore (BINARIA)
typedef struct nodo {
  int info;
  struct nodo *esquerda;
  struct nodo *direita;

} tp_nodo;

//Declaração de estrutura da Raiz da Arvore
typedef struct raiz_arvore {
  int nItens;
  tp_nodo *raiz;

} tp_raiz;


//Declaração de Funções
tp_nodo *push ( tp_nodo *raiz, tp_nodo *novo );
void insert( tp_raiz *raiz );
tp_nodo *search ( tp_nodo *raiz, int key );
void chama_busca ( tp_raiz *raiz );
void Menu_Secundario ( tp_raiz *raiz );
void inorder ( tp_nodo *raiz );
void preorder ( tp_nodo *raiz );
void posorder ( tp_nodo *raiz );
void chama_remocao ( tp_raiz *raiz );
tp_nodo *remocao ( tp_nodo *raiz, int key );
tp_nodo *menor_folha ( tp_nodo *sub_raiz );


//Função Principal
int main() {
  int n;

  //Alocando Dinaicamente Raiz da Arvore
  tp_raiz *raiz = ( tp_raiz* ) malloc(sizeof(tp_raiz));

  if(raiz == NULL) {
    printf("Memoria insufiente\n" );
    return 0;
  }

  raiz->nItens = 0;
  raiz->raiz = NULL;

  //Menu Principal
  while ( 1 ) {
    printf("\n        Menu Principal\n\n");

    printf("1 - Inserir elemento na Arvore\n" );
    printf("2 - Remover elemento da Arvore\n" );
    printf("3 - Imprimir elementos da Arvore\n" );
    printf("4 - Pesquisar elemento na Arvore\n" );
    printf("0 - Para finalizar o programa\n" );
    printf("Digite uma opção: ");
    scanf(" %d", &n );

    switch ( n ) {
      case 1:
        insert( raiz );
      break;

      case 2:
        chama_remocao ( raiz );
      break;

      case 3:
        Menu_Secundario ( raiz );
      break;

      case 4:
        chama_busca ( raiz );
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

//Menu Secundario
void Menu_Secundario ( tp_raiz *raiz ) {
  int n;

  printf("\n        Menu Secundario\n\n");

  printf("1 - In order\n" );
  printf("2 - Pre order\n" );
  printf("3 - Post order\n" );
  printf("0 - Menu Principal\n" );
  printf("Digite uma opção: ");
  scanf(" %d", &n );

  switch ( n ) {
    case 1:
      printf("\n\n" );
      inorder ( raiz->raiz );
    break;

    case 2:
      printf("\n\n" );
      preorder ( raiz->raiz );
    break;

    case 3:
      printf("\n\n" );
      posorder ( raiz->raiz );
    break;

    case 0:
      //Finaliza a função Menu_Secundario
      system("clear");
    break;

    default:
      printf("Opção Invalida\n");
    break;
  }

}

//Função para inserir elemento na arvore
void insert ( tp_raiz *raiz ) {
  tp_nodo *novo;
  static int aux = 0;

  //Alocando dinamicamente novo elemento
  novo = ( tp_nodo* ) malloc(sizeof(tp_nodo));

  if(novo == NULL) {
    printf("Memoria insufiente\n" );
    exit (1);
  }

  printf("\nValor a ser inserido: ");
  scanf(" %d", &novo->info);

  //Verificando se é o primeiro elemento a ser inserido ou não
  if( aux == 0 ) {

    raiz->raiz = push( raiz->raiz, novo );
    aux++;

  } else {

    push( raiz->raiz, novo );

  }

  raiz->nItens++;
  printf("\nElemento foi inserido com sucesso na Arvore\n\n" );

}


//Função de inserção elemento no lugar correto
tp_nodo *push ( tp_nodo *raiz, tp_nodo *novo) {

  //Verifica se é o primeiro elemento a ser inserido na Arvore
  if( raiz == NULL ) {

    //Se for o primeiro a ser inserido o define como raiz
    raiz = novo;
    novo->esquerda = NULL;
    novo->direita = NULL;

  } else {

    //Verifica se o elemento é maior ou menor que a raiz
    if( novo->info < raiz->info ) {

      raiz->esquerda = push( raiz->esquerda, novo );

    } else {

      raiz->direita = push( raiz->direita, novo );

    }

  }

  return raiz;
}


//Função chama busca
void chama_busca ( tp_raiz *raiz ) {
  int num;
  tp_nodo *busca;

  //Elemento a ser pesquisado na Arvore
  printf("\nInsira elemento para buscar: " );
  scanf(" %d", &num );

  //Faz a busca na Arvore
  busca = search( raiz->raiz, num );

  //Verifica se a Arvore possui o elemento e printa resultado
  if( busca != NULL ) {

    printf("\n\nElemento %d encontrado na Arvore\n", busca->info );
  } else {

    printf("\n\nElemento %d não encontrado na Arvore\n", num );
  }

}


//Função para pesquisar elemento na Arvore
tp_nodo *search ( tp_nodo *raiz, int key ) {

  //Verifica se a raiz é nula ou se a key é a propria raiz
  if( raiz == NULL || raiz->info == key ){

    return raiz;

  } else {

    //Verifica se a raiz é menor que key
    if( raiz->info < key ) {

      return search( raiz->direita, key );

    } else {
      //Se a raiz for maior que a key
      return search( raiz->esquerda, key );
    }

  }

}

//Função Imprime In order
void inorder ( tp_nodo *raiz ) {

  if( raiz != NULL ){

    inorder ( raiz->esquerda );

    printf("%d \n", raiz->info );

    inorder ( raiz->direita );

  }
}

//Função Imprime Pre order
void preorder ( tp_nodo *raiz ) {

  if( raiz != NULL ){

    printf("%d \n", raiz->info );

    preorder ( raiz->esquerda );

    preorder ( raiz->direita );

  }
}

//Função Imprime Pre order
void posorder ( tp_nodo *raiz ) {

  if( raiz != NULL ){

    posorder ( raiz->esquerda );

    posorder ( raiz->direita );

    printf("%d \n", raiz->info );

  }
}

//Função para chamar a Remoção
void chama_remocao ( tp_raiz *raiz ) {
  int num;

  //Elemento que deve ser removido da Arvore
  printf("\nInsira elemento para ser removido: " );
  scanf(" %d", &num );

  remocao( raiz->raiz, num );

}

//Função para Remover elemento da Arvore
tp_nodo *remocao ( tp_nodo *raiz, int key ) {

  //Verifica se Arvore não está vazia ou no fim
  if( raiz == NULL ) {

    return raiz;
  }

  //Verifica se a key é menor do que a raiz
  if( key < raiz->info ){

    raiz->esquerda = remocao( raiz->esquerda, key );

  } else {

    //Verifica se a Key é maior que a raiz
    if( key > raiz->info ){

      raiz->direita = remocao( raiz->direita, key );

    } else {

      //Verifica se raiz tem um ou nenhum filho
      if( raiz->esquerda == NULL ) {

        tp_nodo *temp = raiz->direita;
        free( raiz );

        return temp;

      } else {

        if( raiz->direita == NULL ) {

          tp_nodo *temp = raiz->esquerda;
          free( raiz );

          return temp;
        }
      }

      //Quando a raiz tem dois filhos: Busca o sucessor in order
      //na sub-Arvore a direita
      tp_nodo *temp = menor_folha( raiz->direita );

      //Copia o sucessor in order para esse node
      raiz->info = temp->info;

      //Remove sucessor in order
      raiz->direita = remocao( raiz->direita, temp->info );

    }

  }

  return raiz;
}


//Função que busca em uma Arvore não vazia o seu menor valor
tp_nodo *menor_folha ( tp_nodo *sub_raiz ) {
  tp_nodo *atual = sub_raiz;

  //Loop para baixo até encontrar a menor folha a esquerda
  while ( atual->esquerda != NULL ) {

    atual = atual->esquerda;
  }

  return atual;
}
