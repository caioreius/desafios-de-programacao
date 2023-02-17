#include <stdio.h>
#include <string.h>

#define DEBUG(x) x
int main()
{
    char linha[20];
    int cmp,  // competidor
        prb,  // problema
        tmp;  // tempo
    char msg; // mensagem

    int nComp;
    int fim;
    int i;
    scanf("%d\n", &nComp);
    DEBUG(printf("nComp = %d\n", nComp);)

    while (nComp)
    {
        fim = 0;

        // Leitura de uma competicao
        DEBUG(printf("Leitura de competicao\n");)
        while (!fim && fgets(linha, 20, stdin))
        {
            sscanf(linha, "%d %d %d %c", &cmp, &prb, &tmp, &msg);
            DEBUG(printf("C = %d, P = %d, T = %d, M = %c\n", cmp, prb, tmp, msg);)
            if (linha[0] == 10 || linha[0] == 13)
                fim = 1;
        }

        nComp--;
    }
}
