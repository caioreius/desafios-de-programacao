#include <stdio.h>

void permuta (int *V, int inicio, int fim) {
	if (inicio == fim-1) {
	   int i;
	   for (i = 0; i < fim; i++)
	      printf ("%d ", V[i]);
	   printf ("\n");
	   return;
	} 
	else {
	   int i, tmp;
       for (i = inicio; i < fim; i++) {
          tmp = V[i];
          V[i] = V[inicio];
          V[inicio] = tmp;
          permuta (V, inicio + 1, fim);
          V[inicio] = V[i];
          V[i] = tmp;
       }
    }
}

int main () {
	int vetor[4] = {1, 2, 3, 4};
	permuta (vetor, 0, 4);
}
