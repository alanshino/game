#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <conio.h>
#include <windows.h>
void print_draw(int (*pc)[3]);
void gotoxy(int xpos, int ypos);
void showCursor(int visible);
int pox,poy;
void up(void);
void down(void);
void left(void);
void right(void);
void circle(int (*pi)[3]);
void forkk(int (*pf)[3]);
int win_check_circle(int (*pc)[3]);
int win_check_fork(int (*pc)[3]);

int main(int argc,char **argv)
{
    char position;
    int picture[3][3]={0};
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            picture[i][j]='-';
        }
    }
    pox=5;
    poy=2;
    print_draw(picture);
    gotoxy(5,2);
    while (1){
        position=getch();
        if (position==111){
            circle(picture);
            if (win_check_circle(picture)){
                system("CLS");
                gotoxy(3,2);
                printf(" O Circle is win the game !!!\n\n");
                gotoxy(3,5);
                system("pause");
                exit(0);
            }
        }else if (position==120){
            forkk(picture);
            if (win_check_fork(picture)){
                system("CLS");
                gotoxy(3,2);
                printf(" X Fork is win the game !!!\n\n");
                gotoxy(3,5);
                system("pause");
                exit(0);
            }
        }else if (position==-32){
            position=getch();
            if (position!=0){
                switch (position){
                    case 72:
                        up();
                        break;
                    case 80:
                        down();
                        break;
                    case 75:
                        left();
                        break;
                    case 77:
                        right();
                        break;
                }
            }
        }
    }
    return 0;
}

void print_draw(int (*pc)[3]){
    system("CLS");
    printf("        |     |     \n");
    printf("     %c  |  %c  |  %c \n", *(*(pc+0)+0), *(*(pc+0)+1), *(*(pc+0)+2));
    printf("   _____|_____|_____\n");
    printf("        |     |     \n");
    printf("     %c  |  %c  |  %c \n", *(*(pc+1)+0), *(*(pc+1)+1), *(*(pc+1)+2));
    printf("   _____|_____|_____\n");
    printf("        |     |     \n");
    printf("     %c  |  %c  |  %c \n", *(*(pc+2)+0), *(*(pc+2)+1), *(*(pc+2)+2));
    printf("        |     |     \n\n");
}

void gotoxy(int xpos, int ypos){
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput,scrn);
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

void up(void){
    if (poy>2)
        gotoxy(pox,poy-=3);
    else
        gotoxy(pox,poy);
}

void down(void){
    if (poy<6)
        gotoxy(pox,poy+=3);
    else
        gotoxy(pox,poy);
}

void left(void){
    if (pox>5)
        gotoxy(pox-=6,poy);
    else
        gotoxy(pox,poy);
}

void right(void){
    if (pox<17)
        gotoxy(pox+=6,poy);
    else
        gotoxy(pox,poy);
}

void circle(int (*pi)[3]){
    if (pox==5 && poy==2){
        if (*(*(pi+0)+0)=='-'){
            *(*(pi+0)+0)='O';
            print_draw(pi);
            gotoxy(pox,poy);
        }
    }else if (pox==5 && poy==5){
        if (*(*(pi+1)+0)=='-'){
            *(*(pi+1)+0)='O';
            print_draw(pi);
            gotoxy(pox,poy);
        }
    }else if (pox==5 && poy==8){
        if (*(*(pi+2)+0)=='-'){
            *(*(pi+2)+0)='O';
            print_draw(pi);
            gotoxy(pox,poy);
        }
    }else if (pox==11 && poy==2){
        if (*(*(pi+0)+1)=='-'){
            *(*(pi+0)+1)='O';
            print_draw(pi);
            gotoxy(pox,poy);
        }
    }else if (pox==11 && poy==5){
        if (*(*(pi+1)+1)=='-'){
            *(*(pi+1)+1)='O';
            print_draw(pi);
            gotoxy(pox,poy);
        }
    }else if (pox==11 && poy==8){
        if (*(*(pi+2)+1)=='-'){
            *(*(pi+2)+1)='O';
            print_draw(pi);
            gotoxy(pox,poy);
        }
    }else if (pox==17 && poy==2){
        if (*(*(pi+0)+2)=='-'){
            *(*(pi+0)+2)='O';
            print_draw(pi);
            gotoxy(pox,poy);
        }
    }else if (pox==17 && poy==5){
        if (*(*(pi+1)+2)=='-'){
            *(*(pi+1)+2)='O';
            print_draw(pi);
            gotoxy(pox,poy);
        }
    }else if (pox==17 && poy==8){
        if (*(*(pi+2)+2)=='-'){
            *(*(pi+2)+2)='O';
            print_draw(pi);
            gotoxy(pox,poy);
        }
    }
}

void forkk(int (*pf)[3]){
    if (pox==5 && poy==2){
        if (*(*(pf+0)+0)=='-'){
            *(*(pf+0)+0)='X';
            print_draw(pf);
            gotoxy(pox,poy);
        }
    }else if (pox==5 && poy==5){
        if (*(*(pf+1)+0)=='-'){
            *(*(pf+1)+0)='X';
            print_draw(pf);
            gotoxy(pox,poy);
        }
    }else if (pox==5 && poy==8){
        if (*(*(pf+2)+0)=='-'){
            *(*(pf+2)+0)='X';
            print_draw(pf);
            gotoxy(pox,poy);
        }
    }else if (pox==11 && poy==2){
        if (*(*(pf+0)+1)=='-'){
            *(*(pf+0)+1)='X';
            print_draw(pf);
            gotoxy(pox,poy);
        }
    }else if (pox==11 && poy==5){
        if (*(*(pf+1)+1)=='-'){
            *(*(pf+1)+1)='X';
            print_draw(pf);
            gotoxy(pox,poy);
        }
    }else if (pox==11 && poy==8){
        if (*(*(pf+2)+1)=='-'){
            *(*(pf+2)+1)='X';
            print_draw(pf);
            gotoxy(pox,poy);
        }
    }else if (pox==17 && poy==2){
        if (*(*(pf+0)+2)=='-'){
            *(*(pf+0)+2)='X';
            print_draw(pf);
            gotoxy(pox,poy);
        }
    }else if (pox==17 && poy==5){
        if (*(*(pf+1)+2)=='-'){
            *(*(pf+1)+2)='X';
            print_draw(pf);
            gotoxy(pox,poy);
        }
    }else if (pox==17 && poy==8){
        if (*(*(pf+2)+2)=='-'){
            *(*(pf+2)+2)='X';
            print_draw(pf);
            gotoxy(pox,poy);
        }
    }
}

int win_check_circle(int (*pc)[3]){
    if ((*(*(pc+0)+0)=='O'&&*(*(pc+0)+1)=='O'&&*(*(pc+0)+2)=='O')){
        return 1;
    }else if ((*(*(pc+1)+0)=='O'&&*(*(pc+1)+1)=='O'&&*(*(pc+1)+2)=='O')){
        return 1;
    }else if ((*(*(pc+2)+0)=='O'&&*(*(pc+2)+1)=='O'&&*(*(pc+2)+2)=='O')){
        return 1;
    }else if ((*(*(pc+0)+0)=='O'&&*(*(pc+1)+0)=='O'&&*(*(pc+2)+0)=='O')){
        return 1;
    }else if ((*(*(pc+0)+1)=='O'&&*(*(pc+1)+1)=='O'&&*(*(pc+2)+1)=='O')){
        return 1;
    }else if ((*(*(pc+0)+2)=='O'&&*(*(pc+1)+2)=='O'&&*(*(pc+2)+2)=='O')){
        return 1;
    }else if ((*(*(pc+0)+0)=='O'&&*(*(pc+1)+1)=='O'&&*(*(pc+2)+2)=='O')){
        return 1;
    }else if ((*(*(pc+0)+2)=='O'&&*(*(pc+1)+1)=='O'&&*(*(pc+2)+0)=='O')){
        return 1;
    }else{
        return 0;
    }
}

int win_check_fork(int (*pc)[3]){
    if (*(*(pc+0)+0)=='X'&&*(*(pc+0)+1)=='X'&&*(*(pc+0)+2)=='X'){
        return 1;
    }else if ((*(*(pc+1)+0)=='X'&&*(*(pc+1)+1)=='X'&&*(*(pc+1)+2)=='X')){
        return 1;
    }else if ((*(*(pc+2)+0)=='X'&&*(*(pc+2)+1)=='X'&&*(*(pc+2)+2)=='X')){
        return 1;
    }else if ((*(*(pc+0)+0)=='X'&&*(*(pc+1)+0)=='X'&&*(*(pc+2)+0)=='X')){
        return 1;
    }else if ((*(*(pc+0)+1)=='X'&&*(*(pc+1)+1)=='X'&&*(*(pc+2)+1)=='X')){
        return 1;
    }else if ((*(*(pc+0)+2)=='X'&&*(*(pc+1)+2)=='X'&&*(*(pc+2)+2)=='X')){
        return 1;
    }else if ((*(*(pc+0)+0)=='X'&&*(*(pc+1)+1)=='X'&&*(*(pc+2)+2)=='X')){
        return 1;
    }else if ((*(*(pc+0)+2)=='X'&&*(*(pc+1)+1)=='X'&&*(*(pc+2)+0)=='X')){
        return 1;
    }else{
        return 0;
    }
}
