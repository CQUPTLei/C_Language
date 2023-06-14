#include<stdio.h>

#define COLUM 3
#define ROW 3

void sum_row(int tab[][COLUM],int row);
void sum_colum(int [][COLUM],int);         //省略形参名
void sum_2d(int (*p)[COLUM],int row);

char file_scope[] = "This is a file scope array.";

int arrray()
{
    int table[3][3] = { {1,2,3},{1,2,3},{1,2,3} };


    sum_row(table,ROW);
    sum_colum(table,ROW);
    sum_2d(table,ROW);

    return 0;
}

void sum_row(int tab[][COLUM], int row)
{
    int r, c, total;
    for (r=0;r<row;r++)
    {
        total = 0;
        for (c = 0;c < COLUM;c++)
        {
            total += tab[r][c];
        }
        printf("Row %d = %d\n", r, total);
    }
}


void sum_colum(int tab[][COLUM], int row)
{
    int r, c, total;
    for (c = 0;c < COLUM;c++)
    {
        total = 0;
        for (r = 0;r < row;r++)
        {
            total += tab[r][c];
        }
        printf("Colum %d = %d\n", c, total);
    }
}

void sum_2d(int (*p)[COLUM],int row)
{
    int r, c, total;
    total = 0;
    for (r=0;r<row;r++)
    {
        for (c = 0;c < COLUM;c++)
        {
            //total += p[r][c];
            total += *(*(p + r) + c);
        }
    }
    printf("Total= %d\n",total);
}