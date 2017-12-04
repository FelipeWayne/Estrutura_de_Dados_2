/*UNIVERSIDADE FEDERAL DA FRONTEIRA SUL
 PROFESSOR: RICARDO PARIZOTTO
 MATÉRIA: ESTRUTURA DE DADOS II
 ALUNO: FELIPE AUGUSTO DA SILVA
 EMAIL: felipeaugustosilva94@gmail.com
 DESENVOLVIDO NO AMBIENTE LINUX */


/* Regras:
- No Máximo (2*T) filhos
- Minimo de T filhos
- Chaves no Máximo (2*T -1)chaves. (valores que podem ser inseridos em cada filho)
- Chaves no Minimo (T-1)chaves
- Nó interno com K filhos possui K-1 elementos ex:(se ele tem 4 filhos, cada filho possui no máx 3 chaves)
*/


#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "time.h"

typedef struct _nodo {
    int *key;//ponteiro para as chaves do nodo
    struct _nodo **pFilhos;//ponteiro para os filhos dos nodos
    int num_key;//numero de chaves que existe em cada nodo
    bool folha;//booleana que verifica se o nodo é folha(se for == true é folha)
}TpNodo;

typedef struct _arvore{ // estrutura da árvore.
    struct _nodo *pRaiz; // ponteiro para raiz.
}TpArvore;


/* Funções -------------------------------------------------------------------*/
int verifica_T(int T);
TpArvore *inicializa();
TpNodo *inserir(TpNodo *nodo, int chave, int T);
TpNodo *criaNodo(int chave, int T);
void imprime(TpNodo *nodo);
TpNodo *bubbleSort(TpNodo *nodo, int tam);
TpNodo *copia(TpNodo *nodo, int n);
int pesquisaChave(TpNodo *x, int k, int ver);
TpNodo *split(TpNodo *nodo, int chave, int T);
TpNodo *insereChave(TpNodo *nodo, int chave);
TpNodo *splitNodo(TpNodo *nodo, int chave, int filho, int T);
/* Funções -------------------------------------------------------------------*/


int main() {
    int opc, T = 0, chave, i;

    TpArvore *arvore = (TpArvore*) malloc(sizeof(TpArvore));
    arvore = inicializa();

    printf("Digite o valor de T: ");
    scanf("%d", &T);

    T = verifica_T(T);

    while(1) {
        // printf("\n(1) Inserção de um novo elemento\n(2) Listagem dos valores\n(0) Sair\n(99) Insercao Automatica\n--> ");

        printf("\n        Menu Principal\n\n");

        printf("1 - Inserir elemento na Arvore\n" );
        printf("2 - Inserir elementos aleatorios\n" );
        printf("3 - Imprimir elementos da Arvore\n" );
        printf("0 - Para finalizar o programa\n" );
        scanf("%d", &opc);

        switch (opc) {
            case 1:
                system("clear");
                printf("Valor da chave:");
                scanf("%d", &chave);

                if(arvore->pRaiz == NULL) {
                    arvore->pRaiz = inserir(arvore->pRaiz, chave, T);
                    arvore->pRaiz = bubbleSort(arvore->pRaiz, arvore->pRaiz->num_key);
                    imprime(arvore->pRaiz);
                    printf("\n");
                }

                else if(pesquisaChave(arvore->pRaiz, chave, 0) == 1 && pesquisaChave(arvore->pRaiz, chave, 1) == 1) {
                    arvore->pRaiz = inserir(arvore->pRaiz, chave, T);
                    arvore->pRaiz = bubbleSort(arvore->pRaiz, arvore->pRaiz->num_key);
                    imprime(arvore->pRaiz);
                    printf("\n");
                }
                else printf("Chave ja inserida\n\n");
                break;

            case 3:
                system("clear");
                imprime(arvore->pRaiz);
                break;

            case 0:
                return 0;
                break;

            case 2: //pra nao ficar digitando sempre
                system("clear");

                srand(time(NULL));
                for(i = 0; i < 2*T; i++) {
                    int aux = rand() %50;
               //     printf("AUX: %d\n", aux);
                    arvore->pRaiz = inserir(arvore->pRaiz, aux, T);
                    arvore->pRaiz = bubbleSort(arvore->pRaiz, arvore->pRaiz->num_key);
                }
                imprime(arvore->pRaiz);
                printf("\n");

                break;
            default:
                system("clear");
                printf("Opcao Incorreta\n\n");
        }
    }
}

int pesquisaChave(TpNodo *nodo, int k, int ver) { //pesquisa se a chave ja foi inserida
    if(nodo == NULL) return 1;

    TpNodo *x = nodo;
    int i = 0;

    while(i < x->num_key && k > x->key[i]) {
        i++;
    }

    if(i < x->num_key && k == x->key[i]) {
        return 0;
    }
    if(x->folha == true) return 1;

    return pesquisaChave(x->pFilhos[ver], k, ver);
}

TpNodo *criaNodo(int chave, int T) { //cria os nós da árvore
    TpNodo *nodo = (TpNodo*) malloc(sizeof(TpNodo));
    nodo->key = (int*) malloc(sizeof(int) * (2*T-1)); //aloca memória para o ponteiro key
    nodo->pFilhos = (TpNodo**) malloc(sizeof(TpNodo) * (2*T)); //aloca memoria para os filhos

    if(nodo == NULL) exit (1); //caso haja problema de alocacao
    int i;

    nodo->num_key = 0;
    nodo->key[nodo->num_key] = chave;
    nodo->num_key++; //1 chave inserida
    nodo->pFilhos = NULL;
    nodo->folha = true;

    nodo->pFilhos = (TpNodo**) malloc(sizeof(TpNodo*) * (2*T)); //aloca memoria para os filhos

     for(i = 0; i < 2*T; i++) nodo->pFilhos[i] = NULL;

    return nodo;
}

TpNodo *copia(TpNodo *nodo, int n) { //apenas copia o valor n para nodo
    TpNodo *aux = nodo;

    aux->key[aux->num_key] = n;
    aux->num_key++;
    return aux;
}

TpNodo *split(TpNodo *nodo, int chave, int T) { //faz o split quando o nó esta cheio
    TpNodo *aux = nodo;

    int mediana = aux->num_key / 2, i;

    TpNodo *pai = criaNodo(aux->key[mediana], T); //nodo com a chave mediana que será o pai
    pai->folha = false;

    TpNodo *esq_Pai = criaNodo(0, T); //ira receber todos os nodos antes do valor que esta na mediana
    TpNodo *dir_Pai = criaNodo(0, T); //ira receber todos os nodos depois do valor que esta na mediana

    esq_Pai->num_key -= 1; //ajuste
    dir_Pai->num_key -= 1;

    for(i = 0; i < mediana; i++) esq_Pai = copia(esq_Pai, aux->key[i]);
    for(i = mediana + 1; i < aux->num_key; i++) dir_Pai = copia(dir_Pai, aux->key[i]);

    /*Procura onde inserir a chave*/
    if(chave < aux->key[mediana]) { //chave sera inserida a esq do pai
        esq_Pai = insereChave(esq_Pai, chave);
    }
    else dir_Pai = insereChave(dir_Pai, chave);

    /* agora precisa ligar os nodos esq, dir e pai*/
    pai->pFilhos[1] = dir_Pai; //essa parte funcionou nao sei como, obrigado professor!
    pai->pFilhos[0] = esq_Pai;
    return pai;
}

TpNodo *insereChave(TpNodo *nodo, int chave) { //auxilia na inserção
    nodo->key[nodo->num_key] = chave;
    nodo->num_key++;
    nodo = bubbleSort(nodo, nodo->num_key);
    return nodo;
}

TpNodo *inserir(TpNodo *nodo, int chave, int T) { //insere as chaves na árvore (recebe a raiz da árvore)
    if(nodo == NULL) { //não possui nenhum nodo, é inserido na raiz
        return criaNodo(chave, T);
    }

    //quando ja possui a raiz é executado o restante
    TpNodo *aux = nodo;

    if(aux->folha == true) { //o nodo é folha, insere nas folhas
        if(aux->num_key < ((2*T) -1)) { //o nodo não esta cheio
            aux = insereChave(aux, chave);
            return aux;
        }
        else { //o nodo esta cheio e é folha, precisa fazer split
            aux = split(aux, chave, T); //faz a divisao retornando a raiz com os nós
            return aux;
        }
    }

    else { //o nodo não é folha, precisa procurar onde inserir



        if(aux->num_key <= 1) { //uma unica chave inserida
            //está ok dentro desse IF, sem necessidade de alterar
            if(chave < aux->key[0] && aux->pFilhos[0]->num_key < ((2*T) -1)) { //adiciona no filho a esquerda
                aux->pFilhos[0] = insereChave(aux->pFilhos[0], chave);
                return aux;
            }

            else if(chave < aux->key[0] && aux->pFilhos[0]->num_key >= ((2*T) -1)){ //se tiver cheio
                TpNodo *raiz;

                raiz = split(aux->pFilhos[0], chave, T);
                raiz->key[raiz->num_key] = aux->key[0];
                raiz->pFilhos[2] = aux->pFilhos[1];
                raiz->num_key++;

                return raiz;
            }

            else if(chave > aux->key[0] && aux->pFilhos[1]->num_key < ((2*T) -1)){ //adiciona no filho a direita
                aux->pFilhos[1] = insereChave(aux->pFilhos[1], chave);
                return aux;
            }
            else if(chave > aux->key[0] && aux->pFilhos[1]->num_key >= ((2*T) -1)){ //se tiver cheio
                TpNodo *raiz, *troca;

                troca = split(aux->pFilhos[1], chave, T);
                raiz->key[0] = aux->key[0];
                raiz->key[1] = troca->key[0];
                raiz->num_key = 2;
                raiz->pFilhos[0] = aux->pFilhos[0];
                raiz->pFilhos[1] = troca->pFilhos[0];
                raiz->pFilhos[2] = troca->pFilhos[1];
                return raiz;
            }
        }
        else { //tem mais de uma chave
      		int j = 0;
      		while(chave > aux->key[j] && j < aux->num_key) j++; //encontra a posicao pra inserir

      		if(aux->pFilhos[j]->num_key < ((2*T) -1)) { //onde sera inserido esta cheio
      			aux->pFilhos[j] = insereChave(aux->pFilhos[j], chave);
        		return aux;
      		}

      		else return splitNodo(aux, chave, j, T);
      	}
        return nodo;
    }
}

TpNodo *splitNodo(TpNodo *nodo, int chave, int filho, int T) {
	int j = 0;
	TpNodo *troca;

	troca = split(nodo->pFilhos[filho], chave, T);

	nodo->key[nodo->num_key] = troca->key[0]; //recebe o novo valor na raiz
	nodo->num_key++;

 	free(nodo->pFilhos[filho]);

   	nodo->pFilhos[filho ] = troca->pFilhos[0];
   	while(nodo->pFilhos[j] != NULL) {
   		j++;
   	}
   	nodo->pFilhos[j] = troca->pFilhos[1];

   	j = 0;
   	while(nodo->pFilhos[j] != NULL) {
   		if(nodo->pFilhos[j]->key[0] > nodo->pFilhos[j+1]->key[0]) {
   			troca->pFilhos[0] = nodo->pFilhos[j];
   			nodo->pFilhos[j] = nodo->pFilhos[j+1];
   			nodo->pFilhos[j+1] = troca->pFilhos[0];
   		}
   		j++;
   		if(nodo->pFilhos[j+1] == NULL) break;
   	}
   	j = 1;
   	while(nodo->pFilhos[j] != NULL) {
   		if(nodo->pFilhos[j]->key[0] > nodo->pFilhos[j+1]->key[0]) {
   			troca->pFilhos[0] = nodo->pFilhos[j];
   			nodo->pFilhos[j] = nodo->pFilhos[j+1];
   			nodo->pFilhos[j+1] = troca->pFilhos[0];
   		}
   		j++;
   		if(nodo->pFilhos[j+1] == NULL) break;
   	}

	return nodo;
}

void imprime(TpNodo *nodo) { //imprime a árvore B
    if(nodo == NULL) {
        system("clear");
        printf("Arvore vazia\n");
    }
    else {
        int i;

        for (i = 0; i < nodo->num_key; i++) {
            printf("%d ", nodo->key[i]);
            if(nodo->folha == true) printf("-|Folha| ");
            else printf("-||raiz||\t");
        }
        if(nodo->folha == false) {
            printf("\n");
            for(int j = 0; nodo->pFilhos[j] != NULL;j++ ) {
                imprime(nodo->pFilhos[j]);
                printf("______");
            }
        }
    }
}

TpNodo *bubbleSort(TpNodo *nodo, int tam) { //ordenar a chave dos nodos
    int tr, i, troca;
    TpNodo *aux = nodo;

    do {
        tr = 0;
        for (i = 1; i < tam; i++) {
            if(aux->key[i-1] > aux->key[i]) {
                troca = aux->key[i-1];
                aux->key[i-1] = aux->key[i];
                aux->key[i] = troca;

                tr = 1;
            }
        }
    } while(tr);

    return aux; //retorna o nodo ordenado
}

TpArvore *inicializa() { //ira inicializar a arvore B
    TpArvore *arv = (TpArvore*) malloc(sizeof(TpArvore));

    if(arv == NULL) {
        printf("Falha na alocacao\n");
        exit(1);
    }
    arv->pRaiz = NULL;
    return arv;
}

int verifica_T(int T) { //verifica se T é valido
    while(1) {
        if(T < 2) {
            system("clear");
            printf("Digite um T valido (Minimo eh 2): ");
            scanf("%d", &T);
        }
        else return T;
    }
}
