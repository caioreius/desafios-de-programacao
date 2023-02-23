#include <stdio.h>
#include <stdlib.h>
// scanf != EOF
int achaPosicao(int numero, int *linha, int *coluna)
{
    int circulo = 1, cont = 1, caminho, valorAtual;
    while (numero > circulo)
    {
        circulo += 6 * cont;
        cont++;
    }
    (*linha) = 0;
    (*coluna) = cont - 1;
    caminho = cont - 1;
    valorAtual = circulo;
    // printf("\nValorAtual:%d , circulo:%d\n",valorAtual, circulo);

    if (valorAtual == numero)
    {
        return 1;
    }
    // printf("\ncoluna:%d, linha:%d\n", (*coluna), (*linha));
    // sobe
    for (int i = 0; i < caminho; i++)
    {
        (*linha)--;
        valorAtual--;
        if (numero == valorAtual)
            return 1;
    }

    // sobe chapeu
    for (int i = 0; i < caminho; i++)
    {
        (*coluna)--;
        valorAtual--;
        if (numero == valorAtual)
            return 1;
    }

    // desce chapeu
    for (int i = 0; i < caminho; i++)
    {
        (*coluna)--;
        (*linha)++;
        valorAtual--;
        if (numero == valorAtual)
            return 1;
    }

    // desce
    for (int i = 0; i < caminho; i++)
    {
        (*linha)++;
        valorAtual--;
        if (numero == valorAtual)
            return 1;
    }

    for (int i = 0; i < caminho; i++)
    {
        (*coluna)++;
        valorAtual--;
        if (numero == valorAtual)
            return 1;
    }

    // sobe
    for (int i = 0; i < caminho - 1; i++)
    {
        (*coluna)++;
        (*linha)--;
        valorAtual--;
        if (numero == valorAtual)
            return 1;
    }
}

int main()
{
    int numero, linha = 0, coluna = 1;
    while (scanf("%d", &numero) != EOF)
    {
        achaPosicao(numero, &linha, &coluna);
        printf("%d %d\n", coluna, linha);
    };
}
