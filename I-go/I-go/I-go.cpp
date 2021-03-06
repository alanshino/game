// I-go.cpp: 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <windows.h>
#include <conio.h>
#define TRUE 1
#define FALSE 0
#define FLAT 2
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
void gotoxy(int xpos, int ypos);
int print_checkerboard(void);
void SetColor(int ForgC);
void initialization(char ***pblock);
int start_menu(void);
int(*pint[2])(void) = { print_checkerboard ,start_menu };
void(*pinit)(char ***) = initialization;
void(*pgotoxy)(int, int) = gotoxy;
void(*psetcolor)(int) = SetColor;
int colx, rowy;
class Cigo {
private:
	int up,down,left,right;
public:
	Cigo() {
		up = 0;
		down = 0;
		left = 0;
		right = 0;
	}
	void change_up(void) {
		up = 1;
	}
	void change_down(void) {
		down = 1;
	}
	void change_left(void) {
		left = 1;
	}
	void change_right(void) {
		right = 1;
	}
};
using namespace std;

int main()
{
	int attack = 0;
	char ***pblock = (char ***)malloc(sizeof(char **) * 9);
	for (int i = 0; i < 9; i++) {
		*(pblock + i) = (char **)malloc(sizeof(char *) * 9);
	}
	(*pinit)(pblock);
	attack = (*pint[1])();
	(*pint[0])();
    return 0;
}

int print_checkerboard(void) {
	system("color E8");
	printf("   _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ \n");
	printf("  |     |     |     |     |     |     |     |     |     |     |\n");
	printf("  |     |     |     |     |     |     |     |     |     |     |\n");
	printf("  |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n");
	printf("  |     |     |     |     |     |     |     |     |     |     |\n");
	printf("  |     |     |     |     |     |     |     |     |     |     |\n");
	printf("  |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n");
	printf("  |     |     |     |     |     |     |     |     |     |     |\n");
	printf("  |     |     |     |     |     |     |     |     |     |     |\n");
	printf("  |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n");
	printf("  |     |     |     |     |     |     |     |     |     |     |\n");
	printf("  |     |     |     |     |     |     |     |     |     |     |\n");
	printf("  |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n");
	printf("  |     |     |     |     |     |     |     |     |     |     |\n");
	printf("  |     |     |     |     |     |     |     |     |     |     |\n");
	printf("  |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n");
	printf("  |     |     |     |     |     |     |     |     |     |     |\n");
	printf("  |     |     |     |     |     |     |     |     |     |     |\n");
	printf("  |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n");
	printf("  |     |     |     |     |     |     |     |     |     |     |\n");
	printf("  |     |     |     |     |     |     |     |     |     |     |\n");
	printf("  |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n");
	printf("  |     |     |     |     |     |     |     |     |     |     |\n");
	printf("  |     |     |     |     |     |     |     |     |     |     |\n");
	printf("  |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n");
	printf("  |     |     |     |     |     |     |     |     |     |     |\n");
	printf("  |     |     |     |     |     |     |     |     |     |     |\n");
	printf("  |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n");
	printf("  |     |     |     |     |     |     |     |     |     |     |\n");
	printf("  |     |     |     |     |     |     |     |     |     |     |\n");
	printf("  |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n");
	return 0;
}

void gotoxy(int xpos, int ypos) {
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void SetColor(int ForgC) {
	WORD wColor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

void initialization(char ***pblock) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			*(*(pblock + i) + j) = (char *)"  ";
		}
	}
}

int start_menu(void) {
	char c;
	int rowy = 22, colx = 16;
	cout << endl << endl;
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 40; j++) {
			if (i == 0 || i == 24) {
				if (j == 0) {
					cout << "          *";
				}
				else {
					cout << "*";
				}
			}
			else if (j == 0) {
				cout << "          *";
			}
		}
		cout << endl;
	}
	for (int i = 2; i < 26; i++) {
		(*pgotoxy)(49, i);
		cout << "*";
	}
	(*pgotoxy)(26, 6);
	(*psetcolor)(10);
	cout << "遊戲說明";
	(*pgotoxy)(18, 10);
	(*psetcolor)(9);
	cout << "1. 使用Enter鍵放置棋子";
	(*pgotoxy)(18, 13);
	cout << "2. 使用方向鍵鍵移動游標";
	(*pgotoxy)(18, 16);
	cout << "3. 獲得最多地及提子者贏";
	(*pgotoxy)(18, 19);
	cout << "4. 介面右側顯示遊戲資訊";
	(*pgotoxy)(36, 22);
	cout << "後攻(白)";
	(*pgotoxy)(16, 22);
	(*psetcolor)(14);
	cout << "先攻(黑)";
	(*pgotoxy)(18, 22);
	while (TRUE) {
		c = _getch();
		if (c == -32) {
			c = _getch();
			switch (c) {
				case LEFT:
					if (colx == 18) {
						;
					}
					else {
						colx = 36;
						(*pgotoxy)(colx, rowy);
						(*psetcolor)(9);
						cout << "後攻(白)";
						colx = 18;
						(*pgotoxy)(colx - 2, rowy);
						(*psetcolor)(14);
						cout << "先攻(黑)";
						(*pgotoxy)(colx, rowy);
					}
					break;
				case RIGHT:
					if (colx == 38) {
						;
					}
					else {
						colx = 16;
						(*pgotoxy)(colx, rowy);
						(*psetcolor)(9);
						cout << "先攻(黑)";
						colx = 38;
						(*pgotoxy)(colx - 2, rowy);
						(*psetcolor)(14);
						cout << "後攻(白)";
						(*pgotoxy)(colx, rowy);
					}
			}
		}
		else if (c == ENTER) {
			if (colx == 16) {
				system("CLS");
				return 1;
			}
			else {
				system("CLS");
				return 0;
			}
		}
	}
	//system("pause");
}

void play_game(int attack) {

}

