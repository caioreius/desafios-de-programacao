#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DEBUG(x)

char *readBlock()
{
    char controlFirstLoop = 0;
    char line[200];
    char *block = new char[82 * 100]; // 100 lines of 80 chars + 1 for the null char + 1 for the line feed
    while (fgets(line, 82, stdin))
    {
        if (line[0] == '\n' && controlFirstLoop)
        {
            break;
        }

        strcat(block, line);
        controlFirstLoop = 1;
    }

    return block;
}

char *match(char *line, char *decode)
{
    if (strlen(line) != strlen(decode))
        return NULL;

    char *cypher = new char[26];

    for (int i = 0; i < 26; i++)
    {
        cypher[i] = 0;
    }

    for (char *l = line; *l; l++, decode++)
    {
        if (isalnum(*l) && isalnum(*decode))
        {
            if (cypher[*l - 'a'] == 0)
            {
                cypher[*l - 'a'] = *decode;
            }
            else if (cypher[*l - 'a'] != *decode)
            {
                return NULL;
            }
        }
    }
    return cypher;
}

char *matchCypher(char *decode, char *block)
{
    char *cypher;
    char line[81];
    for (char *l = line; *block; block++, l++)
    {
        if (*block == '\n')
        {

            *l = 0;
            DEBUG(printf("line: %s\n", line););
            cypher = match(line, decode);

            if (cypher)
                return cypher;

            l = line;
            block++;
        }
        *l = *block;
    }
    return NULL;
}

char *decode_string(char *cypher, char *block)
{
    char *decode = new char[82 * 100];
    char *d = decode;
    for (char *b = block; *b; b++, d++)
    {
        if (isalnum(*b))
            *d = cypher[*b - 'a'];

        else
            *d = *b;
    }
    return decode;
}

int main(void)
{
    int nBlocks;
    char *block;
    char *cypher;
    char decode[81] = "the quick brown fox jumps over the lazy dog";

    scanf("%d\n", &nBlocks);

    while (nBlocks--)
    {
        DEBUG(printf("nBlocks: %d\n", nBlocks);)
        block = readBlock();
        cypher = matchCypher(decode, block);
        DEBUG(printf("%s\n", cypher ? cypher : "Não resolvido"););
        if (cypher)
            printf("%s\n", decode_string(cypher, block));
        else
            printf("No solution.\n\n");
    }
}