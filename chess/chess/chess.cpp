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
void Start_screen(void);
void (*pointer_to_start)(void) = Start_screen; // pointer to start_screen function
using namespace std;

int main(int argc, char **argv) {
	int i=0, j=0, number_pox=0,number_poy=0;
	int slap = 0;
	int fcolor = 0, bcolor = 3;
	char *(*picture)[10];
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
	(******************pointer_to_start)();
	system("color 30");
	initialization_map(picture);
	draw_picture(picture);
	gotoxy(79, 1);
	cout << "backgroundcolor = " + color_list[bcolor];
	gotoxy(79, 3);
	cout << "forecolor = " + color_table[fcolor];
	gotoxy(79, 5);
	slap == 0 ? printf("● times") : printf("○ times");
	gotoxy(pox, poy);
	while (1) {
		position = _getch();
		gotoxy(79,5);
		slap == 0 ? printf("● times") : printf("○ times");
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
		else if (position == 102) {
			if (fcolor < 7) {
				fcolor++;
			}
			else {
				fcolor = 0;
			}
			gotoxy(79, 3);
			cout << "forecolor = " + color_table[fcolor];
			//if (fcolor==)
			//system();
			gotoxy(pox, poy);
		}
		else if (position == 98) {
			if (bcolor < 7) {
				bcolor++;
			}
			else {
				bcolor = 0;
			}
			gotoxy(79, 1);
			cout << "backgroundcolor = " + color_list[bcolor];
			gotoxy(pox, poy);
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
				printf("Place ● in Col %d    ", pox);
				gotoxy(pox, 1 + i * 3);
				printf("●");
				*(*(picture + i) + x) = (char *) "●";
				success = !success;
				return ;
			}
		}
		printf("this Place isn't void");
	}
	else {
		for (i = 5; i >= 0; i--) {
			if (*(*(picture + i) + x) == "  ") {
				printf("Place ○ in Col %d    ", pox);
				gotoxy(pox, 1 + i * 3);
				printf("○");
				*(*(picture + i) + x) = (char *) "○";
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
	system("color 0A");
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
	system("pause");
	//Sleep(2000);
	//_sleep(2000);
	system("CLS");
}
/*if (*(*(picture + y) + x) == "  ") {
			printf("Place ● in Col %d    ", pox);
			gotoxy(pox, poy);
			printf("●");
			*(*(picture + y) + x) = (char *) "●";
		}
		else {
			printf("this Place isn't void");
			//printf("\n %d %d", y, x);
			//slap = !slap;
}*/
/*if (*(*(picture + y) + x) == "  ") {
			printf("Place ○ in Col %d    ", pox);
			gotoxy(pox, poy);
			printf("○");
			*(*(picture + y) + x) = (char *) "○";
		}
		else {
			printf("this Place isn't void");
			//printf("\n %d %d", y, x);
			//slap = !slap;
	}*/
/*int check_block(int (*pblock)[10],int test,int block) {
	if (*(*(pblock + test) + block) == 0) {
		return block;
	}
	else {
		check_block(pblock,test,block-1);
	}
}*/
