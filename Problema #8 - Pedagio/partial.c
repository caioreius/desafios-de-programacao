#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int vetor[] = { 13, 20, 7, 15, 32 };

int compara (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

struct cad {
    int idade;
    char *nome;
} lista[5] = 
     {13, "luiz", 
      20, "pedro", 
      40, "joao", 
       8, "lucas", 
      12, "marcos"};

int comparaIdade (const void *a, const void *b) {
    return ((struct cad *)a)->idade - ((struct cad *)b)->idade;
}

int comparaNome (const void *a, const void *b) {
    return strcmp (((struct cad *)a)->nome, ((struct cad *)b)->nome);
}

void mostraLista (struct cad *L, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf ("%d:[%10s,%2d]\n", i, L[i].nome, L[i].idade);
    }
}

int main()
{
   int n;

   printf("Vetor antes da ordenação: \n");
   for( n = 0 ; n < 5; n++ ) printf("%d ", vetor[n]);

   qsort(vetor, 5, sizeof(int), compara);

   printf("\nVetor depois da ordenação: \n");
   for( n = 0 ; n < 5; n++ ) printf("%d ", vetor[n]);
   
   printf ("\n\nLista antes de ordenar por Idade: \n");
   mostraLista (lista, 5);
   
   qsort (lista, 5, sizeof (struct cad), comparaIdade);

   printf ("\nLista depois de ordenar por Idade: \n");
   mostraLista (lista, 5);
   
   printf ("\n\nLista antes de ordenar por Nome: \n");
   mostraLista (lista, 5);
   
   qsort (lista, 5, sizeof (struct cad), comparaNome);

   printf ("\nLista depois de ordenar por Nome: \n");
   mostraLista (lista, 5);
      
   return(0);
}
