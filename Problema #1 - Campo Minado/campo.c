#include <stdlib.h>
#include <stdio.h>

// int validatePosition(int p, int nc, nl);

void printMatriz(char *arr, int nl, int nc)
{
    for (int i = 0; i < nl; i++)
    {
        for (int j = 0; j < nc; j++)
        {
            printf("%c", arr[i * nc + j]);
        }
        printf("\n");
    }
}

void printMatrizInt(int *arr, int nl, int nc)
{
    for (int i = 0; i < nl; i++)
    {
        for (int j = 0; j < nc; j++)
        {
            if (arr[i * nc + j] == -1)
            {
                printf("%c", '*');
                
            } else
            printf("%d", arr[i * nc + j]);
        }
        printf("\n");
    }
}

int *calc(char *arr, int nl, int nc)
{
    int *result = malloc(nc * nl * sizeof(int));
    int nlInterno, ncInterno;

    for (int i = 0; i < nc * nl; i++)
        result[i] = 0;

    for (int i = 0; i < nl; i++)
    {
        for (int j = 0; j < nc; j++)
        {
            if (arr[i * nc + j] == '.')
                continue;
            for (int a = -1; a <= 1; a++)
            {
                for (int b = -1; b <= 1; b++)
                {
                    nlInterno = i + a;
                    ncInterno = j + b;
                    if (!(nlInterno >= 0 && nlInterno < nl))
                        continue; //
                    if (!(ncInterno >= 0 && ncInterno < nc))
                        continue;
                    if (arr[nlInterno * nc + ncInterno] == '*')
                    {
                        result[nlInterno * nc + ncInterno] = -1;
                        continue;
                    }
                    result[nlInterno * nc + ncInterno]++;
                }
            }
        }
    }
    return result;
}

int main(void)
{
    int nl, nc, count = 1;
    char arr[10000], tmp;
    scanf("%d %d", &nl, &nc);
    do
    {
        printf("Field #%d:\n", count++);
        for (int i = 0; i < nc * nl; i++)
        {

            scanf("%c", &tmp);
            if (tmp == '\n')
            {
                i = i - 1;
                continue;
            }
            arr[i] = tmp;
        }

        // printMatriz(arr, nc, nl);
        int *result = calc(arr, nl, nc);
        printMatrizInt(result, nl, nc);

        scanf("%d %d", &nl, &nc);
        printf("\n");
    } while (nc || nl);
}
