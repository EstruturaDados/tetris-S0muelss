

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// =======================================================
// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Nível Novato: Fila de Peças Futuras
// =======================================================

// ------------------------------
// Constantes
// ------------------------------
#define TAM_FILA 5  // Capacidade máxima da fila circular

// ------------------------------
// Estrutura da peça
// ------------------------------
typedef struct {
    char tipo; // Tipo da peça ('I', 'O', 'T', 'L')
    int id;    // Identificador único
} Peca;

// ------------------------------
// Estrutura da fila circular
// ------------------------------
typedef struct {
    Peca itens[TAM_FILA];
    int frente;
    int tras;
    int total;
} Fila;

// ------------------------------
// Protótipos das funções
// ------------------------------
void inicializarFila(Fila *f);
bool filaCheia(Fila *f);
bool filaVazia(Fila *f);
void enqueue(Fila *f, Peca nova);
void dequeue(Fila *f);
void mostrarFila(Fila *f);
Peca gerarPeca(int id);

// =======================================================
// Função principal
// =======================================================
int main() {
    Fila fila;
    inicializarFila(&fila);

    srand(time(NULL));
    int idAtual = 0;
    int opcao;

    // Inicializa a fila com 5 peças automáticas
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(idAtual++));
    }

    do {
        printf("\n=== Fila de Peças Futuras ===\n");
        mostrarFila(&fila);

        printf("\nMenu de Ações:\n");
        printf("1 - Jogar peça (remover da frente)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (!filaVazia(&fila)) {
                    dequeue(&fila);
                    enqueue(&fila, gerarPeca(idAtual++)); // repõe automaticamente
                } else {
                    printf("⚠️ A fila está vazia!\n");
                }
                break;
            case 0:
                printf("Encerrando o jogo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

// =======================================================
// Implementação das Funções da Fila
// =======================================================

// Inicializa os campos da fila
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->total = 0;
}

// Verifica se a fila está cheia
bool filaCheia(Fila *f) {
    return f->total == TAM_FILA;
}

// Ver


