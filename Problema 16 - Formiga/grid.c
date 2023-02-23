#include <stdio.h>
#include <stdlib.h>

#define NPOWERS 45000

static int Powers[NPOWERS];

static void generate_powers(int n) {
    for (int i = 0; i < n; i++) {
        Powers[i] = i * i;
    }
}

static void compute_position(int n, int *c, int *r) {
    int p, s;
    for (p = 0; p < NPOWERS; p++) {
        if (Powers[p] >= n) {
            break;
        }
    }
    for (s = 0; s < (p + p); s++) {
        if (n == (Powers[p] - s)) {
            break;
        }
    }
    if (p % 2) {
        *c = 1 + (s < p ? s : p - 1);
        *r = p - (s < p ? 0 : s - p + 1);
    } else {
        *c = p - (s < p ? 0 : s - p + 1);
        *r = 1 + (s < p ? s : p - 1);
    }
}

int main(int argc, char *argv[]) {
    int n, c, r;
    generate_powers(NPOWERS);
    while (scanf("%d", &n) == 1 && n > 0) {
        compute_position(n, &c, &r);
        printf("%d %d\n", c, r);
    }
    return EXIT_SUCCESS;
}
