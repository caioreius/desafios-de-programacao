//Equipe Lambda
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>

#define N 4
using namespace std;

#define TRUE 1
#define FALSE 0
#define INFINITY 1000000
#define MAXCAND 45
#define DEBUG(x)
int finished = FALSE;

typedef struct pto_
{
    int x;
    int y;
} pto;

typedef struct puzzle_
{
    pto position;
    int board[16];
} puzzle;

pto directions[4] = {
    {0, -1}, {0, 1}, {-1, 0}, {1, 0}};

char translate[4] = {'L', 'R', 'U', 'D'};

enum Directions
{
    LEFT = 0,
    RIGHT,
    UP,
    DOWN
};

int is_a_solution(int[], int, puzzle *);
void process_solution(int[], int, puzzle);
void construct_candidates(int a[], int k, puzzle puzzle_, int c[], int *nCand);
void print_soluction_parcial(int a[], puzzle puzzle_, int init, int end);
bool isSolvable(int *puzzle);
int findXPosition(int *puzzle);
int getInvCount(int arr[]);

int is_finished(int k, int *board)
{
    return k > 45 || finished;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

pto sumPto(pto a, pto b)
{
    pto c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}

puzzle *cpyPuzzle(puzzle *a)
{
    puzzle *b = (puzzle *)malloc(sizeof(puzzle));
    b->position.x = a->position.x;
    b->position.y = a->position.y;
    for (int i = 0; i < 16; i++)
    {
        b->board[i] = a->board[i];
    }
    return b;
}

puzzle *movePuzzle(puzzle *a, int dir)
{
    DEBUG(printf("\nmove_puzzle\n"););
    puzzle *b = cpyPuzzle(a);
    int *pos = &b->board[b->position.x * 4 + b->position.y];
    b->position = sumPto(b->position, directions[dir]);
    DEBUG(printf("(%d, %d) -> ", a->position.x, a->position.y););
    DEBUG(printf("(%d, %d)\n", b->position.x, b->position.y););
    int *newPos = &b->board[b->position.x * 4 + b->position.y];
    swap(pos, newPos);
    return b;
}

void printArray(int a[], int size)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%3d ", a[i * 4 + j]);
        }
        printf("\n");
    }
}

void backtrack(int a[], int k, puzzle *input)
{
    int c[MAXCAND];
    puzzle *newPuzzle;
    int nCand;
    int i;
    if (is_a_solution(a, k, input))
        process_solution(a, k, *input);
    else
    {
        k = k + 1;
        construct_candidates(a, k, *input, c, &nCand);
        for (i = 0; i < nCand; i++)
        {
            if (is_finished(k, input->board))
                return;

            a[k] = c[i];
            newPuzzle = movePuzzle(input, c[i]);
            backtrack(a, k, newPuzzle);
            delete newPuzzle;
        }
    }
}

int cmpArray(int a[], int b[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (a[i] != b[i])
            return FALSE;
    }
    return TRUE;
}

int is_a_solution(int a[], int k, puzzle *puzzle_)
{
    DEBUG(printf("\nis_a_solution\n"););
    DEBUG(print_soluction_parcial(a, *puzzle_, 1, k););
    DEBUG(printArray(puzzle_->board, 16););
    int soluction[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
    return cmpArray(soluction, puzzle_->board, 16);
}

void print_soluction_parcial(int a[], puzzle puzzle_, int init, int end)
{
    for (int i = init; i <= end; i++)
    {
        printf("%c", translate[a[i]]);
    }

    printf("\n");
}

void process_solution(int a[], int k, puzzle puzzle_)
{
    finished = TRUE;
    DEBUG(printf("soluction: "););
    print_soluction_parcial(a, puzzle_, 1, k);
}

pto getIdealPositionInBoard(int value)
{
    pto idealPosition;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (value == i * 4 + j + 1)
            {
                idealPosition.x = i;
                idealPosition.y = j;
                return idealPosition;
            }
        }
    }

    return {-1, -1};
}

int getManhattanDistance(pto a, pto b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int *get_distance_ideal_position(int *elements, int n, pto position)
{
    int *distance = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        pto idealPosition = getIdealPositionInBoard(elements[i]);
        distance[n] = getManhattanDistance(position, idealPosition);
    }

    return distance;
}

void sort_by_most_provavel_direction(puzzle puzzle_, int *c, int nCands)
{
    DEBUG(printf("\nsort_by_most_provavel_direction\n"););
    int *board = puzzle_.board;
    pto position = puzzle_.position;

    struct element
    {
        int element;
        int distance;
    };

    element *elements = (element *)malloc(sizeof(element) * nCands);

    for (int i = 0; i < nCands; i++)
    {
        elements[i].element = c[i];
        pto elementPos = sumPto(puzzle_.position, directions[c[i]]);
        int elementoValor = board[elementPos.x * 4 + elementPos.y];
        DEBUG(printf("element: %d, ", elementoValor););
        pto idealPosition = getIdealPositionInBoard(elementoValor);
        elements[i].distance = getManhattanDistance(position, idealPosition) + elementoValor * 10;
        if (getManhattanDistance(elementPos, idealPosition) == 0)
        {
            elements[i].distance += INFINITY;
        }
        DEBUG(printf("distance: %d\n", elements[i].distance););
    }

    qsort(elements, nCands, sizeof(element), [](const void *a, const void *b)
          { return ((element *)a)->distance - ((element *)b)->distance; });

    for (int i = 0; i < nCands; i++)
    {
        c[i] = elements[i].element;
    }
}

void construct_candidates(int a[], int k, puzzle puzzle_, int c[], int *nCand)
{
    DEBUG(printf("\nconstruct_candidates\n"););
    pto position = puzzle_.position;
    *nCand = 0;
    srand(k + time(NULL));
    int init = rand() % 4;
    DEBUG(printf("init: %d\n", init););
    for (int i = init; i < init + 4; i++)

    {
        int j = i % 4;

        // Tratando possibilidades de movimento
        if (position.x == 0 && j == UP)
            continue;
        if (position.x == 3 && j == DOWN)
            continue;
        if (position.y == 0 && j == LEFT)
            continue;
        if (position.y == 3 && j == RIGHT)
            continue;

        // Evitando loops de ir e voltar
        if (j == UP && a[k - 1] == DOWN)
            continue;
        if (j == DOWN && a[k - 1] == UP)
            continue;
        if (j == LEFT && a[k - 1] == RIGHT)
            continue;
        if (j == RIGHT && a[k - 1] == LEFT)
            continue;

        DEBUG(printf("%c", translate[j]););
        c[*nCand] = j;
        *nCand = *nCand + 1;
    }

    sort_by_most_provavel_direction(puzzle_, c, *nCand);
    DEBUG(print_soluction_parcial(c, puzzle_, 0, *nCand - 1););
    DEBUG(printf("\nCandidatos contruidos: %d\n", *nCand););
}

pto translate_char_to_dir(char c)
{
    for (int i = 0; i < 4; i++)
    {
        if (translate[i] == c)
            return directions[i];
    }

    return directions[0];
}

int getInvCount(int arr[])
{
    int inv_count = 0;
    for (int i = 0; i < N * N - 1; i++)
    {
        for (int j = i + 1; j < N * N; j++)
        {
            // count pairs(arr[i], arr[j]) such that
            // i < j but arr[i] > arr[j]
            if (arr[j] && arr[i] && arr[i] > arr[j])
                inv_count++;
        }
    }
    return inv_count;
}

int findXPosition(int *puzzle)
{
    for (int i = N - 1; i >= 0; i--)
        for (int j = N - 1; j >= 0; j--)
            if (puzzle[i * 4 + j] == 0)
                return N - i;

    return -1;
}

bool isSolvable(int *puzzle)
{
    int invCount = getInvCount((int *)puzzle);

    if (N & 1)
        return !(invCount & 1);

    else 
    {
        int pos = findXPosition(puzzle);
        if (pos & 1)
            return !(invCount & 1);
        else
            return invCount & 1;
    }
}

void puzzle_resolv(puzzle *p)
{
    int a[MAXCAND];
    a[0] = -1;


    if (isSolvable(p->board))
    {
        backtrack(a, 0, p);
    }
    else
    {
        printf("This puzzle is not solvable.\n");
    }
}

puzzle *readPuzzle()
{
    puzzle *p = (puzzle *)malloc(sizeof(puzzle));
    int board[16];
    for (int i = 0; i < 16; i++)
    {
        scanf("%d", &board[i]);
    }
    for (int i = 0; i < 4; i++)
    {

        for (int j = 0; j < 4; j++)
        {
            if (board[i * 4 + j] == 0)
            {
                p->position = {i, j};
            }
            p->board[i * 4 + j] = board[i * 4 + j];
        }
    }
    return p;
}

int main(int argc, char **argv)
{
    int n_cases;
    scanf("%d", &n_cases);
    for (int i = 0; i < n_cases; i++)
    {
        puzzle *p = readPuzzle();
        DEBUG(printArray(p->board, 16););
        puzzle_resolv(p);
    }
    return (EXIT_SUCCESS);
}
