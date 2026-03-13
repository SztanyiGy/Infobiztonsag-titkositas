#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "playfair.h"

char matrix[5][5];

void generateMatrix(char *key)
{
    int used[26] = {0};
    int row = 0, col = 0;

    for(int i=0; key[i]; i++)
    {
        char c = toupper(key[i]);

        if(c=='J') c='I';

        if(!used[c-'A'])
        {
            matrix[row][col++] = c;
            used[c-'A'] = 1;

            if(col==5)
            {
                col=0;
                row++;
            }
        }
    }

    for(char c='A'; c<='Z'; c++)
    {
        if(c=='J') continue;

        if(!used[c-'A'])
        {
            matrix[row][col++] = c;

            if(col==5)
            {
                col=0;
                row++;
            }
        }
    }
}

void findPosition(char c,int *row,int *col)
{
    if(c=='J') c='I';

    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(matrix[i][j]==c)
            {
                *row=i;
                *col=j;
                return;
            }
        }
    }
}

void encryptPair(char a,char b)
{
    int r1,c1,r2,c2;

    findPosition(a,&r1,&c1);
    findPosition(b,&r2,&c2);

    if(r1==r2)
        printf("%c%c",matrix[r1][(c1+1)%5],matrix[r2][(c2+1)%5]);

    else if(c1==c2)
        printf("%c%c",matrix[(r1+1)%5][c1],matrix[(r2+1)%5][c2]);

    else
        printf("%c%c",matrix[r1][c2],matrix[r2][c1]);
}

void decryptPair(char a,char b)
{
    int r1,c1,r2,c2;

    findPosition(a,&r1,&c1);
    findPosition(b,&r2,&c2);

    if(r1==r2)
        printf("%c%c",matrix[r1][(c1+4)%5],matrix[r2][(c2+4)%5]);

    else if(c1==c2)
        printf("%c%c",matrix[(r1+4)%5][c1],matrix[(r2+4)%5][c2]);

    else
        printf("%c%c",matrix[r1][c2],matrix[r2][c1]);
}

void encryptText(char *text)
{
    for(int i=0;text[i];i+=2)
        encryptPair(text[i],text[i+1]);

    printf("\n");
}

void decryptText(char *text)
{
    for(int i=0;text[i];i+=2)
        decryptPair(text[i],text[i+1]);

    printf("\n");
}

void prepareText(char *input,char *output)
{
    int j=0;

    for(int i=0;input[i];i++)
    {
        if(isalpha(input[i]))
            output[j++]=toupper(input[i]);
    }

    output[j]='\0';

    if(j%2!=0)
    {
        output[j++]='X';
        output[j]='\0';
    }
}

void printMatrix()
{
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
            printf("%c ",matrix[i][j]);

        printf("\n");
    }
}
