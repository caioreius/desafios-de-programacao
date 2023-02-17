// Equipe λ

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG(x)

void _2dn(int *registro, int d, int n)
{
    registro[d] = n;
}

void _3dn(int *registro, int d, int n)
{
    registro[d] = (registro[d] + n) % 1000;
}

void _4dn(int *registro, int d, int n)
{
    registro[d] = (registro[d] * n) % 1000;
}

void _5ds(int *registro, int d, int s)
{
    registro[d] = registro[s];
}

void _6ds(int *registro, int d, int s)
{
    registro[d] = (registro[d] + registro[s]) % 1000;
}

void _7ds(int *registro, int d, int s)
{
    registro[d] = (registro[d] * registro[s]) % 1000;
}

void _8da(int *registro, int *memory, int d, int a)
{
    registro[d] = memory[registro[a]];
}

void _9sa(int *registro, int *memory, int s, int a)
{
    memory[registro[a]] = registro[s];
}

int _0ds(int *registro, int d, int s)
{
    if (registro[s] != 0)
    {
        return registro[d];
    }
    return -1;
}

void printArr(int *arr, int arr_size);

void clean(int *arr, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
    {
        arr[i] = 0;
    };
}

void split_instruction(int instruction, int *command, int *arg1, int *arg2)
{
    if (instruction < 10)
    {
        *command = 0;
        *arg1 = 0;
        *arg2 = instruction;
    }

    else if (instruction < 100)
    {
        *command = 0;
        *arg2 = instruction % 10;
        *arg1 = (instruction - *arg2) / 10;
    }
    else
    {
        *arg2 = instruction % 10;
        *arg1 = ((instruction - *arg2) / 10) % 10;
        *command = (instruction - *arg2 - *arg1 * 10) / 100;
    }

    DEBUG(printf("command: %d, arg1: %d, arg2: %d\n", *command, *arg1, *arg2));
}

int resolv_program(int *memory)
{
    int registers[10], p, instruction, operator1, operator2;
    clean(registers, 10);
    int i = 0;
    for (int *m = memory; *m != 100; m++, i++)
    {
        split_instruction(*m, &instruction, &operator1, &operator2);

        switch (instruction)
        {
        case 2:
            _2dn(registers, operator1, operator2);
            break;
        case 3:
            _3dn(registers, operator1, operator2);
            break;
        case 4:
            _4dn(registers, operator1, operator2);
            break;
        case 5:
            _5ds(registers, operator1, operator2);
            break;
        case 6:
            _6ds(registers, operator1, operator2);
            break;
        case 7:
            _7ds(registers, operator1, operator2);
            break;
        case 8:
            _8da(registers, memory, operator1, operator2);
            break;
        case 9:
            _9sa(registers, memory, operator1, operator2);
            break;
        case 0:
            p = _0ds(registers, operator1, operator2);
            if (p != -1)
            {
                m = &memory[p - 1];
            }
            break;
        default:
            printf("Error: invalid instruction %d", instruction);
            exit(10);
        }
    }

    return i + 1; // +1 because the last instruction is 100
}

void printArr(int *arr, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
    {
        printf("%d ", arr[i]);
    };
}

void main(void)
{
    int n_programs, count = 0, n_instructions, memory[1000], *m;
    char string[3], tmp, *s;
    scanf("%d", &n_programs);
    tmp = getchar();
    tmp = getchar();
    do
    {
        s = string;
        m = memory;
        clean(memory, 1000);
        DEBUG(printf("Programa %d\n", count + 1));
        while (1)
        {
            tmp = getchar();
            if (tmp == '\n')
            {
                *(m++) = atoi(string);
                // DEBUG(printf("%s ", string));
                s = string; // reset read string
                tmp = getchar();
                if (tmp == '\n' || tmp == EOF)
                {
                    DEBUG(printf("fim de programa\n"));
                    break;
                }
            }
            *(s++) = tmp;
        }

        count++;
        n_instructions = resolv_program(memory);
        printf("%d\n\n", n_instructions);

    } while (count < n_programs);
}
