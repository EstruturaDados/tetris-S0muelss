

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// =======================================================
// Desafio Tetris Stack - Fila + Pilha
// =======================================================

#define TAM_FILA 5   // Capacidade da fila circular
#define TAM_PILHA 3  // Capacidade da pilha

// ------------------------------
// Estrutura da peça
// ------------------------------
typedef struct {
    char tipo; // Tipo ('I', 'O', 'T', 'L')
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
// Estrutura da pilha
// ------------------------------
typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

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

void inicializarPilha(Pilha *p);
bool pilhaCheia(Pilha *p);
bool pilhaVazia(Pilha *p);
void push(Pilha *p, Peca nova);
void pop(Pilha *p);
void mostrarPilha(Pilha *p);

// =======================================================
// Função principal
// =======================================================
int main() {
    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    srand(time(NULL));

    int idAtual = 0;
    int opcao;

    // Inicializa a fila com 5 peças automáticas
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(idAtual++));
    }

    do {
        printf("\n============================\n");
        printf("   ESTADO ATUAL DAS PEÇAS\n");
        printf("============================\n");
        mostrarFila(&fila);
        mostrarPilha(&pilha);

        printf("\nMenu de Ações:\n");
        printf("1 - Jogar peça (remover da frente da fila)\n");
        printf("2 - Reservar peça (mover da fila para pilha)\n");
        printf("3 - Usar peça reservada (remover do topo da pilha)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (!filaVazia(&fila)) {
                    dequeue(&fila);
                    enqueue(&fila, gerarPeca(idAtual++));
                } else {
                    printf("⚠️  A fila está vazia!\n");
                }
                break;

            case 2:
                if (!filaVazia(&fila)) {
                    if (!pilhaCheia(&pilha)) {
                        // Mover peça da frente da fila para a pilha
                        Peca p = fila.itens[fila.frente];
                        dequeue(&fila);
                        push(&pilha, p);
                        enqueue(&fila, gerarPeca(idAtual++));
                        printf("✅ Peça %c%d movida para a reserva!\n", p.tipo, p.id);
                    } else {
                        printf("⚠️  A pilha de reserva está cheia!\n");
                    }
                } else {
                    printf("⚠️  A fila está vazia!\n");
                }
                break;

            case 3:
                if (!pilhaVazia(&pilha)) {
                    Peca removida = pilha.itens[pilha.topo];
                    pop(&pilha);
                    printf("🧩 Peça %c%d usada e removida da reserva!\n", removida.tipo, removida.id);
                } else {
                    printf("⚠️  A pilha de reserva está vazia!\n");
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
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->total = 0;
}

bool filaCheia(Fila *f) {
    return f->total == TAM_FILA;
}

bool filaVazia(Fila *f) {
    return f->total == 0;
}

void enqueue(Fila *f, Peca nova) {
    if (filaCheia(f)) return;
    f->tras = (f->tras + 1) % TAM_FILA;
    f->itens[f->tras] = nova;
    f->total++;
}

void dequeue(Fila *f) {
    if (filaVazia(f)) return;
    f->frente = (f->frente + 1) % TAM_FILA;
    f->total--;
}

void mostrarFila(Fila *f) {
    printf("Fila de peças: ");
    if (filaVazia(f)) {
        printf("(vazia)\n");
        return;
    }
    int i, idx;
    for (i = 0, idx = f->frente; i < f->total; i++) {
        printf("[%c %d] ", f->itens[idx].tipo, f->itens[idx].id);
        idx = (idx + 1) % TAM_FILA;
    }
    printf("\n");
}

Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.tipo = tipos[rand() % 4];
    p.id = id;
    return p;
}

// =======================================================
// Implementação das Funções da Pilha
// =======================================================
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

bool pilhaCheia(Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

bool pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void push(Pilha *p, Peca nova) {
    if (pilhaCheia(p)) return;
    p->topo++;
    p->itens[p->topo] = nova;
}

void pop(Pilha *p) {
    if (pilhaVazia(p)) return;
    p->topo--;
}

void mostrarPilha(Pilha *p) {
    printf("Pilha de reserva (Topo -> Base): ");
    if (pilhaVazia(p)) {
        printf("(vazia)\n");
        return;
    }
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->itens[i].tipo, p->itens[i].id);
    }
    printf("\n");
}

