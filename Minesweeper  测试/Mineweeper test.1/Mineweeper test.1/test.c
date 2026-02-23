#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "game.h"

void start()
{
	printf("****************************************\n");
	printf("*********         1.play       *********\n");
	printf("*********         0.exit       *********\n");
	printf("****************************************\n");
}


void game()
{
	char mine[ROWS][COLS];
	char show[ROWS][COLS];
	IntBoard(mine, ROWS, COLS, '0');
	IntBoard(show, ROWS, COLS, '*');
	PrintBoard(show, ROW, COL);
	//PrintBoard(mine, ROW, COL);
	SetBoard(mine, ROW, COL);
	//PrintBoard(mine, ROW, COL);
	FindBoard(mine, show, ROW, COL);
}

void test()
{
	int input = 0;
	do
	{
		srand((unsigned int)time(NULL));
		start();
		printf("请选择：");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("输入错误，请重新输入\n");
			break;
		}
	} while (input);
}


int main()
{
	test();
	return 0;
}