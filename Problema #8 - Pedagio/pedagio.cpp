#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define DEBUG(x) x

using namespace std;
typedef struct register_
{
    char placa[21];
    char data[12];
    char status;
    int km;
} registrator;

void printArrInt(int *arr, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
        printf("%d ", arr[i]);
    puts("");
}

void printArrReg(registrator **arr, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
        printf("Carro %d: %s %s %c %d\n", i, arr[i]->placa, arr[i]->data, arr[i]->status, arr[i]->km);
    puts("");
}

char **create_array_of_string(int size, int sizeofstring)
{
    char **result;

    result = new char *[size];

    for (int i = 0; i < size - 1; i++)
    {
        result[i] = new char[6];
    }

    result[size - 1] = NULL;

    return result;
}

char **split(char *line)
{
    char **strings = create_array_of_string(5, 21);
    char stringAux[21];
    int i = 0;
    int j = 0;
    for (char *l = line; *l; l++)
    {
        i++;
        stringAux[i - 1] = *l;
        if (*l == ' ' || *l == '\n')
        {
            stringAux[i - 1] = 0;
            //
            strcpy(strings[j++], stringAux);
            i = 0;
        }
    }

    return strings;
}

registrator *create_registrator(char placa[21], char data[12], char status, int km)
{
    registrator *registrator_ = new registrator;
    strcpy(registrator_->placa, placa);
    strcpy(registrator_->data, data);
    registrator_->status = status;
    registrator_->km = km;

    return registrator_;
}

int cmpfunc(const void *a, const void *b)
{
    registrator *reg1 = *(registrator **)a;
    registrator *reg2 = *(registrator **)b;

    if (!strcmp(reg1->placa, reg2->placa))
    {
        return strcmp(reg1->data, reg2->data);
    }
    else
        return strcmp(reg1->placa, reg2->placa);
}

void validateRegistros(registrator **registrators, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
    {

        if (registrators[i]->status == 'x' || (registrators[i]->status == 'n' && i + 1 >= arr_size))
        {
            registrators[i]->km = -1;
            continue;
        }

        if (!strcmp(registrators[i]->placa, registrators[i + 1]->placa))
        {

            if (registrators[i]->status - registrators[i + 1]->status > 0)
            {

                registrators[i]->km = -1;
                registrators[i + 1]->km = -1;
                i++;
            }
            else
            {
                if (registrators[i]->status - registrators[i + 1]->status == 0)
                {

                    registrators[i]->km = -1;
                }
                else
                    i++;
            }
        }
        else
        {

            registrators[i]->km = -1;
        }
    }
}

void calculatePrice(registrator **registrators, int size_registrator, int *tributeByHour)
{
    int aux, total, count;
    for (int i = 0; i < size_registrator; )
    {
        registrator carro1, carro2;
        total = count = 0;
        do
        {

            carro1 = *registrators[i];
            carro2 = *registrators[i + 1];
            //printf("\nCarro %d: %s %s %c %d\n", i, carro1.placa, carro1.data, carro1.status, carro1.km);

            char indice[] = {carro1.data[6], carro1.data[7], '\0'};
            //printf("Tributo:%d Indice:%d\n", tributeByHour[atoi(indice)], atoi(indice));
            total += abs(carro1.km - carro2.km) * tributeByHour[atoi(indice)];
            count++;

            i += 2;

            if(i >= size_registrator){
                break;
            }

        } while (!strcmp(carro1.placa, registrators[i]->placa));
        printf("%s $%.2f \n", carro1.placa, (float)total / 100.00 + count + 2);
    }
}

void removeInvalidate(registrator **registrators, int *arr_size)
{
    int j = 0;
    for (int i = 0; i < *arr_size; i++)
    {
        if (registrators[i]->km == -1)
        {
            continue;
        }
        else
        {
            registrators[j] = registrators[i];
            j++;
        }
    }

    *arr_size = j;
}

int main(void)
{
    int nCases, tributeByHour[24];
    registrator *registrators[1000];
    char line[200];
    char **lineSplit;

    scanf("%d\n", &nCases);

    while (nCases--)
    {
        for (int i = 0; i < 24; i++)
        {

            scanf("%d", &tributeByHour[i]);
        }

        fgets(line, 201, stdin);

        int count = 0;
        while (fgets(line, 201, stdin))
        {
            if (line[0] == '\n' || line[0] == EOF)
                break;
            lineSplit = split(line);
            // printf("%s %s %s %s\n", lineSplit[0], lineSplit[1], lineSplit[2], lineSplit[3]);
            registrators[count++] = create_registrator(lineSplit[0], lineSplit[1], lineSplit[2][1], atoi(lineSplit[3]));
        }

        qsort(registrators, count, sizeof(registrator *), cmpfunc);

        validateRegistros(registrators, count);
        //printArrReg(registrators, count);

        removeInvalidate(registrators, &count);
        //printArrReg(registrators, count);
        calculatePrice(registrators, count, tributeByHour);
        puts("");
    }
}
