// Longest commom subsequence (Cormen)
#include <stdio.h>
#include <string.h>

#define MAXLEN 100

enum
{
    MATCH,
    INSERT,
    DELETE
};

struct
{
    int cost;                  /* cost of reaching this cell */
    int parent;                /* parent cell */
} tab[MAXLEN + 1][MAXLEN + 1]; /* dynamic programming table */

int lcs_lenght(char *X, char *Y)
{
    int m = strlen(X);
    int n = strlen(Y);
    for (int i = 1; i < m; i++)
        tab[i][0].cost = 0;
    for (int j = 1; j < n; j++)
        tab[0][j].cost = 0;
    for (int i = 1; i < m; i++)
        for (int j = 1; j < n; j++)
        {
            if (X[i] == Y[j])
            {
                tab[i][j].cost = tab[i - 1][j - 1].cost + 1;
                tab[i][j].parent = MATCH;
            }
            else if (tab[i - 1][j].cost >= tab[i][j - 1].cost)
            {
                tab[i][j].cost = tab[i - 1][j].cost;
                tab[i][j].parent = DELETE;
            }
            else
            {
                tab[i][j].cost = tab[i][j - 1].cost;
                tab[i][j].parent = INSERT;
            }
        }
    return tab[m - 1][n - 1].cost;
}

void print_lcs(char *X, int i, int j)
{
    char lcs[MAXLEN] = "";
    int count = 0;
    while (i != 0 && j != 0)
    {
        if (tab[i][j].parent == MATCH)
        {
            lcs[count++] = X[i];
            i = i - 1;
            j = j - 1;
        }
        else if (tab[i][j].parent == INSERT)
            j = j - 1;
        else
            i = i - 1;
    }
    lcs[count] = 0;
    for (int i = 0; i < count / 2; i++)
    {
        char tmp = lcs[i];
        lcs[i] = lcs[count - i - 1];
        lcs[count - i - 1] = tmp;
    }
    printf("%s\n", lcs);
}

void print_matrix(char *X, char *Y, int cost)
{
    int i, j; /* counters */
    int x, y; /* string lengths */

    x = strlen(X);
    y = strlen(Y);

    printf("   ");
    for (i = 0; i < y; i++)
        printf("  %c", Y[i]);
    printf("\n");

    for (i = 0; i < x; i++)
    {
        printf("%c: ", X[i]);
        for (j = 0; j < y; j++)
        {
            if (cost)
                printf(" %2d", tab[i][j].cost);
            else
                printf(" %2d", tab[i][j].parent);
        }
        printf("\n");
    }
}

int main()
{
    char *x = "democrat", *y = "republican";
    printf("%d\n", lcs_lenght(x, y));
    print_lcs(x, strlen(x) - 1, strlen(y) - 1);
    print_matrix(x, y, 1);
    print_matrix(x, y, 0);
}
