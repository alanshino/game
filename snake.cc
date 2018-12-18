// Snake.cpp: 定義主控台應用程式的進入點。
//

//#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <ctime>
#include <string>
#include <assert.h>
#include <cstdio>
#include <stdio.h>
typedef struct Snake{
	int coordinate_x;
	int coordinate_y;
}snake;
typedef struct Food {
	int coorx;
	int coory;
}food;
void gotoxy(int xpos, int ypos);
void situation(void);
void showCursor(int visible);
void(*pgotoxy)(int, int) = gotoxy;
void(*pshowcursor)(int) = showCursor;
void initialization(snake *psnake);
void(*pinit)(snake *)= initialization;
void draw_map(void);
void(*pdrawmap)(void) = draw_map;
void print_snake(int  i, snake *psnake);
void(*pprintsnake)(int, snake *) = print_snake;
void play_game(snake *);
void(*pplaygame)(snake *) = play_game;
snake snake_body[100], snake_coor, snake_last;
food snake_food;
int body_long;
int path = 3;
int snake_speed;
void SetColor(int ForgC);
void start_menu(void);
void choice_mode(void);
void(*pvoid_menu[3])(void) = { start_menu ,choice_mode,situation };
void(*psetcolor[2])(int) = { showCursor ,SetColor };
int mode,Score;
using namespace std;

int main(int argc,char **argv)
{
	(******************(*(pvoid_menu+0)))();
	(******************pdrawmap)();
	(******************pinit)(snake_body);
	(******************(*(pvoid_menu+2)))();
	(******************pplaygame)(snake_body);
    return 0;
}

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void showCursor(int visible)
{
	CONSOLE_CURSOR_INFO ConCurInf;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(hStdOut, &ConCurInf);
	ConCurInf.bVisible = visible;
	SetConsoleCursorInfo(hStdOut, &ConCurInf);
}

void initialization(snake *psnake) {
	body_long = 6;
	for (int i = 0; i < body_long; i++) {
		psnake[i].coordinate_y = 5;
	}
	for (int i = 0; i < body_long; i++) {
		psnake[i].coordinate_x = 10 - i;
	}
	snake_coor.coordinate_x = psnake[0].coordinate_x;
	snake_coor.coordinate_y = psnake[0].coordinate_y;
	for (int i = 0; i < body_long; i++) {
		(*pprintsnake)(i, psnake);
	}
}

void draw_map(void) {
	//(*psetcolor[1])(9);
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 81; j++) {
			if (i == 0 || i == 24) {
				(*psetcolor[1])(9);
				cout << "=";
			}
			else if (j == 0 || j == 80){
				(*psetcolor[1])(11);
				cout << "#";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
}

void print_snake(int  i, snake *psnake) {
	(*psetcolor[1])(10);
	gotoxy(psnake[i].coordinate_x, psnake[i].coordinate_y);
	cout << "&"; //"●"
}

void play_game(snake *psnake) {
	int game = 1;
	int feed = 0;
	int check = 0;
	char code;
	//system("pause");
	srand((unsigned int)time(NULL));
	(******************pshowcursor)(0);
	while (game) {
		if (_kbhit()) {
			code = _getch();
			if (code == -32) {
				code = _getch();
				switch (code) {
					case 72:
						snake_coor.coordinate_y--;
						path = 0;
						(*pgotoxy)(95, 14);
						cout << " Up  ";
						break;
					case 80:
						snake_coor.coordinate_y++;
						path = 1;
						(*pgotoxy)(95, 14);
						cout << " Down";
						break;
					case 75:
						snake_coor.coordinate_x--;
						path = 2;
						(*pgotoxy)(95, 14);
						cout << " Left";
						break;
					case 77:
						snake_coor.coordinate_x++;
						path = 3;
						(*pgotoxy)(95, 14);
						cout << "Right";
						break;
				}
			}
			else if (code == '-') {
				if (snake_speed > 0)
					snake_speed -= 10;
			    if (snake_speed < 100) {
					(*pgotoxy)(96, 8);
					cout << snake_speed << " ";
				}
				else {
					(*pgotoxy)(96, 8);
					cout << snake_speed;
				}
				switch (path) {
					case 0:
						snake_coor.coordinate_y--;
						path = 0;
						break;
					case 1:
						snake_coor.coordinate_y++;
						path = 1;
						break;
					case 2:
						snake_coor.coordinate_x--;
						path = 2;
						break;
					case 3:
						snake_coor.coordinate_x++;
						path = 3;
						break;
				}
			}
			else if (code == '+') {
				snake_speed += 10;
				(*pgotoxy)(95, 8);
				cout << " " << snake_speed;
				switch (path) {
					case 0:
						snake_coor.coordinate_y--;
						path = 0;
						break;
					case 1:
						snake_coor.coordinate_y++;
						path = 1;
						break;
					case 2:
						snake_coor.coordinate_x--;
						path = 2;
						break;
					case 3:
						snake_coor.coordinate_x++;
						path = 3;
						break;
				}
			}
		}
		else {
			switch (path) {
				case 0:
					snake_coor.coordinate_y--;
					path = 0;
					break;
				case 1:
					snake_coor.coordinate_y++;
					path = 1;
					break;
				case 2:
					snake_coor.coordinate_x--;
					path = 2;
					break;
				case 3:
					snake_coor.coordinate_x++;
					path = 3;
					break;
			}
		}
		if (game) {
			if (snake_coor.coordinate_x>0 && snake_coor.coordinate_x<80 && snake_coor.coordinate_y>0 && snake_coor.coordinate_y<24) {
				snake_last.coordinate_x = snake_body[body_long - 1].coordinate_x;
				snake_last.coordinate_y = snake_body[body_long - 1].coordinate_y;
				for (int i = body_long - 1; i > -1; i--) {
					if (i == 0) {
						psnake[i].coordinate_x = snake_coor.coordinate_x;
						psnake[i].coordinate_y = snake_coor.coordinate_y;
					}
					else {
						psnake[i].coordinate_x = psnake[i - 1].coordinate_x;
						psnake[i].coordinate_y = psnake[i - 1].coordinate_y;
					}
				}
			}
			else {
				//system("CLS");
				//cout << "Snake Die";
				break;
			}
			for (int i = 0; i < body_long; i++) {
				(*pprintsnake)(i, psnake);
			}
			//system("pause");
			(******************pgotoxy)(snake_last.coordinate_x, snake_last.coordinate_y);
			cout << " ";
			Sleep(snake_speed);
		}
		if (!feed) {
			snake_food.coorx = rand() % 79 + 1;
			snake_food.coory = rand() % 23 + 1;
			(******************pgotoxy)(snake_food.coorx,snake_food.coory);
			cout << "*";
			feed = 1;
		}
		if (psnake[0].coordinate_x == snake_food.coorx&&psnake[0].coordinate_y == snake_food.coory) {
			(******************pgotoxy)(snake_food.coorx, snake_food.coory);
			cout << " ";
			body_long++;
			feed--;
			Score += 100;
			(*pgotoxy)(95, 11);
			cout << " ";
			cout << Score;
			psnake[body_long - 1].coordinate_x = snake_last.coordinate_x;
			psnake[body_long - 1].coordinate_y = snake_last.coordinate_y;
		}
	}
	system("CLS");
	//printf("%d",code);
	(******************pgotoxy)(8,3);
    cout << "Snake Die";
    (******************pgotoxy)(8,5);
    cout << "Your score "<<Score;
    (******************pgotoxy)(8,7);
    cout << "Do you want to play again? 'Y/y' or 'N/n': ";
    scanf("%c",&code);
    (******************pgotoxy)(8,9);
    if (code == 'Y' || code == 'y'){
        system("CLS");
        system("snake.exe");
    }
    else if (code == 'N' || code == 'n'){
        cout << "Thank you !!!";
    }
}

void SetColor(int ForgC)
{
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

void start_menu(void) {
	char c = ' ';
	int Row = 12;
	(*pgotoxy)(Row, 1);
	(*psetcolor[1])(10);
	cout << "*******************************************************************";
	(*pgotoxy)(Row, 2);
	cout << "*                                                                 *";
	(*pgotoxy)(Row, 3);
	cout << "*                                                                 *";
	(*pgotoxy)(Row, 4);
	cout << "*                   ";
	(*psetcolor[1])(15);
	cout<<"Welcome to Snake Game !!!";
	(*psetcolor[1])(10);
	cout<<"                     *";
	(*pgotoxy)(Row, 5);
	cout << "*                                                                 *";
	(*pgotoxy)(Row, 6);
	cout << "*              ";
	(*psetcolor[1])(15);
	cout << "Arrow keys control up,down,left,right";
	(*psetcolor[1])(10);
	cout << "              *";
	(*pgotoxy)(Row, 7);
	cout << "*                                                                 *";
	(*pgotoxy)(Row, 8);
	cout << "*              ";
	(*psetcolor[1])(15);
	cout << "Eat food to increase the snake body";
	(*psetcolor[1])(10);
	cout<<"                *";
	(*pgotoxy)(Row, 9);
	cout << "*                                                                 *";
	(*pgotoxy)(Row, 10);
	cout << "*                ";
	(*psetcolor[1])(15);
	cout<<"Hit the wall the snake will die";
	(*psetcolor[1])(10);
	cout<<"                  *";
	(*pgotoxy)(Row, 11);
	cout << "*                                                                 *";
	(*pgotoxy)(Row, 12);
	cout << "*                  ";
	(*psetcolor[1])(14);
	cout << "Use '+' to speed up snake";
	(*psetcolor[1])(10);
	cout<<"                      *";
	(*pgotoxy)(Row, 13);
	cout << "*                                                                 *";
	(*pgotoxy)(Row, 14);
	cout << "*                  ";
	(*psetcolor[1])(14);
	cout << "Use '-' to slow down snake";
	(*psetcolor[1])(10);
	cout<<"                     *";
	(*pgotoxy)(Row, 15);
	cout << "*                                                                 *";
	(*pgotoxy)(Row, 16);
	cout << "*                  ";
	(*psetcolor[1])(14);
	cout << "Use the Enter key to select";
	(*psetcolor[1])(10);
	cout<<"                    *";
	(*pgotoxy)(Row, 17);
	cout << "*                                                                 *";
	(*pgotoxy)(Row, 18);
	cout << "*              ";
	(*psetcolor[1])(11);
	cout << "The above is the instructions for use";
	(*psetcolor[1])(10);
	cout<<"              *";
	(*pgotoxy)(Row, 19);
	cout << "*                                                                 *";
	(*pgotoxy)(Row, 20);
	cout << "*                                                                 *";
	(*pgotoxy)(Row, 21);
	cout << "*******************************************************************";
	(*pgotoxy)(Row+22, 23);
	(*psetcolor[1])(13);
	system("pause");
	system("CLS");
	(*pvoid_menu[1])();
}

void choice_mode(void) {
	char c;
	int i, j;
	int Row = 35, Col = 6;
	int control_row = 35;
	int in_line = 45;
	cout << endl ;
	(*psetcolor[1])(10);
	printf("                    &&=======================================&&\n");
	(*psetcolor[1])(9);
	for (i = 1; i <= 22; i++)
	{
		for (j = 0; j <= 20; j++)
		{
			if (j == 0)
			{
				printf("                    ||");
			}
			else if (j == 20)
			{
				printf(" ||");
			}
			else
			{
				printf("  ");
			}
		}
		printf("\n");
	}
	(*psetcolor[1])(10);
	printf("                    &&= = = = = = = = = = = = = = = = = = = =&&\n");
	(*psetcolor[1])(12);
	(*pgotoxy)(36, 6);
	cout << "Simple Mode";
	(*pgotoxy)(36, 11);
	cout << "Normal Mode";
	(*pgotoxy)(35, 16);
	cout << "Difficult Mode";
	Row = 36;
	(*pgotoxy)(Row, Col);
	(*psetcolor[1])(11);
	cout << "Simple Mode";
	(*pgotoxy)(in_line, 6);
	while (1) {
		c = _getch();
		if (c == -32) {
			c = _getch();
			switch (c) {
				case 72:
					if (Col > 6) {
                        (*psetcolor[1])(12);
                        (*pgotoxy)(control_row, Col);
                        if (Col == 11){
                            cout << " Normal Mode ";
                        }else if (Col == 16){
                            cout << "Difficult Mode";
                        }
                        Col -= 5;
					}
					(*psetcolor[1])(11);
					(*pgotoxy)(control_row, Col);
					if (Col == 6){
                        cout << " Simple Mode ";
					}else if (Col == 11){
                        cout << " Normal Mode ";
					}
					(*pgotoxy)(in_line, Col);
					break;
				case 80:
					if (Col < 16) {
                        (*psetcolor[1])(12);
                        (*pgotoxy)(control_row, Col);
                        if (Col == 6){
                            cout << " Simple Mode ";
                        }else if (Col == 11){
                            cout << " Normal Mode ";
                        }
                        Col += 5;
					}
					(*psetcolor[1])(11);
					(*pgotoxy)(control_row, Col);
					if (Col == 11){
                        cout << " Normal Mode ";
					}else if (Col == 16){
                        cout << "Difficult Mode";
					}
					(*pgotoxy)(in_line, Col);
					break;
			}
		}
		else if (c == 13) {
			(*pgotoxy)(34, 20);
			if (Col == 6) {
				snake_speed = 180;
				(*psetcolor[1])(11);
				cout << "Snake Speed " << snake_speed;
				mode = 0;
				(*pgotoxy)(34, 22);
				(*psetcolor[1])(15);
				cout << "Wait 2 seconds";
				Sleep(1200);
				system("CLS");
				break;
			}
			else if (Col == 11) {
				snake_speed = 150;
				(*psetcolor[1])(11);
				cout << "Snake Speed " << snake_speed;
				mode = 1;
				(*pgotoxy)(34, 22);
				(*psetcolor[1])(15);
				cout << "Wait 2 seconds";
				Sleep(1200);
				system("CLS");
				break;
			}
			else {
				snake_speed = 100;
				(*psetcolor[1])(11);
				cout << "Snake Speed " << snake_speed;
				mode = 2;
				(*pgotoxy)(35, 22);
				(*psetcolor[1])(15);
				cout << "Wait 2 seconds";
				Sleep(1200);
				system("CLS");
				break;
			}
		}
	}
}

void situation(void) {
	(*psetcolor[1])(12);
	(*pgotoxy)(88, 5);
	switch (mode) {
		case 0:
			cout << "In Simple Mode   ";
			break;
		case 1:
			cout << "In Normal Mode   ";
			break;
		case 2:
			cout << "In Difficult Mode";
			break;
	}
	(*pgotoxy)(88, 8);
	(*psetcolor[1])(15);
	cout << "Speed = ";
	(*psetcolor[1])(14);
	cout << snake_speed;
	(*pgotoxy)(88, 11);
	(*psetcolor[1])(15);
	cout << "Score = ";
	(*psetcolor[1])(14);
	cout << Score;
	(*pgotoxy)(88, 14);
	(*psetcolor[1])(15);
	cout << "Path = ";
	(*psetcolor[1])(14);
	cout << "Right";
}

