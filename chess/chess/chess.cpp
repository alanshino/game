// chess.cpp: 定義主控台應用程式的進入點。
//

#include "stdafx.h"
// test.cpp: 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <assert.h>
#include <conio.h>
#include <string.h>
#include <ctime>
#include <string>
#include <cstdlib>
#define TRUE 1
#define FALSE 0
//開發工具 : Visual C++   -   Visual Studio
//https://github.com/alanshino/game; //github資訊
void draw_picture(char *(*pi)[10]);
void initialization_map(char *(*pi)[10]); // 初始化之function
void(*pvoid_func)(char *(*)[10]); 
void gotoxy(int xpos, int ypos); // windows.h提供控制游標之function
void showCursor(int visible); //啟動後隱藏游標
void up(void); // 控制游標移動方向 依序為 上 下 左 右
void down(void);
void left(void);
void right(void);
int pox, poy; // 確認目前游標的位置
int success = 0; //確認下子成功
void (*pvoid_for_cursor[4])(void) = { up,down,left,right }; // 控制游標移動 是一個function pointer
void putchess(char *(*pc)[10], int x, int y, int slap); // 確認下子的位置
void gomoku(char *(*pc)[10], int x, int y, int slap);  //確認下子的順序
void (*(pointer_to_vopfour)[2])(char *(*)[10], int, int, int) = { putchess , gomoku }; // two pointer of pointer to function pointer have four parameter
int Flat(char *(*pc)[10], int x, int y); //判斷是否都放置完成
typedef int (*pointer_to_Flat)(char*(*pc)[10], int, int); // function pointer to Flat function  
void Start_screen(void);  // 起始畫面
void (*pointer_to_start)(void) = Start_screen; // pointer to start_screen function
void change_color(int background, int forecolor); // 更換顏色 前景 背景 相同function
void(*pchange_color)(int, int) = change_color; // Pointer to change_color function
void(*pgotoxy)(int, int) = gotoxy; // pointer to gotoxy
void SetCursorVisible(BOOL Visible, DWORD Size); // set cursor proportion
void setColor(int color); // 設定顏色
void (*psetcolor)(int) = setColor;
int check_win(char *(*pc)[10], int y, int x, char *); // 判斷遊戲是否產生贏家
int (*pointer_to_check_win)(char *(*)[10], int, int, char *)= check_win; // pointer to check_win() function
int global_color_number = 0;
int call = 0;
void SetColor(int ForgC);
void (*pSetColor)(int) = SetColor;
using namespace std;

int main(int argc, char **argv) {
	int i = 0, j = 0, number_pox = 0, number_poy = 0, start_menu = 0;
	int take = 0;
	int slap = 0;
	int fcolor = 0, bcolor = 3;
	char *(*picture)[10];
	SetCursorVisible(1,80);
	//int(*pblock)[10] = (int(*)[10])malloc(sizeof(int[10]) * 6);
	char position;
	picture = (char *(*)[10])malloc(sizeof(char *[10]) * 6);
	int **pblock = (int **)malloc(sizeof(int) * 6);
	char * background[8] = { (char *)"color 0",(char *)"color 1",(char *)"color 2",(char *)"color 3",(char *)"color 4",(char *)"color 5",(char *)"color 6",(char *)"color 7" };
	char * foreground[8] = { (char *)"8",(char *)"9",(char *)"A",(char *)"B",(char *)"C",(char *)"D",(char *)"E",(char *)"F" };
	string color_list[8] = { "black     ","blue      ","green     ","blue-green","red       ","purple    ","yellow    ","white     " };
	string color_table[8] = { "gray            ","light blue      ","light green     ","light blue green","light red       ","light purple     ","light yellow    ","light white     " };
	pox = 5;
	poy = 1;
	pointer_to_Flat ptr_to_flat = Flat;
	for (i = 0; i < 6; i++) {
		*(pblock + i) = (int *)malloc(sizeof(int) * 10);
	}
	for (i = 0 , number_poy=1 ; i < 6; i++, number_poy+=3 ) {
		for (j = 0 , number_pox=5 ; j < 10; j++, number_pox+=7 ) { //將 ROW COL 值相加
			*(*(pblock + i) + j) = number_pox+number_poy;
		}
	}
	system("color 0A");
	(******************pointer_to_start)();
	label:
	system("color 0F");
	(*pSetColor)(11);
	initialization_map(picture);
	draw_picture(picture);
	gotoxy(79, 1);
	(*pSetColor)(9);
	cout << "backgroundcolor = " + color_list[bcolor];
	gotoxy(79, 3);
	(*pSetColor)(10);
	cout << "forecolor = " + color_table[fcolor];
	gotoxy(79, 5);
	(*pSetColor)(15);
	slap == 0 ? printf("● times") : printf("○ times");
	(*****************pgotoxy)(79, 9);
	(*pSetColor)(14);
	cout << "Use ← ↑ → ↓ to move" << endl;
	(*****************pgotoxy)(79, 11);
	(*pSetColor)(14);
	cout << "Enter to put ● or ○" << endl;
	gotoxy(pox, poy);
	while (1) {  // ⌚⌚⌚⌚⌚⌚⌚⌚⌚⌚⌚⌚⌚⌚⌚⌚⌚⌚
		position = _getch();
		gotoxy(79,5);
		(*psetcolor)(8);
		slap == 0 ? printf("# Now ● times") : printf("# Now ○ times");
		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
		gotoxy(pox,poy);
		if ((******************(ptr_to_flat))(picture, 10, 6)) {
			system("CLS"); //清空視窗
			gotoxy(10, 3); 
			printf("This game is tied\n");
			Sleep(2000); //停兩秒鐘 Visual C++
			//_sleep(2000); // Because Compiler deffrent Gcc - MinGw
			exit(0);
		}
		if (position == 13) { // 偵測Enter鍵有無被按下
			gotoxy(79, 7);
			if (slap == 0) {
				for (i = 0, number_pox = 5; i < 10; i++, number_pox += 7) {
					for (j = 0, number_poy = 1; j < 6; j++, number_poy += 3) {
						if ((pox + poy) == (number_poy + number_pox)) {  //如果值與配置之值相同呼叫 function pointer
							(******************(pointer_to_vopfour)[0])(picture, j, i, slap);
						}
					}//number_poy = 1
				}
			}
			else {
				for (i = 0, number_pox = 5; i < 10; i++, number_pox += 7) {
					for (j = 0, number_poy = 1; j < 6; j++, number_poy += 3) {
						if ((pox + poy) == (number_poy + number_pox)) {
							(******************(pointer_to_vopfour)[0])(picture, j, i, slap);
						}
					}//number_poy = 1
				}
			}
			if (success) {
				success = !success; // 如果有放置成功棋子才會轉換
				slap = !slap;
			}
			gotoxy(pox,poy);
		}else if (position == -32) { // 方向鍵是 2 Bytes
				position = _getch();
				switch (position) {
					case 72:
						(******************pvoid_for_cursor[0])();
						break;
					case 80:
						(******************pvoid_for_cursor[1])();
						break;
					case 75:
						(******************pvoid_for_cursor[2])();
						break;
					case 77:
						(******************pvoid_for_cursor[3])();
						break;
			}
		}
		else if (position == 102 || position == 70) {
			if (fcolor < 7) {
				fcolor++;
				(******************pchange_color)(bcolor, fcolor);
				//SetColor(fcolor);
			}
			else {
				fcolor = 0;
				(******************pchange_color)(bcolor, fcolor);
				//SetColor(fcolor);
			}
			gotoxy(79, 3);
			cout << "forecolor = " + color_table[fcolor];
			gotoxy(pox, poy);
		}
		else if (position == 98 || position ==  66) {
			if (bcolor < 7) {
				bcolor++;
				(******************pchange_color)(bcolor, fcolor);
			}
			else {
				bcolor = 0;
				(******************pchange_color)(bcolor, fcolor);
			}
			gotoxy(79, 1);
			cout << "backgroundcolor = " + color_list[bcolor];
			gotoxy(pox, poy);
		}
		else if (position == 42) {
			call++;
			if (start_menu == 0) {
				system("color 0E");
				(******************pointer_to_start)();
				start_menu++;
				goto label;
			}
			else if (start_menu == 1) {
				system("color 0A");
				(******************pointer_to_start)();
				start_menu++;
				goto label;
			}
			else if (start_menu == 2) {
				system("color 09");
				(******************pointer_to_start)();
				start_menu++;
				goto label;
			}
			else {
				system("color 0B");
				(******************pointer_to_start)();
				start_menu = 0;
				goto label;
			}
		}
	}
	for (i = 0; i < 6; i++) {
		free(*(pblock + i));
	}
	free(pblock);
	return 0;
}

void initialization_map(char * (*pi)[10]) { // 初始化function
	int i, j;
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 10; j++) {
			*(*(pi + i) + j) = (char *)malloc(sizeof(char) * 5);
		}
	}
	for (i = 0; i<6; i++) {
		for (j = 0; j<10; j++) {
			(*(*(pi + i) + j)) = (char *)"  ";
		}
	}
}

void draw_picture(char *(*pi)[10]) {  // 繪製需要的遊戲圖
	printf("  |      |      |      |      |      |      |      |      |      |      |\n");
	printf("  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |\n", *(*(pi + 0) + 0), *(*(pi + 0) + 1), *(*(pi + 0) + 2), *(*(pi + 0) + 3), *(*(pi + 0) + 4), *(*(pi + 0) + 5), *(*(pi + 0) + 6), *(*(pi + 0) + 7), *(*(pi + 0) + 8), *(*(pi + 0) + 9));
	printf("  |______|______|______|______|______|______|______|______|______|______|\n");
	printf("  |      |      |      |      |      |      |      |      |      |      |\n");
	printf("  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |\n", *(*(pi + 1) + 0), *(*(pi + 1) + 1), *(*(pi + 1) + 2), *(*(pi + 1) + 3), *(*(pi + 1) + 4), *(*(pi + 1) + 5), *(*(pi + 1) + 6), *(*(pi + 1) + 7), *(*(pi + 1) + 8), *(*(pi + 1) + 9));
	printf("  |______|______|______|______|______|______|______|______|______|______|\n");
	printf("  |      |      |      |      |      |      |      |      |      |      |\n");
	printf("  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |\n", *(*(pi + 2) + 0), *(*(pi + 2) + 1), *(*(pi + 2) + 2), *(*(pi + 2) + 3), *(*(pi + 2) + 4), *(*(pi + 2) + 5), *(*(pi + 2) + 6), *(*(pi + 2) + 7), *(*(pi + 2) + 8), *(*(pi + 2) + 9));
	printf("  |______|______|______|______|______|______|______|______|______|______|\n");
	printf("  |      |      |      |      |      |      |      |      |      |      |\n");
	printf("  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |\n", *(*(pi + 3) + 0), *(*(pi + 3) + 1), *(*(pi + 3) + 2), *(*(pi + 3) + 3), *(*(pi + 3) + 4), *(*(pi + 3) + 5), *(*(pi + 3) + 6), *(*(pi + 3) + 7), *(*(pi + 3) + 8), *(*(pi + 3) + 9));
	printf("  |______|______|______|______|______|______|______|______|______|______|\n");
	printf("  |      |      |      |      |      |      |      |      |      |      |\n");
	printf("  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |\n", *(*(pi + 4) + 0), *(*(pi + 4) + 1), *(*(pi + 4) + 2), *(*(pi + 4) + 3), *(*(pi + 4) + 4), *(*(pi + 4) + 5), *(*(pi + 4) + 6), *(*(pi + 4) + 7), *(*(pi + 4) + 8), *(*(pi + 4) + 9));
	printf("  |______|______|______|______|______|______|______|______|______|______|\n");
	printf("  |      |      |      |      |      |      |      |      |      |      |\n");
	printf("  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |\n", *(*(pi + 5) + 0), *(*(pi + 5) + 1), *(*(pi + 5) + 2), *(*(pi + 5) + 3), *(*(pi + 5) + 4), *(*(pi + 5) + 5), *(*(pi + 5) + 6), *(*(pi + 5) + 7), *(*(pi + 5) + 8), *(*(pi + 5) + 9));
	printf("  |______|______|______|______|______|______|______|______|______|______|\n");
	gotoxy(5, 1);
	//system("pause");
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

void gotoxy(int xpos, int ypos) {
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void up(void) {
	if (poy>2) {
		//gotoxy(24, 2);
		//printf("Coordinate Row:%d Col:%d ", pox, poy - 3);
		gotoxy(pox, poy -= 3);
	}
	else
		gotoxy(pox, poy);
}

void down(void) {
	if (poy<15) {
		//gotoxy(24, 2);
		//printf("Coordinate Row:%d Col:%d ", pox, poy + 3);
		gotoxy(pox, poy += 3);
	}
	else
		gotoxy(pox, poy);
}

void left(void) {
	if (pox>10) {
		//gotoxy(24, 2);
		//printf("Coordinate Row:%d Col:%d ", pox - 6, poy);
		gotoxy(pox -= 7, poy);
	}
	else
		gotoxy(pox, poy);
}

void right(void) {
	if (pox<68) {
		//gotoxy(24, 2);
		//printf("Coordinate Row:%d Col:%d ", pox + 6, poy);
		gotoxy(pox += 7, poy);
	}
	else
		gotoxy(pox, poy);
}

void putchess(char *(*pc)[10],int x,int y,int slap) {
	if (slap == 0 || slap == 1) {
		if (pox == 5) {
			if (poy == 1) {
				(******************(pointer_to_vopfour)[1])(pc, 0, 0, slap);
				//gomoku(pc, 0, 0, slap);
			}
			else if (poy == 4) {
				(******************(pointer_to_vopfour)[1])(pc, 0, 1, slap);
				//gomoku(pc, 0, 1, slap);
			}
			else if (poy == 7) {
				(******************(pointer_to_vopfour)[1])(pc, 0, 2, slap);
				//gomoku(pc, 0, 2, slap);
			}
			else if (poy == 10) {
				(******************(pointer_to_vopfour)[1])(pc, 0, 3, slap);
				//gomoku(pc, 0, 3, slap);
			}
			else if (poy == 13) {
				(******************(pointer_to_vopfour)[1])(pc, 0, 4, slap);
				//gomoku(pc, 0, 4, slap);
			}
			else if (poy == 16) {
				(******************(pointer_to_vopfour)[1])(pc, 0, 5, slap);
				//gomoku(pc, 0, 5, slap);
			}
		}
		else if (pox == 12) {
			if (poy == 1) {
				(******************(pointer_to_vopfour)[1])(pc, 1, 0, slap);
				//gomoku(pc, 1, 0, slap);
			}
			else if (poy == 4) {
				(******************(pointer_to_vopfour)[1])(pc, 1, 1, slap);
				//gomoku(pc, 1, 1, slap);
			}
			else if (poy == 7) {
				(******************(pointer_to_vopfour)[1])(pc, 1, 2, slap);
				//gomoku(pc, 1, 2, slap);
			}
			else if (poy == 10) {
				(******************(pointer_to_vopfour)[1])(pc, 1, 3, slap);
				//gomoku(pc, 1, 3, slap);
			}
			else if (poy == 13) {
				(******************(pointer_to_vopfour)[1])(pc, 1, 4, slap);
				//gomoku(pc, 1, 4, slap);
			}
			else if (poy == 16) {
				(******************(pointer_to_vopfour)[1])(pc, 1, 5, slap);
				//gomoku(pc, 1, 5, slap);
			}
		}
		else if (pox == 19) {
			if (poy == 1) {
				(******************(pointer_to_vopfour)[1])(pc, 2, 0, slap);
				//gomoku(pc, 2, 0, slap);
			}
			else if (poy == 4) {
				(******************(pointer_to_vopfour)[1])(pc, 2, 1, slap);
				//gomoku(pc, 2, 1, slap);
			}
			else if (poy == 7) {
				(******************(pointer_to_vopfour)[1])(pc, 2, 2, slap);
				//gomoku(pc, 2, 2, slap);
			}
			else if (poy == 10) {
				(******************(pointer_to_vopfour)[1])(pc, 2, 3, slap);
				//gomoku(pc, 2, 3, slap);
			}
			else if (poy == 13) {
				(******************(pointer_to_vopfour)[1])(pc, 2, 4, slap);
				//gomoku(pc, 2, 4, slap);
			}
			else if (poy == 16) {
				(******************(pointer_to_vopfour)[1])(pc, 2, 5, slap);
				//gomoku(pc, 2, 5, slap);
			}
		}
		else if (pox == 26) {
			if (poy == 1) {
				(******************(pointer_to_vopfour)[1])(pc, 3, 0, slap);
				//gomoku(pc, 3, 0, slap);
			}
			else if (poy == 4) {
				(******************(pointer_to_vopfour)[1])(pc, 3, 1, slap);
				//gomoku(pc, 3, 1, slap);
			}
			else if (poy == 7) {
				(******************(pointer_to_vopfour)[1])(pc, 3, 2, slap);
				//gomoku(pc, 3, 2, slap);
			}
			else if (poy == 10) {
				(******************(pointer_to_vopfour)[1])(pc, 3, 3, slap);
				//gomoku(pc, 3, 3, slap);
			}
			else if (poy == 13) {
				(******************(pointer_to_vopfour)[1])(pc, 3, 4, slap);
				//gomoku(pc, 3, 4, slap);
			}
			else if (poy == 16) {
				(******************(pointer_to_vopfour)[1])(pc, 3, 5, slap);
				//gomoku(pc, 3, 5, slap);
			}
		}
		else if (pox == 33) {
			if (poy == 1) {
				(******************(pointer_to_vopfour)[1])(pc, 4, 0, slap);
				//gomoku(pc, 4, 0, slap);
			}
			else if (poy == 4) {
				(******************(pointer_to_vopfour)[1])(pc, 4, 1, slap);
				//gomoku(pc, 4, 1, slap);
			}
			else if (poy == 7) {
				(******************(pointer_to_vopfour)[1])(pc, 4, 2, slap);
				//gomoku(pc, 4, 2, slap);
			}
			else if (poy == 10) {
				(******************(pointer_to_vopfour)[1])(pc, 4, 3, slap);
				//gomoku(pc, 4, 3, slap);
			}
			else if (poy == 13) {
				(******************(pointer_to_vopfour)[1])(pc, 4, 4, slap);
				//gomoku(pc, 4, 4, slap);
			}
			else if (poy == 16) {
				(******************(pointer_to_vopfour)[1])(pc, 4, 5, slap);
				//gomoku(pc, 4, 5, slap);
			}
		}
		else if (pox == 40) {
			if (poy == 1) {
				(******************(pointer_to_vopfour)[1])(pc, 5, 0, slap);
				//gomoku(pc, 5, 0, slap);
			}
			else if (poy == 4) {
				(******************(pointer_to_vopfour)[1])(pc, 5, 1, slap);
				//gomoku(pc, 5, 1, slap);
			}
			else if (poy == 7) {
				(******************(pointer_to_vopfour)[1])(pc, 5, 2, slap);
				//gomoku(pc, 5, 2, slap);
			}
			else if (poy == 10) {
				(******************(pointer_to_vopfour)[1])(pc, 5, 3, slap);
				//gomoku(pc, 5, 3, slap);
			}
			else if (poy == 13) {
				(******************(pointer_to_vopfour)[1])(pc, 5, 4, slap);
				//gomoku(pc, 5, 4, slap);
			}
			else if (poy == 16) {
				(******************(pointer_to_vopfour)[1])(pc, 5, 5, slap);
				//gomoku(pc, 5, 5, slap);
			}
		}
		else if (pox == 47) {
			if (poy == 1) {
				(******************(pointer_to_vopfour)[1])(pc, 6, 0, slap);
				//gomoku(pc, 6, 0, slap);
			}
			else if (poy == 4) {
				(******************(pointer_to_vopfour)[1])(pc, 6, 1, slap);
				//gomoku(pc, 6, 1, slap);
			}
			else if (poy == 7) {
				(******************(pointer_to_vopfour)[1])(pc, 6, 2, slap);
				//gomoku(pc, 6, 2, slap);
			}
			else if (poy == 10) {
				(******************(pointer_to_vopfour)[1])(pc, 6, 3, slap);
				//gomoku(pc, 6, 3, slap);
			}
			else if (poy == 13) {
				(******************(pointer_to_vopfour)[1])(pc, 6, 4, slap);
				//gomoku(pc, 6, 4, slap);
			}
			else if (poy == 16) {
				(******************(pointer_to_vopfour)[1])(pc, 6, 5, slap);
				//gomoku(pc, 6, 5, slap);
			}
		}
		else if (pox == 54) {
			if (poy == 1) {
				(******************(pointer_to_vopfour)[1])(pc, 7, 0, slap);
				//gomoku(pc, 7, 0, slap);
			}
			else if (poy == 4) {
				(******************(pointer_to_vopfour)[1])(pc, 7, 1, slap);
				//gomoku(pc, 7, 1, slap);
			}
			else if (poy == 7) {
				(******************(pointer_to_vopfour)[1])(pc, 7, 2, slap);
				//gomoku(pc, 7, 2, slap);
			}
			else if (poy == 10) {
				(******************(pointer_to_vopfour)[1])(pc, 7, 3, slap);
				//gomoku(pc, 7, 3, slap);
			}
			else if (poy == 13) {
				(******************(pointer_to_vopfour)[1])(pc, 7, 4, slap);
				//gomoku(pc, 7, 4, slap);
			}
			else if (poy == 16) {
				(******************(pointer_to_vopfour)[1])(pc, 7, 5, slap);
				//gomoku(pc, 7, 5, slap);
			}
		}
		else if (pox == 61) {
			if (poy == 1) {
				(******************(pointer_to_vopfour)[1])(pc, 8, 0, slap);
				//gomoku(pc, 8, 0, slap);
			}
			else if (poy == 4) {
				(******************(pointer_to_vopfour)[1])(pc, 8, 1, slap);
				//gomoku(pc, 8, 1, slap);
			}
			else if (poy == 7) {
				(******************(pointer_to_vopfour)[1])(pc, 8, 2, slap);
				//gomoku(pc, 8, 2, slap);
			}
			else if (poy == 10) {
				(******************(pointer_to_vopfour)[1])(pc, 8, 3, slap);
				//gomoku(pc, 8, 3, slap);
			}
			else if (poy == 13) {
				(******************(pointer_to_vopfour)[1])(pc, 8, 4, slap);
				//gomoku(pc, 8, 4, slap);
			}
			else if (poy == 16) {
				(******************(pointer_to_vopfour)[1])(pc, 8, 5, slap);
				//gomoku(pc, 8, 5, slap);
			}
		}
		else if (pox == 68) {
			if (poy == 1) {
				(******************(pointer_to_vopfour)[1])(pc, 9, 0, slap);
				//gomoku(pc, 9, 0, slap);
			}
			else if (poy == 4) {
				(******************(pointer_to_vopfour)[1])(pc, 9, 1, slap);
				//gomoku(pc, 9, 1, slap);
			}
			else if (poy == 7) {
				(******************(pointer_to_vopfour)[1])(pc, 9, 2, slap);
				//gomoku(pc, 9, 2, slap);
			}
			else if (poy == 10) {
				(******************(pointer_to_vopfour)[1])(pc, 9, 3, slap);
				//gomoku(pc, 9, 3, slap);
			}
			else if (poy == 13) {
				(******************(pointer_to_vopfour)[1])(pc, 9, 4, slap);
				//gomoku(pc, 9, 4, slap);
			}
			else if (poy == 16) {
				(******************(pointer_to_vopfour)[1])(pc, 9, 5, slap);
				//gomoku(pc, 9, 5, slap);
			}
		}
	}
	return;
}

void gomoku(char *(*picture)[10], int x, int y, int slap) {
	int i=0, j=0;
	if (slap == 0) {
		for (i = 5; i >= 0; i--) {
			if (*(*(picture + i) + x) == "  "){  //顯示要放子的所有資訊在視窗右邊
				/*if (global_color_number < 15) {
					global_color_number++;
					psetcolor(global_color_number); //SetColor();
				}
				else {
					global_color_number = 0;
					psetcolor(global_color_number);
				}*/
				printf("Place ● in Col %d    ", pox);
				gotoxy(pox, 1 + i * 3);
				(*psetcolor)(2);
				printf("●");
				*(*(picture + i) + x) = (char *) "●";
				if (pointer_to_check_win(picture, i, x, (char *)"●")) {
					if (global_color_number < 15) {
						global_color_number++;
						psetcolor(global_color_number); //SetColor();
					}
					else {
						global_color_number = 0;
						psetcolor(global_color_number);
					}
					gotoxy(79, 13);
					cout << "● win this game" << endl;
					Sleep(2000);
					system("CLS");
					gotoxy(5, 3);
					cout << "● win this game" << endl;
					system("pause");
					exit(0);
				}
				success = !success;
				return ;
			}
		}
		printf("this Place isn't void");
	}
	else {
		for (i = 5; i >= 0; i--) {
			if (*(*(picture + i) + x) == "  ") {
				/*if (global_color_number < 15) {
				global_color_number++;
				psetcolor(global_color_number); //SetColor();
				}
				else {
				global_color_number = 0;
				psetcolor(global_color_number);
				}*/
				printf("Place ○ in Col %d    ", pox);
				gotoxy(pox, 1 + i * 3);
				(*psetcolor)(2);
				printf("○");
				*(*(picture + i) + x) = (char *) "○";
				if (pointer_to_check_win(picture, i, x, (char *)"○")) {
					if (global_color_number < 15) {
						global_color_number++;
						psetcolor(global_color_number); //SetColor();
					}
					else {
						global_color_number = 0;
						psetcolor(global_color_number);
					}
					gotoxy(79, 13);
					cout << "○ win this game" << endl;
					Sleep(2000);
					system("CLS");
					gotoxy(5, 3);
					cout << "○ win this game" << endl;
					system("pause");
					exit(0);
				}
				success = !success;
				return;
			}
		}
		printf("this Place isn't void");
	}
}

int Flat(char *(*pc)[10],int x,int y) {
	int i = 0, j = 0;
	for (i = 0; i < y; i++) {
		for (j = 0; j < x; j++) {
			if (*(*(pc + i) + j) == "  ") {
				return 0;
			}
		}
	}
	return 1;
}

void Start_screen(void) {
	system("CLS");
	if (call == 0) {
		label:
		gotoxy(10, 3);
		cout << "**********************************************************************************" << endl;
		gotoxy(10, 4);
		cout << "*                                                                                *" << endl;
		gotoxy(10, 5);
		cout << "*                                                                                *" << endl;
		gotoxy(10, 6);
		cout << "*             Welcome to play Puzzles Bingo Game!!!                              *";
		gotoxy(10, 7);
		cout << "*                                                                                *";
		gotoxy(10, 8);
		cout << "*                                                                                *";
		gotoxy(10, 9);
		cout << "*           1.  Use Arrow keys to move the cursor                                *";
		gotoxy(10, 10);
		cout << "*                                                                                *";
		gotoxy(10, 11);
		cout << "*                                                                                *";
		gotoxy(10, 12);
		cout << "*           2.  Use Enter keys to place content                                  *";
		gotoxy(10, 13);
		cout << "*                                                                                *";
		gotoxy(10, 14);
		cout << "*                                                                                *";
		gotoxy(10, 15);
		cout << "*           3.  The same character is connected into four winning                *";
		gotoxy(10, 16);
		cout << "*                                                                                *";
		gotoxy(10, 17);
		cout << "*                                                                                *";
		gotoxy(10, 18);
		cout << "*           4.  Every piece will go down until encountering obstacles            *";
		gotoxy(10, 19);
		cout << "*                                                                                *";
		gotoxy(10, 20);
		cout << "*                                                                                *";
		gotoxy(10, 21);
		cout << "*           5.  You can control background color and foreground color            *";
		gotoxy(10, 22);
		cout << "*                                                                                *";
		gotoxy(10, 23);
		cout << "**********************************************************************************" << endl;
		gotoxy(10, 24);
		if (call != 0) goto label1;
		system("pause");
	}
	else {
		goto label;
		label1:
		Sleep(2000);
		//_sleep(3000);
		system("CLS");
		return ;
	}
	system("CLS");
}

void change_color(int background,int forecolor) {
	// background - color = 0 
	if (background == 0 && forecolor == 0) {
		system("color 00");
	}
	else if (background == 0 && forecolor == 1) {
		system("color 01");
	}
	else if (background == 0 && forecolor == 2) {
		system("color 02");
	}
	else if (background == 0 && forecolor == 3) {
		system("color 03");
	}
	else if (background == 0 && forecolor == 4) {
		system("color 04");
	}
	else if (background == 0 && forecolor == 5) {
		system("color 05");
	}
	else if (background == 0 && forecolor == 6) {
		system("color 06");
	}
	else if (background == 0 && forecolor == 7) {
		system("color 07");
	}// background - color = 1
	else if (background == 1 && forecolor == 0) {
		system("color 10");
	}
	else if (background == 1 && forecolor == 1) {
		system("color 11");
	}
	else if (background == 1 && forecolor == 2) {
		system("color 12");
	}
	else if (background == 1 && forecolor == 3) {
		system("color 13");
	}
	else if (background == 1 && forecolor == 4) {
		system("color 14");
	}
	else if (background == 1 && forecolor == 5) {
		system("color 15");
	}
	else if (background == 1 && forecolor == 6) {
		system("color 16");
	}
	else if (background == 1 && forecolor == 7) {
		system("color 17");
	}
	else if (background == 2 && forecolor == 0) {
		system("color 20");
	}
	else if (background == 2 && forecolor == 1) {
		system("color 21");
	}
	else if (background == 2 && forecolor == 2) {
		system("color 22");
	}
	else if (background == 2 && forecolor == 3) {
		system("color 23");
	}
	else if (background == 2 && forecolor == 4) {
		system("color 24");
	}
	else if (background == 2 && forecolor == 5) {
		system("color 25");
	}
	else if (background == 2 && forecolor == 6) {
		system("color 26");
	}
	else if (background == 2 && forecolor == 7) {
		system("color 27");
	} // background-color = 3
	else if (background == 3 && forecolor == 0) {
		system("color 30");
	}
	else if (background == 3 && forecolor == 1) {
		system("color 31");
	}
	else if (background == 3 && forecolor == 2) {
		system("color 32");
	}
	else if (background == 3 && forecolor == 3) {
		system("color 33");
	}
	else if (background == 3 && forecolor == 4) {
		system("color 34");
	}
	else if (background == 3 && forecolor == 5) {
		system("color 35");
	}
	else if (background == 3 && forecolor == 6) {
		system("color 36");
	}
	else if (background == 3 && forecolor == 7) {
		system("color 37");
	}// background - color = 4
	else if (background == 4 && forecolor == 0) {
		system("color 40");
	}
	else if (background == 4 && forecolor == 1) {
		system("color 41");
	}
	else if (background == 4 && forecolor == 2) {
		system("color 42");
	}
	else if (background == 4 && forecolor == 3) {
		system("color 43");
	}
	else if (background == 4 && forecolor == 4) {
		system("color 44");
	}
	else if (background == 4 && forecolor == 5) {
		system("color 45");
	}
	else if (background == 4 && forecolor == 6) {
		system("color 46");
	}
	else if (background == 4 && forecolor == 7) {
		system("color 47");
	} // background - color = 5
	else if (background == 5 && forecolor == 0) {
		system("color 50");
	}
	else if (background == 5 && forecolor == 1) {
		system("color 51");
	}
	else if (background == 5 && forecolor == 2) {
		system("color 52");
	}
	else if (background == 5 && forecolor == 3) {
		system("color 53");
	}
	else if (background == 5 && forecolor == 4) {
		system("color 54");
	}
	else if (background == 5 && forecolor == 5) {
		system("color 55");
	}
	else if (background == 5 && forecolor == 6) {
		system("color 56");
	}
	else if (background == 5 && forecolor == 7) {
		system("color 57");
	}// background-color = 6
	else if (background == 6 && forecolor == 0) {
		system("color 60");
	}
	else if (background == 6 && forecolor == 1) {
		system("color 61");
	}
	else if (background == 6 && forecolor == 2) {
		system("color 62");
	}
	else if (background == 6 && forecolor == 3) {
		system("color 63");
	}
	else if (background == 6 && forecolor == 4) {
		system("color 64");
	}
	else if (background == 6 && forecolor == 5) {
		system("color 65");
	}
	else if (background == 6 && forecolor == 6) {
		system("color 66");
	}
	else if (background == 6 && forecolor == 7) {
		system("color 67");
	}// background-color = 7
	else if (background == 7 && forecolor == 0) {
		system("color 70");
	}
	else if (background == 7 && forecolor == 1) {
		system("color 71");
	}
	else if (background == 7 && forecolor == 2) {
		system("color 72");
	}
	else if (background == 7 && forecolor == 3) {
		system("color 73");
	}
	else if (background == 7 && forecolor == 4) {
		system("color 74");
	}
	else if (background == 7 && forecolor == 5) {
		system("color 75");
	}
	else if (background == 7 && forecolor == 6) {
		system("color 76");
	}
	else if (background == 7 && forecolor == 7) {
		system("color 77");
	}
}

void SetCursorVisible(BOOL Visible, DWORD Size)
{
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = Visible; // 是否可視
	cci.dwSize = Size; // 設定大小,1~100
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void setColor(int color) // 設定前景及背景顏色
{
	switch (color)
	{
	case 0:    // White on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED |
			FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case 1:    // Red on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED);
		break;
	case 2:    // Green on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		break;
	case 3:    // Yellow on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED |
			FOREGROUND_GREEN);
		break;
	case 4:    // Blue on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_BLUE);
		break;
	case 5:    // Magenta on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED |
			FOREGROUND_BLUE);
		break;
	case 6:    // Cyan on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_GREEN |
			FOREGROUND_BLUE);
		break;
	case 7:    // Black on Gray
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_INTENSITY | BACKGROUND_INTENSITY);
		break;
	case 8:    // Black on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN |
			BACKGROUND_BLUE);
		break;
	case 9:    // Red on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN |
			BACKGROUND_BLUE |
			FOREGROUND_RED);
		break;
	case 10:    // Green on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN |
			BACKGROUND_BLUE | FOREGROUND_GREEN);
		break;
	case 11:    // Yellow on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN |
			BACKGROUND_BLUE | FOREGROUND_RED |
			FOREGROUND_GREEN);
		break;
	case 12:    // Blue on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN |
			BACKGROUND_BLUE | FOREGROUND_BLUE);
		break;
	case 13:    // Magenta on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN |
			BACKGROUND_BLUE | FOREGROUND_RED |
			FOREGROUND_BLUE);
		break;
	case 14:    // Cyan on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN |
			BACKGROUND_BLUE | FOREGROUND_GREEN |
			FOREGROUND_BLUE);
		break;
	case 15:    // White on White
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_INTENSITY | FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_GREEN |
			BACKGROUND_BLUE | FOREGROUND_RED |
			FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	default:    // White on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED |
			FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	}
}

int check_win(char *(*pc)[10], int y, int x,char *pcheck) {
	int wincheck = 0;
	int road_eight = 0; // 八路判斷
	int road_three = 0; // 三路判斷
	int i = 0, j = 0;
	if (y != 5 && y != 0 && x != 0 && x != 9) {
		for (i = y; i > -1; i--) {  // ONE  ↑ check
			if (*(*(pc + i) + x) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = y; i < 6; i++) { // TWO  ↓ check
			if (*(*(pc + i) + x) == pcheck) {
				wincheck++;
				/*gotoxy(79, 15);
				cout << wincheck << "↓";
				Sleep(2000);*/
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x; i > -1; i--) { // THREE  ← check
			if (*(*(pc + y) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x; i < 10; i++) { // FOUR  → check
			if (*(*(pc + y) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x, j = y; j > -1, i > -1; i--, j--) { // FIVE  ↖ check
			if (*(*(pc + j) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x, j = y; j > -1, i < 10; i++, j--) { // SIX  ↗ check
			if (*(*(pc + j) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x, j = y; j < 6, i > -1; i--, j++) { //  SEVEN  ↙ check
			if (*(*(pc + j) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x, j = y; j < 6, i < 10; i++, j++) { // EIGHT  ↘ check
			if (*(*(pc + j) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		return 0;
	}
	else if (y == 0 && x != 0 && x!=9) { // 五路判斷 
		for (i = y; i < 6; i++) { // TWO  ↓ check
			if (*(*(pc + i) + x) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x; i > -1; i--) { // THREE  ← check
			if (*(*(pc + y) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x; i < 10; i++) { // FOUR  → check
			if (*(*(pc + y) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x, j = y; j < 6, i > -1; i--, j++) { //  SEVEN  ↙ check
			if (*(*(pc + j) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x, j = y; j < 6, i < 10; i++, j++) { // EIGHT  ↘ check
			if (*(*(pc + j) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		return 0;
	}
	else if (y != 0 && x == 0 && y!=5) { // 五路判斷
		for (i = y; i > -1; i--) {  // ONE  ↑ check
			if (*(*(pc + i) + x) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = y; i < 6; i++) { // TWO  ↓ check
			if (*(*(pc + i) + x) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x; i < 10; i++) { // FOUR  → check
			if (*(*(pc + y) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x, j = y; j > -1, i < 10; i++, j--) { // SIX  ↗ check
			if (*(*(pc + j) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x, j = y; j < 6, i < 10; i++, j++) { // EIGHT  ↘ check
			if (*(*(pc + j) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		return 0;
	}
	else if (y != 0 && x == 9 && y!=5) { // 五路判斷
		for (i = y; i > -1; i--) {  // ONE  ↑ check
			if (*(*(pc + i) + x) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = y; i < 6; i++) { // TWO  ↓ check
			if (*(*(pc + i) + x) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x; i > -1; i--) { // THREE  ← check
			if (*(*(pc + y) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x, j = y; j > -1, i > -1; i--, j--) { // FIVE  ↖ check
			if (*(*(pc + j) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x, j = y; j < 6, i > -1; i--, j++) { //  SEVEN  ↙ check
			if (*(*(pc + j) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		return 0;
	}
	else if (y == 5 && x != 0 && x != 9) { // 五路判斷 
		for (i = y; i > -1; i--) {  // ONE  ↑ check
			if (*(*(pc + i) + x) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x; i > -1; i--) { // THREE  ← check
			if (*(*(pc + y) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x; i < 10; i++) { // FOUR  → check
			if (*(*(pc + y) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x, j = y; j > -1, i > -1; i--, j--) { // FIVE  ↖ check
			if (*(*(pc + j) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x, j = y; j > -1, i < 10; i++, j--) { // SIX  ↗ check
			if (*(*(pc + j) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		return 0;
	}
	else if (y == 0 && x == 0) { // 三路判斷
		for (i = y; i < 6; i++) { // TWO  ↓ check
			if (*(*(pc + i) + x) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x; i < 10; i++) { // FOUR  → check
			if (*(*(pc + y) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x, j = y; j < 6, i < 10; i++, j++) { // EIGHT  ↘ check
			if (*(*(pc + j) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		return 0;
	}
	else if (y == 5 && x == 0) { // 三路判斷
		for (i = x, j = y; j > -1, i < 10; i++, j--) { // SIX  ↗ check
			if (*(*(pc + j) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = y; i > -1; i--) {  // ONE  ↑ check
			if (*(*(pc + i) + x) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x; i < 10; i++) { // FOUR  → check
			if (*(*(pc + y) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		return 0;
	}
	else if (y == 0 && x == 9) { // 三路判斷
		for (i = x; i > -1; i--) { // THREE  ← check
			if (*(*(pc + y) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = y; i < 6; i++) { // TWO  ↓ check
			if (*(*(pc + i) + x) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x, j = y; j < 6, i > -1; i--, j++) { //  SEVEN  ↙ check
			if (*(*(pc + j) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		return 0;
	}
	else if (y == 5 && x == 9) { // 三路判斷
		for (i = x; i > -1; i--) { // THREE  ← check
			if (*(*(pc + y) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = y; i > -1; i--) {  // ONE  ↑ check
			if (*(*(pc + i) + x) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		wincheck = 0;
		for (i = x, j = y; j > -1, i > -1; i--, j--) { // FIVE  ↖ check
			if (*(*(pc + j) + i) == pcheck) {
				wincheck++;
				if (wincheck == 4) return 1;
			}
			else {
				wincheck = 0;
				break;
			}
		}
		return 0;
	}
	return 0;
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