#include "calculadora.h"

int main() {
    char expr[MAXLEN];

    printf("Digite a expressao pos-fixada: ");
    fgets(expr, MAXLEN, stdin);

    // Remove a nova linha do final da string
    expr[strcspn(expr, "\n")] = '\0';

    printf("Avaliando: %s\n", expr);
    avaliaPosfixada(expr);

    return 0;
}

