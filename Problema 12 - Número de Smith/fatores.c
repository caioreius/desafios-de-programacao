#include <stdio.h>
#include <math.h>

void fatores_primos (long n) {
     	long c = n;
     	long i;
		printf ("Numero = %ld:", n);
     	while ((c % 2 == 0)) {
     	    printf ("%ld ", 2);
     	    c = c / 2;
     	}
     	i = 3;
     	while (i <= sqrt(c) + 1) {
     		if (c % i == 0) {
     			printf ("%ld ", i);
     			c = c / i;
     		}
     		else i = i + 2;
     	}
     	if (c > 1) printf ("%ld ", c);
}

int main (void) {
	int num;
	while (scanf ("%d\n", &num) != EOF) {
	    fatores_primos (num);
		printf ("\n");
	}
	return 0;
}
