#pragma once
#include <stdlib.h>
#include <time.h>

#define ROW 9
#define COL 9
#define EASY 10

#define ROWS ROW+2
#define COLS COL+2

void IntBoard(char board[ROWS][COLS], int r, int c, char set);
void PrintBoard(char board[ROWS][COLS],int r,int c);
void SetBoard(char board[ROWS][COLS], int r, int c);
void FindBoard(char mine[ROWS][COLS], char show[ROWS][COLS], int r, int c);