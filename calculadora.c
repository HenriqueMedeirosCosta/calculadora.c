#include "calculadora.h"

// Inicializa a pilha
void inicializaPilha(Pilha *p) {
    p->topo = -1;
}

// Inicializa a pilha de strings
void inicializaPilhaStrings(PilhaStrings *p) {
    p->topo = -1;
}

// Verifica se a pilha está cheia
int estaCheia(Pilha *p) {
    return p->topo == MAXPILHA - 1;
}

// Verifica se a pilha de strings está cheia
int estaCheiaStrings(PilhaStrings *p) {
    return p->topo == MAXPILHA - 1;
}

// Verifica se a pilha está vazia
int estaVazia(Pilha *p) {
    return p->topo == -1;
}

// Verifica se a pilha de strings está vazia
int estaVaziaStrings(PilhaStrings *p) {
    return p->topo == -1;
}

// Empilha um item na pilha
void empilha(Pilha *p, double valor) {
    if (!estaCheia(p)) {
        p->itens[++(p->topo)] = valor;
    } else {
        printf("Pilha cheia\n");
    }
}

// Empilha uma string na pilha de strings
void empilhaStrings(PilhaStrings *p, char *valor) {
    if (!estaCheiaStrings(p)) {
        p->itens[++(p->topo)] = valor;
    } else {
        printf("Pilha de strings cheia\n");
    }
}

// Desempilha um item da pilha
double desempilha(Pilha *p) {
    if (!estaVazia(p)) {
        return p->itens[(p->topo)--];
    } else {
        printf("Pilha vazia\n");
        return 0.0;
    }
}

// Desempilha uma string da pilha de strings
char *desempilhaStrings(PilhaStrings *p) {
    if (!estaVaziaStrings(p)) {
        return p->itens[(p->topo)--];
    } else {
        printf("Pilha de strings vazia\n");
        return NULL;
    }
}

// Realiza as operações
void realizaOperacao(Pilha *p, PilhaStrings *ps, char *op) {
    double a, b;
    char *sa, *sb, *res = malloc(MAXLEN * sizeof(char));
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0 || strcmp(op, "*") == 0 || strcmp(op, "/") == 0 || strcmp(op, "^") == 0) {
        b = desempilha(p);
        a = desempilha(p);
        sb = desempilhaStrings(ps);
        sa = desempilhaStrings(ps);
        snprintf(res, MAXLEN, "(%s %s %s)", sa, op, sb);
        empilha(p, (strcmp(op, "+") == 0) ? (a + b) : (strcmp(op, "-") == 0) ? (a - b) : (strcmp(op, "*") == 0) ? (a * b) : (strcmp(op, "/") == 0) ? (a / b) : pow(a, b));
    } else if (strcmp(op, "log") == 0) {
        a = desempilha(p);
        sa = desempilhaStrings(ps);
        snprintf(res, MAXLEN, "log(%s)", sa);
        empilha(p, log10(a));
    } else if (strcmp(op, "sen") == 0) {
        a = desempilha(p);
        sa = desempilhaStrings(ps);
        snprintf(res, MAXLEN, "sen(%s)", sa);
        empilha(p, sin(a * M_PI / 180.0)); // convertendo para radianos
    } else if (strcmp(op, "cos") == 0) {
        a = desempilha(p);
        sa = desempilhaStrings(ps);
        snprintf(res, MAXLEN, "cos(%s)", sa);
        empilha(p, cos(a * M_PI / 180.0)); // convertendo para radianos
    } else {
        printf("Operacao desconhecida: %s\n", op);
        free(res);
        return;
    }
    empilhaStrings(ps, res);
}

// Avalia a expressão pós-fixada
void avaliaPosfixada(char *expr) {
    Pilha pilha;
    PilhaStrings pilhaStrings;
    inicializaPilha(&pilha);
    inicializaPilhaStrings(&pilhaStrings);

    char *token = strtok(expr, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            empilha(&pilha, atof(token));
            char *numStr = malloc(MAXLEN * sizeof(char));
            snprintf(numStr, MAXLEN, "%s", token);
            empilhaStrings(&pilhaStrings, numStr);
        } else {
            realizaOperacao(&pilha, &pilhaStrings, token);
        }
        token = strtok(NULL, " ");
    }

    if (!estaVazia(&pilha)) {
        printf("Expressao infixa: %s\n", desempilhaStrings(&pilhaStrings));
        printf("Resultado: %f\n", desempilha(&pilha));
    } else {
        printf("Expressao invalida\n");
    }
}

