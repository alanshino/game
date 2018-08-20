#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void moramenu(void);
void startgame(int);
void overgame(void);
int same(char *pc,char *ps);

int main(int argc,char **argv){
    int player=0;
    moramenu();
    return 0;
}

void startgame(int times){
    srand(time(NULL));
    char *ppmora=NULL,*pmora=NULL;
    int winner=0,flat=0,lose=0;
    int win=0;
    int computer=0;
    system("CLS");
    ppmora=malloc(sizeof(char)*15);
    label:
    printf("input what you want to mora\n (rock > scissors)\n (cloth > rock)\n (scissors > cloth)\n");
    printf("input ==>>> ");
    scanf("%s",ppmora);
    if (*ppmora!='s'&&*ppmora!='r'&&*ppmora!='c'){
        goto label;
    }
    computer=rand()%3+1;
    switch (computer){
    case 1:
        pmora="scissors";
        break;
    case 2:
        pmora="rock";
        break;
    case 3:
        pmora="cloth";
        break;
    }
    win=same(ppmora,pmora);
    if (win==1){
        winner++;
    }else if (win==0){
        flat++;
    }else{
        lose++;
    }
    times--;
    if (times!=0){
        goto label;
    }
    system("CLS");
    printf("you win %d time%c , lose %d time%c , flat %d time%c\n",winner,(winner>1)?'s':' ',lose,(lose>1)?'s':' ',flat,(flat>1)?'s':' ');
    free(ppmora);
    free(pmora);
}

void overgame(void){
    system("CLS");
    printf("Thank you\n");
    return;
}

int same(char *pc,char *ps){
    char *pcheck=pc,*pcomputer=ps;
    //printf("%p %p\n",pc,ps);
    int n=0;
    while (*pcheck!='\0'){
        if (*pcheck!=*pcomputer){
            n=1;
            break;
        }
        pcheck++;
        pcomputer++;
    }
    if (n==1){
        if (*pc=='r'&&*ps=='s'){
            printf("user winner\n");
            return 1;
        }else if (*pc=='s'&&*ps=='c'){
            printf("user winner\n");
            return 1;
        }else if (*pc=='c'&&*ps=='r'){
            printf("user winner\n");
            return 1;
        }else{
            printf("computer winner\n");
            return 2;
        }
    }else{
        printf("Flat\n");
        return 0;
    }
    //return ;
}

void moramenu(void){
    int i=10;
    char *pc=malloc(sizeof(char)*5);
    char *pc1=malloc(sizeof(char)*10);
    if (pc1==NULL){
        printf("Sorry have an error\n");
        exit(1);
    }
    label:
    printf("Do you want to start Mora game: (Y/y or N/n): ");
    scanf("%s",pc1);
    if (*pc1=='Y'||*pc1=='y'){
        //free(pc1);
        printf("How times do you want to play: ");
        scanf("%s",pc);
        startgame(atoi(pc));
    }else if(*pc1=='N'||*pc1=='n'){
        //free(pc1);
        overgame();
    }else{
        printf("input is error\n");
        fflush(stdin);
        i--;
        if (i==0){
            free(pc1);
            return ;
        }
        goto label;
    }
    free(pc1);
    return ;
}
