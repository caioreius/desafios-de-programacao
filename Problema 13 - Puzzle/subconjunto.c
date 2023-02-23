#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAXCAND 10
int finished = FALSE;

int is_a_solution (int [], int, int);
void process_solution (int [], int, int);
void construct_candidates (int [], int, int, int [], int *);

void backtrack (int a[], int k, int input) {
    int c[MAXCAND];
    int nCand;
    int i;
    if (is_a_solution (a, k, input))
        process_solution (a, k, input);
    else {
        k = k + 1;
        construct_candidates (a, k, input, c, &nCand);
        for (i = 0; i < nCand; i++) {
            a[k] = c[i];
            backtrack (a, k, input);
            if (finished) return;
        }
    }
}

int is_a_solution (int a[], int k, int n) {
    return k == n;
}

void process_solution (int a[], int k, int input) {
    int i;
    printf ("{");
    for (i = 1; i <= k; i++)
        if (a[i] == TRUE)
            printf ("%d ", i);
    printf ("}\n");
}

void construct_candidates (int a[], int k, int n, int c[], int *nCand) {
    c[0] = TRUE;
    c[1] = FALSE;
    *nCand = 2;
}

void generate_subsets (int n) {
    int a[MAXCAND];
    backtrack (a, 0, n);
}

int main(int argc, char** argv) {
    generate_subsets (4);
    return (EXIT_SUCCESS);
}
