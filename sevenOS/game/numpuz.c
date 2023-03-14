#include "type.h"
#include "stdio.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "fs.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"

const int numpuz_table[9][9] = {
    {1,0,0,8,3,0,0,0,2},
    {5,7,0,0,0,1,0,0,0},
    {0,0,0,5,0,9,0,6,4},
    {7,0,4,0,0,8,5,9,0},
    {0,0,3,0,1,0,4,0,0},
    {0,5,1,4,0,0,3,0,6},
    {3,6,0,7,0,4,0,0,0},
    {0,0,0,6,0,0,0,7,9},
    {8,0,0,0,5,2,0,0,3} };

int numpuz[9][9] = { 0 };

int answer[9][9] = {
    {1,4,9,8,3,6,7,5,2},
    {5,7,6,2,4,1,9,3,8},
    {2,3,8,5,7,9,1,6,4},
    {7,2,4,3,6,8,5,9,1},
    {6,8,3,9,1,5,4,2,7},
    {9,5,1,4,2,7,3,8,6},
    {3,6,2,7,9,4,8,1,5},
    {4,1,5,6,8,3,2,7,9},
    {8,9,7,1,5,2,6,4,3} };

int Try = 0;
char choice[10] = { 0 };

void show(); 
void sudoku_start();
void sudoku_restart();
void judge(int x, int y, int num);
void get_answer();
int finish();
void hint();

void sudoku(int fd_stdin, int fd_stdout)
{
    sudoku_start();
    printf("welcome to play sudoku\n\n");
    printf("h to get a hint\n");
    printf("a to get answer\n");
    printf("r to restart\n");
    printf("g x y n,this format to do next step,in(x,y),fill n\n");
    printf("q to quit");

    char x[2], y[2], numsd[2];
    while (1)
    {
        read(fd_stdin, choice, 2);
        if (choice[0] == 'q')
        {
            printf("bye\n");
            break;
        }
        switch (choice[0])
        {
        case 'h':
            hint(); break;
        case 'a':
            get_answer(); break;
        case 'r':
            sudoku_restart(); break;
        case 'g':
            Try += 1;
            read(fd_stdin, x, 2);
            read(fd_stdin, y, 2);
            read(fd_stdin, numsd, 2);
            int x1=x[0]-48;
            int y1=y[0]-48;
            int numsd1=numsd[0]-48;
            if (numsd1 < 10 && numsd1>0)
            {
                numpuz[x1][y1] = numsd1;
                judge(x1, y1, numsd1);
            }

            show();

        default:
            break;
        }
        if (finish() == 0)
        {
            printf("bye\n");
            break;
        }
    }
}

void sudoku_restart()
{
    int i, j;
    Try = 0;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            printf("%d ", numpuz_table[i][j]);
            numpuz[i][j] = numpuz_table[i][j];
        }
        printf("\n");
    }
}

void hint()
{
    int i, j;
    for(i=0;i<9;i++)
        for (j = 0; j < 9; j++)
        {
            if (numpuz[i][j] == 0)
            {
                printf("hint: x:%d y:%d num:%d", i, j, answer[i][j]);
                return;
            }
        }
}

int finish()
{
    int i, j;
    int k = 0;
    for (i = 0; i < 9; i++)
        for (j = 0; j < 9; j++)
            if (numpuz[i][j] == 0)
                k += 1;
    if (k == 0)
    {
        printf("Congratuation,you've done it!!!\n");
        printf("You 've tried %d time\n", Try);
    }
    return k;
}

void sudoku_start()
{
    int i, j;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            numpuz[i][j] = numpuz_table[i][j];
            printf("%d ", numpuz_table[i][j]);
        }
        printf("\n");
    }
}

void get_answer()
{
    int i, j;
    printf("answer!\n\n");
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            printf("%d ", answer[i][j]);
        }
        printf("\n");
    }
}

void show()
{
    int i, j;
    printf("your way!\n\n");
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            printf("%d ", numpuz[i][j]);
        }
        printf("\n");
    }
}

void judge(int x,int y,int num)
{
    int i, j;
    for (i = 0; i < 9; i++)
    {
        if (i == x)
            continue;
        if (numpuz[i][y] == num)
        {
            numpuz[x][y] = 0;
            printf("colunm wrong:%d %d\n",i,y);
        }
    }

    for (j = 0; j < 9; j++)
    {
        if (j == y)
            continue;
        if (numpuz[x][j] == num)
        {
            numpuz[x][y] = 0;
            printf("line wrong:%d %d\n",x,j);
        }
    }

    i = x / 3; j = y / 3;
    int p = i * 3 + 3; int q = j * 3 + 3;
    for(i=i*3;i<p;i++)
        for (j = j * 3; j < q; j++)
        {
            if (i == x && j == y)
                continue;
            if (numpuz[i][j] == num)
            {
                numpuz[x][y] = 0;
                printf("area wrong:%d %d\n",i,j);
            }
        }
}
