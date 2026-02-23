#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "game.h"


void menu()
{
	printf("*************************************\n");
	printf("*********       1.play       ********\n");
	printf("*********       0.exit       ********\n");
	printf("*************************************\n");
}

void game()
{
	char mine[ROWS][COLS];//雷的信息布置到这个数组中
	char show[ROWS][COLS];//排查到的雷的信息存放到这个数组中
	//初始化棋盘
	InitBoard(mine, ROWS, COLS,'0');
	InitBoard(show, ROWS, COLS,'*');
	DisplayBoard(show, ROW, COL);
	//DisplayBoard(mine, ROW, COL);
	//布置雷
	SetMine(mine,ROW,COL);
	//DisplayBoard(mine, ROW, COL);
	//排查雷
	FindMine(mine, show, ROW, COL);
}
void test()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("请选择");
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
			printf("选择错误，请重新选择\n");
			break;
		}
	} while(input);
}
int main()
{
	test();
	return 0;
}
