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
int flat(int (*)[3]);
void (*pvoid_func) (void);
int (*pint_func) (int (*)[3]);
void (*ppox_poy) (int,int);
void (*ppic_func) (int (*)[3]);

int main(int argc,char **argv)
{
    char Code;
    int key=0;
    char position;
    int picture[3][3]={0};
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            picture[i][j]='-';
        }
    }
    pox=5;
    poy=2;
    ppic_func=print_draw;
    //print_draw(picture);
    (************ppic_func)(picture);
    gotoxy(24,2);
    printf("Coordinate Row=5 Col=2");
    gotoxy(5,2);
    while (1){
        if (flat(picture)){
            system("CLS");
            printf("This game is tied\n");
            _sleep(2000);
            //system("psuae");
            system("Tictactoe_direction_control_over.exe");
        }
        position=getch();
        if (position==111){
            circle(picture);
            gotoxy(24,4);
            printf("Place O in Row:%d Col:%d ",pox,poy);
            gotoxy(pox,poy);
            if (win_check_circle(picture)){
                system("CLS");
                gotoxy(3,2);
                printf(" O Circle is win the game !!!\n\n");
                gotoxy(3,5);
                system("pause");
                gotoxy(3,7);
                printf("Do you want to play one again? \n");
                gotoxy(3,9);
                printf("'y' or 'Y' to start new game, 'n' or 'N' to close this game\n");
                gotoxy(3,11);
                printf("Input instruction :  ");
                //while ((Code=getchar())!='\n' && Code!=EOF);
                labelcircle:
                if (key!=0) {
                    system("CLS");
                    printf("your input instruction is error\n");
                    printf("Input instruction :  ");
                }
                scanf("%c",&Code);
                if (Code=='y' || Code=='Y') {system("Tictactoe_direction_control_over.exe");}
                else if (Code=='n' || Code=='N'){
                    gotoxy(3,13);
                    printf("Goobye !!!\n");
                    exit(0);
                }else{
                    if (key==0){
                        gotoxy(3,13);
                        printf("your input instruction is error\n");
                        gotoxy(3,14);
                        system("pause");
                        key++;
                        goto labelcircle;
                    }else{
                        goto labelcircle;
                    }
                }
            }
        }else if (position==120){
            forkk(picture);
            gotoxy(24,4);
            printf("Place X in Row:%d Col:%d ",pox,poy);
            gotoxy(pox,poy);
            if (win_check_fork(picture)){
                system("CLS");
                gotoxy(3,2);
                printf(" X Fork is win the game !!!\n\n");
                gotoxy(3,5);
                system("pause");
                gotoxy(3,7);
                printf("Do you want to play one again?\n");
                //exit(0);
                gotoxy(3,9);
                printf("'y' or 'Y' to start new game, 'n' or 'N' to close this game\n");
                gotoxy(3,11);
                printf("Input instruction :  ");
                //while ((Code=getchar())!='\n' && Code!=EOF);
                labelfork:
                if (key!=0) {
                    system("CLS");
                    printf("your input instruction is error\n");
                    printf("Input instruction :  ");
                }
                scanf("%c",&Code);
                if (Code=='y' || Code=='Y') {system("Tictactoe_direction_control_over.exe");}
                else if (Code=='n' || Code=='N'){
                    gotoxy(3,13);
                    printf("Goobye !!!\n");
                    exit(0);
                }else{
                    if (key==0){
                        gotoxy(3,13);
                        printf("your input instruction is error\n");
                        gotoxy(3,14);
                        system("pause");
                        key++;
                        goto labelfork;
                    }else{
                        goto labelfork;
                    }
                }
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
    gotoxy(24,2);
    printf("Coordinate Row:%d Col:%d ",pox,poy);
    gotoxy(pox,poy);
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
    if (poy>2){
        gotoxy(24,2);
        printf("Coordinate Row:%d Col:%d ",pox,poy-3);
        gotoxy(pox,poy-=3);
    }
    else
        gotoxy(pox,poy);
}

void down(void){
    if (poy<6){
        gotoxy(24,2);
        printf("Coordinate Row:%d Col:%d ",pox,poy+3);
        gotoxy(pox,poy+=3);
    }
    else
        gotoxy(pox,poy);
}

void left(void){
    if (pox>5){
        gotoxy(24,2);
        printf("Coordinate Row:%d Col:%d ",pox-6,poy);
        gotoxy(pox-=6,poy);
    }
    else
        gotoxy(pox,poy);
}

void right(void){
    if (pox<17){
        gotoxy(24,2);
        printf("Coordinate Row:%d Col:%d ",pox+6,poy);
        gotoxy(pox+=6,poy);
    }
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

int flat(int (*pc)[3]){
    int i,j,flat_check=0;
    for (i=0;i<3;i++){
        for (j=0;j<3;j++){
            if (*(*(pc+i)+j)!='-') flat_check++;
        }
    }
    if (flat_check==9){
        return 1;
    }else
        return 0;
}
