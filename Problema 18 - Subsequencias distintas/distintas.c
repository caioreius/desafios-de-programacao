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
    for (int j = 0; j < n; j++)
        tab[0][j].cost = 1;
    for (int i = 1; i < m; i++)
        for (int j = 1; j < n; j++)
        {
            if (X[i] == Y[j])
            {
                tab[i][j].cost = tab[i - 1][j - 1].cost + tab[i][j - 1].cost ;
                tab[i][j].parent = MATCH;
            }
            else {
                tab[i][j].cost = tab[i][j - 1].cost;
                tab[i][j].parent = DELETE;
            }
        }
    return tab[m - 1][n - 1].cost;
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
    int n_cases;
    scanf("%d", &n_cases);
    while (n_cases--) {
        char x[MAXLEN], y[MAXLEN], x_[MAXLEN + 1], y_[MAXLEN + 1];
        scanf("%s", x);
        scanf("%s", y);
        sprintf(x_, " %s", x);
        sprintf(y_, " %s", y);
        printf("%d\n", lcs_lenght(y_, x_));
    }
}
