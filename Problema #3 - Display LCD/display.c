// Equipe λ
#include <stdio.h>
#include <stdlib.h>

int draw(int direction, int lado, int fontSize)
{

    printf(" ");
    fontSize = fontSize + 2;
    for (int i = 0; i < fontSize; i++)
    {
        if (!direction)
        {
            if (i == 0 || i == fontSize - 1)
                printf(" ");
            else
                printf(lado ? "-" : " ");
        }
        else
        {
            int test[] = {!i, i == fontSize - 1, i == fontSize - 1 || i == 0};
            printf(test[lado] ? "|" : " ");    
        }
    }
}

void drawByLine(char *numero, int line, int fontSize, int direction)
{
    char tmp[2];
    int representation[10][5] = {
        {1, 2, 0, 2, 1},
        {0, 1, 0, 1, 0},
        {1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1},
        {0, 2, 1, 1, 0},
        {1, 0, 1, 1, 1},
        {0, 0, 1, 2, 1},
        {1, 1, 0, 1, 0},
        {1, 2, 1, 2, 1},
        {1, 2, 1, 1, 0}};

    for (char *s = numero; *s; s++)
    {
        sscanf(s, "%c", tmp);
        draw(direction, representation[atoi(tmp)][line], fontSize);
    }
    printf("\n");
}

int display(char *numero, int fontSize)
{
    for (int j = 0; j < 5; j++)
    {
        if (j == 1 || j == 3)
            for (int i = 0; i < fontSize; i++)
                drawByLine(numero, j, fontSize, 1);
        else
            drawByLine(numero, j, fontSize, 0);
    }
}

int main()
{
    char fontSize[2], number[9];
    scanf("%s %s", fontSize, number);
    while (atoi(fontSize) && atoi(number))
    {
        display(number, atoi(fontSize));
        scanf("%s %s", fontSize, number);
    }
}
