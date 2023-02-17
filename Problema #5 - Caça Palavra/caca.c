#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <iostream>

#define DEBUG(x) 

using namespace std;

typedef struct
{
    int x;
    int y;
} pto;

typedef struct
{
    char *board;
    int nl;
    int nc;
} hwBoardType;

pto directions[8] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {1, -1}, {-1, -1}, {1, 1}, {-1, 1}};

void remove_newline(char *str)
{
    for (; *str; str++)
    {
        if (*str == '\n')
            *str = '\0';
    }
}

void string_toupper(char *str)
{
    for (; *str; str++)
    {
        *str = toupper(*str);
    }
}

pto sum_pto(pto a, pto b)
{
    pto res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;

    return res;
}
bool validPosition(pto position, int maxx, int maxy)
{
    if (position.x >= maxx)
        return false;
    if (position.y >= maxy)
        return false;
    if (position.x < 0)
        return false;
    if (position.y < 0)
        return false;
    return true;
}

string translateDirection(pto dir)
{
    if (dir.x == 1 && dir.y == 1)
    {
        return "SE";
    }
    if (dir.x == -1 && dir.y == -1)
    {
        return "NO";
    }
    if (dir.x == 1 && dir.y == 0)
    {
        return "S";
    }
    if (dir.x == 0 && dir.y == 1)
    {
        return "L";
    }
    if (dir.x == -1 && dir.y == 0)
    {
        return "N";
    }
    if (dir.x == 0 && dir.y == -1)
    {
        return "O";
    }
    if (dir.x == -1 && dir.y == 1)
    {
        return "NE";
    }
    if (dir.x == 1 && dir.y == -1)
    {
        return "SO";
    }

    return "?";
}
bool searchOneDirection(hwBoardType *hwBoard, pto position, char *word, pto dir)
{

    if (*word == '\0')
        return true;

    if (!validPosition(position, hwBoard->nl, hwBoard->nc))
        return false;

    char hwLetter = hwBoard->board[position.x * hwBoard->nc + position.y];

    DEBUG(cout << "Procurando por " << word << " na direção " << translateDirection(dir) << " letters " << hwLetter << " == " << word[0] << endl;);

    if (hwLetter != word[0])
        return false;

    return searchOneDirection(hwBoard, sum_pto(position, dir), ++word, dir);
}

pto searchWord(hwBoardType *hwboard, char *word)
{
    pto position;
    for (int i = 0; i < hwboard->nl; i++)
    {
        for (int j = 0; j < hwboard->nc; j++)
        {
            DEBUG(printf("Procurando por %s em (%d, %d)\n", word, i, j););
            for (int d = 0; d < 8; d++)
            {
                position = {i, j};
                if (searchOneDirection(hwboard, position, word, directions[d]))
                {
                    printf("%d %d\n", i + 1, j + 1);
                    return {i, j};
                }
            }
        }
    }

    return (pto){-1, -1};
}

hwBoardType *createHwBoard(int nl, int nc)
{
    hwBoardType *bp = new hwBoardType();
    bp->nc = nc;
    bp->nl = nl;
    return bp;
}

void deleteHwBoard(hwBoardType *hwboard_p)
{
    delete hwboard_p->board;
    delete hwboard_p;
}

int main()
{
    char linha[30];

    int nHuntingWords, nl, nc;
    int i;
    scanf("%d\n", &nHuntingWords);
    DEBUG(printf("nHuntingWords = %d\n", nHuntingWords);)

    while (nHuntingWords--)
    {
        scanf("%d %d\n", &nl, &nc);
        hwBoardType *hwboard = createHwBoard(nl, nc);
        hwboard->board = new char[nl * nc];
        // Leitura de uma competicao
        DEBUG(printf("Leitura de competicao\n"););
        while (fgets(linha, 20, stdin))
        {
            if (atoi(linha) || !strcmp(linha, "0"))
                break;
            remove_newline(linha);
            string_toupper(linha);
            strcat(hwboard->board, linha);
            DEBUG(printf("%s", linha););
        }

        int nWords = atoi(linha);

        while (nWords--)
        {
            fgets(linha, 30, stdin);
            string_toupper(linha);
            remove_newline(linha);
            searchWord(hwboard, linha);
        }
        DEBUG(puts("----------------------------------"););
        printf("\n");
        deleteHwBoard(hwboard);
    }
}
