#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "game.h"

static int addboard(char mine[ROWS][COLS],int i,int j)
{
	return mine[i - 1][j - 1] + mine[i - 1][j] + mine[i - 1][j + 1] + mine[i][j - 1] + mine[i][j + 1] + mine[i + 1][j - 1] + mine[i + 1][j + 1]+mine[i+1][j] - 8 * '0';
}

void IntBoard(char board[ROWS][COLS], int r, int c, char set)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < c; j++)
		{
			board[i][j] = set;
		}
	}
}
void PrintBoard(char board[ROWS][COLS], int r, int c)
{
	printf("*******      扫雷     *******\n");
	int i = 0;
	int j = 0;
	for (i = 0; i <= r; i++)
	{
		printf("%d ", i);
	}
	printf("\n");
	for (i = 1; i <= r; i++)
	{
		printf("%d ", i);
		for (j = 1; j <= c; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}
void SetBoard(char board[ROWS][COLS], int r, int c)
{
	int count = EASY;
	while (count)
	{
		int i = rand() % r + 1;
		int j = rand() % c + 1;
		if (board[i][j] = '0')
		{
			board[i][j] = '1';
			count--;
		}
	}
}

void FindBoard(char mine[ROWS][COLS], char show[ROWS][COLS], int r, int c)
{
	int i = 0;
	int j = 0;
	int win = 0;
	while (win < r * c - EASY)
	{
		printf("请输入要排查雷的坐标：\n");
		scanf("%d %d", &i,&j);
		if (i >= 1 && i <= r && j >= 1 && j <= c)
		{
			if (mine[i][j] == '1')
			{
				printf("You Dead\n");
				PrintBoard(mine, r, c);
				break;
			}
			else
			{
				if (show[i][j]=='*')
				{
					int count = addboard(mine,i,j);
					show[i][j] = count+'0';
					PrintBoard(show, r, c);
					win++;
				}
				else
				{
					printf("该坐标已被排查\n");
				}
			}
		}
		else
		{
			printf("输入有误，请重新输入\n");
		}
	}
	if (win == r * c - EASY)
	{
		printf("排雷成功！");
		PrintBoard(mine, r, c);
	}
}