#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Definindo a estrutura da pilha
#define MAXPILHA 100
#define MAXLEN 100

typedef struct {
    int topo;
    double itens[MAXPILHA];
} Pilha;

typedef struct {
    int topo;
    char *itens[MAXPILHA];
} PilhaStrings;

// Inicializa a pilha
void inicializaPilha(Pilha *p);

void inicializaPilhaStrings(PilhaStrings *p);

int estaCheia(Pilha *p);

int estaCheiaStrings(PilhaStrings *p);

int estaVazia(Pilha *p);

int estaVaziaStrings(PilhaStrings *p);

void empilha(Pilha *p, double valor);

void empilhaStrings(PilhaStrings *p, char *valor);

double desempilha(Pilha *p);

char *desempilhaStrings(PilhaStrings *p);

void realizaOperacao(Pilha *p, PilhaStrings *ps, char *op);

void avaliaPosfixada(char *expr);

