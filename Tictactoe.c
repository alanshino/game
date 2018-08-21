#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void initialization(char **p);
void print(char **pc);
void menu(char **pc);
void overgame(void);
void startgame(char **pc);
void wincheck(char **pc);

int times=0;

int main(int argc,char **argv){
    char **pc=NULL;
    pc=malloc(sizeof(char *)*3);
    for (int i=0;i<3;i++){
        *(pc+i)=malloc(sizeof(char));
    }
    initialization(pc);
    print(pc);
    menu(pc);
    for (int i=0;i<3;i++){
        free(*(pc+i));
    }
    free(pc);
    return 0;
}

void initialization(char **p){
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            *(*(p+i)+j)='-';
        }
    }
}

void print(char **pc){
    times++;
    if (times==1){
        printf("already initialization\n");
    }else{
        for (int i=0;i<3;i++){
            for (int j=0;j<3;j++){
                printf("%c ",*(*(pc+i)+j));
            }
            printf("\n");
        }
    }
}

void menu(char **pc){
    char *ps=malloc(sizeof(char)*10);
    label:
    printf("Do you want to start TicTacToe game: (Y/y or N/n): ");
    scanf("%s",ps);
    if (*ps=='Y'||*ps=='y'){
        startgame(pc);
    }else if(*ps=='N'||*ps=='n'){
        overgame();
    }else{
        goto label;
    }
}

void overgame(void){
    system("CLS");
    printf("Thank you\n");
}

void startgame(char **pc){
    srand(time(NULL));
    char c,check;
    int a=0,b=0;
    int *pi=malloc(sizeof(int)*2);
    int *pp=malloc(sizeof(int)*2);
    int **panswer=malloc(sizeof(int *)*3);
    for (int i=0;i<3;i++){
        *(panswer+i)=malloc(sizeof(int)*3);
    }
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            *(*(panswer+i)+j)=0;
        }
    }
    label:
    printf("How You want to attack first or later [ O is first ],[ X is later ]: ");
    scanf("%c%c",&c,&check);
    if (c=='O'||'o'){
        label1:
        printf("input row and col: ");
        for (int i=0;i<2;i++){
            scanf("%d",pi+i);
        }
        if (*(pi+0)>3||*(pi+0)<1||*(pi+1)>3||*(pi+1)<1){
            printf("input is error\n");
            goto label1;
        }else{
            if (*(*(panswer+*(pi+0)-1)+*(pi+1)-1)==0){
                *(*(panswer+*(pi+0)-1)+*(pi+1)-1)=1;
                *(*(pc+*(pi+0)-1)+*(pi+1)-1)='O';
                print(pc);
                label2:
                a=rand()%3+1;
                b=rand()%3+1;
                *(pp+0)=a;
                *(pp+1)=b;
                if (*(*(panswer+*(pp+0)-1)+*(pp+1)-1)==0){
                    *(*(panswer+*(pp+0)-1)+*(pp+1)-1)=1;
                    *(*(pc+*(pp+0)-1)+*(pp+1)-1)='X';
                    print(pc);
                }else{
                    goto label2;
                }
                if (wincheck(pc)){

                }
            }else{
                printf("the block is already put a car\n");
                goto label1;
            }
        }
    }else if (c=='X'||c=='x'){

    }else{
        printf("input is error\n");
        goto label;
    }
}

void wincheck(char **pc){
    if (*(*(pc+0)+0)=='O'&&*(*(pc+0)+1)=='O'&&*(*(pc+0)+2)=='O'){
        return 1;
    }else if (){

    }else if (){

    }
}
