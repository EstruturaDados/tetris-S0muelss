

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// =======================================================
// Desafio Tetris Stack - Fila Circular + Pilha
// =======================================================

// ------------------------------
// Constantes
// ------------------------------
#define TAM_FILA 5   // Capacidade da fila circular
#define TAM_PILHA 3  // Capacidade da pilha

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

void inicializarPilha(Pilha *p);
bool pilhaCheia(Pilha *p);
bool pilhaVazia(Pilha *p);
void push(Pilha *p, Peca nova);
void pop(Pilha *p);
void mostrarPilha(Pilha *p);

Peca gerarPeca(int id);

void trocarTopoComFrente(Pilha *p, Fila *f);
void trocarMultiplos(Pilha *p, Fila *f);

// =======================================================
// Função principal
// =======================================================
int main() {
    Fila fila;
    Pilha pilha;
    int idAtual = 0;
    int opcao;

    srand(time(NULL));
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Preenche a fila inicial
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
        printf("3 - Usar peça reservada (remover da pilha)\n");
        printf("4 - Trocar peça da frente com topo da pilha\n");
        printf("5 - Trocar 3 primeiras da fila com 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (!filaVazia(&fila)) {
                    dequeue(&fila);
                    enqueue(&fila, gerarPeca(idAtual++));
                    printf("✅ Peça jogada com sucesso!\n");
                } else {
                    printf("⚠️  A fila está vazia!\n");
                }
                break;

            case 2:
                if (!filaVazia(&fila)) {
                    if (!pilhaCheia(&pilha)) {
                        Peca p = fila.itens[fila.frente];
                        dequeue(&fila);
                        push(&pilha, p);
                        enqueue(&fila, gerarPeca(idAtual++));
                        printf("✅ Peça %c%d movida para a reserva!\n", p.tipo, p.id);
                    } else {
                        printf("⚠️  A pilha está cheia!\n");
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

            case 4:
                trocarTopoComFrente(&pilha, &fila);
                break;

            case 5:
                trocarMultiplos(&pilha, &fila);
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

// =======================================================
// Geração e Trocas
// =======================================================
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.tipo = tipos[rand() % 4];
    p.id = id;
    return p;
}

// Troca simples: frente da fila ↔ topo da pilha
void trocarTopoComFrente(Pilha *p, Fila *f) {
    if (pilhaVazia(p)) {
        printf("⚠️  A pilha está vazia, não há peça para trocar!\n");
        return;
    }
    if (filaVazia(f)) {
        printf("⚠️  A fila está vazia, não há peça para trocar!\n");
        return;
    }

    int idxFrente = f->frente;
    Peca temp = p->itens[p->topo];
    p->itens[p->topo] = f->itens[idxFrente];
    f->itens[idxFrente] = temp;

    printf("🔄 Troca realizada entre topo da pilha e frente da fila!\n");
}

// Troca múltipla: 3 primeiras da fila ↔ 3 da pilha
void trocarMultiplos(Pilha *p, Fila *f) {
    if (p->topo < 2 || f->total < 3) {
        printf("⚠️  É necessário ter ao menos 3 peças em cada estrutura para a troca múltipla!\n");
        return;
    }

    for (int i = 0; i < 3; i++) {
        int idxFila = (f->frente + i) % TAM_FILA;
        Peca temp = p->itens[p->topo - i];
        p->itens[p->topo - i] = f->itens[idxFila];
        f->itens[idxFila] = temp;
    }

    printf("🔁 Troca múltipla realizada entre as 3 primeiras da fila e as 3 da pilha!\n");
}
