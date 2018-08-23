#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void initialization(char **p);
void print(char **pc);
void menu(char **pc);
void overgame(void);
void startgame(char **pc);
int wincheck(char **pc);
int aicomputer(char **pc);
int originalcheck(char **pc);
void startdouble(char **pc);

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
    char *pi=malloc(sizeof(char)*10);
    label:
    printf("Do you want to start TicTacToe game: (Y/y or N/n): ");
    scanf("%s",ps);
    if (*ps=='Y'||*ps=='y'){
        label1:
        printf("Double play or Single match [(D/d or 2 to Double play),(S/s or 1 to Single match)]: ");
        scanf("%s",pi);
        if (*pi=='D'||*pi=='d'||*pi=='2'){
            startdouble(pc);
        }else if (*pi=='S'||*pi=='s'||*ps=='1'){
            startgame(pc);
        }else{
            goto label1;
        }
    }else if(*ps=='N'||*ps=='n'){
        overgame();
    }else{
        fflush(stdin);
        printf("input is error\n");
        goto label;
    }
    free(ps);
    free(pi);
}

void overgame(void){
    system("CLS");
    printf("Thank you\n");
}

void startgame(char **pc){
    srand(time(NULL));
    char c,check;
    int flat=9;
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
    system("CLS");
    printf("start Single match\n");
    label:
    printf("How you want to attack first or later [ O is first ],[ X is later ]: ");
    fflush(stdin);
    scanf("%c%c",&c,&check);
    if (c=='O'||c=='o'){
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
                    flat=9;
                    for (int i=0;i<3;i++){
                        for (int j=0;j<3;j++){
                            if (*(*(panswer+i)+j)!=0){
                                flat--;
                            }
                        }
                    }
                    if (flat>0){
                        goto label2;
                    }else{
                        printf("Tic Tac Toe is over ,This game is tied\n");
                        exit(1);
                    }
                }
                if (wincheck(pc)){
                    printf("you win!!!\n");
                }else if(aicomputer(pc)){
                    printf("you lose the game\n");
                    //goto label1;
                }else{
                    //printf("you lose the game\n");
                    goto label1;
                }
            }else{
                printf("the block is already put a car\n");
                goto label1;
            }
        }
    }else if (c=='X'||c=='x'){
        label3:
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
                *(*(pc+*(pi+0)-1)+*(pi+1)-1)='X';
                print(pc);
                label4:
                a=rand()%3+1;
                b=rand()%3+1;
                *(pp+0)=a;
                *(pp+1)=b;
                if (*(*(panswer+*(pp+0)-1)+*(pp+1)-1)==0){
                    *(*(panswer+*(pp+0)-1)+*(pp+1)-1)=1;
                    *(*(pc+*(pp+0)-1)+*(pp+1)-1)='O';
                    print(pc);
                }else{
                    goto label4;
                }
                if (aicomputer(pc)){
                    printf("you win!!!\n");
                }else if(wincheck(pc)){
                    printf("you lose the game\n");
                    //goto label3;
                }else{
                    //printf("you lose the game\n");
                    goto label3;
                }
            }else{
                printf("the block is already put a car\n");
                goto label1;
            }
        }
    }else{
        printf("input is error\n");
        goto label;
    }
    for (int i=0;i<3;i++){
        free(*(panswer+i));
    }
    free(panswer);
    free(pi);
    free(pp);
}

int originalcheck(char **pc){
    if ((*(*(pc+0)+0)=='O'&&*(*(pc+0)+1)=='O'&&*(*(pc+0)+2)=='O')||(*(*(pc+0)+0)=='X'&&*(*(pc+0)+1)=='X'&&*(*(pc+0)+2)=='X')){
        return 1;
    }else if ((*(*(pc+1)+0)=='O'&&*(*(pc+1)+1)=='O'&&*(*(pc+1)+2)=='O')||(*(*(pc+1)+0)=='X'&&*(*(pc+1)+1)=='X'&&*(*(pc+1)+2)=='X')){
        return 1;
    }else if ((*(*(pc+2)+0)=='O'&&*(*(pc+2)+1)=='O'&&*(*(pc+2)+2)=='O')||(*(*(pc+2)+0)=='X'&&*(*(pc+2)+1)=='X'&&*(*(pc+2)+2)=='X')){
        return 1;
    }else if ((*(*(pc+0)+0)=='O'&&*(*(pc+1)+0)=='O'&&*(*(pc+2)+0)=='O')||(*(*(pc+0)+0)=='X'&&*(*(pc+1)+0)=='X'&&*(*(pc+2)+0)=='X')){
        return 1;
    }else if ((*(*(pc+0)+1)=='O'&&*(*(pc+1)+1)=='O'&&*(*(pc+2)+1)=='O')||(*(*(pc+0)+1)=='X'&&*(*(pc+1)+1)=='X'&&*(*(pc+2)+1)=='X')){
        return 1;
    }else if ((*(*(pc+0)+2)=='O'&&*(*(pc+1)+2)=='O'&&*(*(pc+2)+2)=='O')||(*(*(pc+0)+2)=='X'&&*(*(pc+1)+2)=='X'&&*(*(pc+2)+2)=='X')){
        return 1;
    }else if ((*(*(pc+0)+0)=='O'&&*(*(pc+1)+1)=='O'&&*(*(pc+2)+2)=='O')||(*(*(pc+0)+0)=='X'&&*(*(pc+1)+1)=='X'&&*(*(pc+2)+2)=='X')){
        return 1;
    }else if ((*(*(pc+0)+2)=='O'&&*(*(pc+1)+1)=='O'&&*(*(pc+2)+0)=='O')||(*(*(pc+0)+2)=='X'&&*(*(pc+1)+1)=='X'&&*(*(pc+2)+0)=='X')){
        return 1;
    }else{
        return 0;
    }
}

int wincheck(char **pc){
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

int aicomputer(char **pc){
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

void startdouble(char **pc){
    int flat=9;
    char *ps=malloc(sizeof(char)*10);
    char c,check;
    int **panswer=malloc(sizeof(int *)*3);
    int *pi=malloc(sizeof(int)*2);
    for (int i=0;i<3;i++){
        *(panswer+i)=malloc(sizeof(int)*3);
    }
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            *(*(panswer+i)+j)=0;
        }
    }
    system("CLS");
    printf("start double player\n");
    label:
    printf("What you want to attack first is 'O' or 'X' : ");
    fflush(stdin);
    scanf("%c%c",&c,&check);
    if (c=='O'||c=='o'){
        label2:
        printf("Player one time\n");
        printf("input row and col: ");
        scanf("%d%d",pi+0,pi+1);
        if (*(pi+0)>3||*(pi+0)<0||*(pi+1)>3||*(pi+1)<0){
            printf("input is error\n");
            goto label2;
        }else{
            if (*(*(panswer+*(pi+0)-1)+*(pi+1)-1)==0){
                *(*(panswer+*(pi+0)-1)+*(pi+1)-1)=1;
                *(*(pc+*(pi+0)-1)+*(pi+1)-1)='O';
                print(pc);
                printf("Change player second operation\n");
                label3:
                printf("input row and col: ");
                scanf("%d%d",pi+0,pi+1);
                if (*(pi+0)>3||*(pi+0)<0||*(pi+1)>3||*(pi+1)<0){
                    printf("input is error\n");
                    goto label3;
                }else{
                    if (*(*(panswer+*(pi+0)-1)+*(pi+1)-1)==0){
                        *(*(panswer+*(pi+0)-1)+*(pi+1)-1)=1;
                        *(*(pc+*(pi+0)-1)+*(pi+1)-1)='X';
                        print(pc);
                    }else{
                        printf("the block is already put a car\n");
                        goto label3;
                    }
                }
                if (wincheck(pc)){
                    printf("Player one wins\n");
                }else if (aicomputer(pc)){
                    printf("Player two wins\n");
                }else{
                    for (int i=0;i<3;i++){
                        for (int j=0;j<3;j++){
                            if (*(*(panswer+i)+j)!=0){
                                flat--;
                            }
                        }
                    }
                    if (flat>0){
                        goto label2;
                    }else{
                        printf("Tic Tac Toe is over ,This game is tied\n");
                        exit(1);
                    }
                }
            }else{
                printf("the block is already put a car\n");
                goto label2;
            }
        }
    }else if (c=='X'||c=='x'){
        label4:
        printf("Player one time\n");
        printf("input row and col: ");
        scanf("%d%d",pi+0,pi+1);
        if (*(pi+0)>3||*(pi+0)<0||*(pi+1)>3||*(pi+1)<0){
            printf("input is error\n");
            goto label4;
        }else{
            if (*(*(panswer+*(pi+0)-1)+*(pi+1)-1)==0){
                *(*(panswer+*(pi+0)-1)+*(pi+1)-1)=1;
                *(*(pc+*(pi+0)-1)+*(pi+1)-1)='X';
                print(pc);
                printf("Change player second operation\n");
                label5:
                printf("input row and col: ");
                scanf("%d%d",pi+0,pi+1);
                if (*(pi+0)>3||*(pi+0)<0||*(pi+1)>3||*(pi+1)<0){
                    printf("input is error\n");
                    goto label5;
                }else{
                    if (*(*(panswer+*(pi+0)-1)+*(pi+1)-1)==0){
                        *(*(panswer+*(pi+0)-1)+*(pi+1)-1)=1;
                        *(*(pc+*(pi+0)-1)+*(pi+1)-1)='O';
                        print(pc);
                    }else{
                        printf("the block is already put a car\n");
                        goto label5;
                    }
                }
                if (wincheck(pc)){
                    printf("Player one wins\n");
                }else if (aicomputer(pc)){
                    printf("Player two wins\n");
                }else{
                    for (int i=0;i<3;i++){
                        for (int j=0;j<3;j++){
                            if (*(*(panswer+i)+j)!=0){
                                flat--;
                            }
                        }
                    }
                    if (flat>0){
                        goto label4;
                    }else{
                        printf("Tic Tac Toe is over ,This game is tied\n");
                        exit(1);
                    }
                }
            }else{
                printf("the block is already put a car\n");
                goto label4;
            }
        }
    }else{
        printf("input is error\n");
        goto label;
    }
    for (int i=0;i<3;i++){
        free(*(panswer+i));
    }
    free(panswer);
    free(pi);
    free(ps);
    return ;
}
