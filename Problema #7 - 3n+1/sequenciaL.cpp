#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <vector> 

#define DEBUG(x) 

int *split(char *line){    int *numbers = new int[2];    char *numberAux = new char[20];    int i = 0;    int j = 0;    for (char *l = line; *l; l++)    {        i++;        numberAux[i - 1] = *l;        if (*l == ' ' || *l == '\n')        {            numberAux[i - 1] = 0;            /*DEBUG(printf("%s", numberAux););*/;            numbers[j++] = atoi(numberAux);            i = 0;        };    };    return numbers;};int tres(int n) {    if (n == 1) return 1;    return 1 + tres(n % 2 ? 3 * n + 1 : n / 2);};int getMaxCycle(int i, int j) {    int max = 0;        for (int k = i; k < j + 1; k++) {        int result = tres(k);        if (result > max) {            max = result;        }    }    return max;}; void printArr(int *arr, int arr_size) {    for (int i = 0; i < arr_size; i++)        printf("%d ", arr[i]);    puts("");} int main(void) {    int i, j, *lineInt;    char line[80];    while (fgets(line, 81, stdin))    {        if (line[0] == '\n' || line[0] == EOF)            break;        lineInt = split(line);        printf("%d %d %d\n", lineInt[0], lineInt[1], getMaxCycle(lineInt[0], lineInt[1]));        DEBUG(printArr(lineInt, 2););    }    scanf("%d %d", &i, &j);}
