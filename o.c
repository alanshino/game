#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>
#include <conio.h>
int check_input(char *);
void go_sign_up(void);
void go_sign_in(void);
void go_Administrator(void);
void Library_menu(void);
void initialization(void);
void gotoxy(int,int);
int Compare_string(char *,char *);
typedef int (*PFunstring)(char*,char*);
typedef void (*PFunvoid)(void);
typedef void (*PFunint)(int,int);
typedef struct Library{
    char *pauthor;
    char *ptitle;
    int books;
    struct Library*pnext;
}library;
void Donation(library *);
typedef void (*PFlibrary)(library*);
void user_account(void);
PFunvoid pfunvoid;
PFunint pfunint;
int *(*arraya(int n))[]{
    int *(*p)[5]=malloc(sizeof(int*)*5);
    return p;
}
static char user_name[20];
static char user_password[20];
static char user_mail[50];
library *plibrary,*current,previous;
void print_library(library *);
int borrow_book(library *);
int Returning_books(library*);
size_t blocks=0;
size_t check=0;
void stock_book(library *);
void copy_string(char *,char *);
PFlibrary pflibrary;

int main(int argc,char **argv){
    pfunvoid=initialization;
    pfunint=gotoxy;
    //PFlibrary pflibrary=Donation;
    (********************pfunvoid)();
    char *pc=malloc(sizeof(char)*20);
    char c;
    (********************pfunint)(4,2);
    printf("歡迎登入圖書館系統\n\n");
    label:
    (********************pfunint)(5,4);
    printf("1 ------ 註冊\n");
    (********************pfunint)(5,5);
    printf("2 ------ 登入\n");
    (********************pfunint)(5,6);
    printf("3 ------ 管理員登入\n");
    (********************pfunint)(5,7);
    printf("請輸入 : ");
    scanf("%s",pc);
    switch (check_input(pc)){
    case 1:
        go_sign_up();
        break;
    case 2:
        go_sign_in();
        break;
    case 3:
        go_Administrator();
        break;
    default:
        printf("your input is error,please check again\n");
        while ((c=getchar())!='\n'&&c!=EOF);
        goto label;
    }
    free(pc);
    free(plibrary);
    return 0;
}

int check_input(char *pc){
    char c;
    if (*pc=='1'){
        //while ((c=getchar())!='\n'&&c!=EOF);
        return 1;
    }else{
        if (*pc=='2'){
            //while ((c=getchar())!='\n'&&c!=EOF);
            return 2;
        }else if (*pc=='3'){
            //while ((c=getchar())!='\n'&&c!=EOF);
            return 3;
        }
    }
    return 0;
}

void go_sign_up(void){
    char c;
    FILE *Fp1;
    Fp1=fopen("user.txt","a+");
    while ((c=getchar())!='\n'&&c!=EOF);
    system("CLS");
    (********************pfunint)(4,2);
    printf("請輸入您的使用者名稱: ");
    scanf("%[^'\n']",user_name);
    while ((c=getchar())!='\n'&&c!=EOF);
    printf("請輸入您的使用者密碼: ");
    scanf("%[^'\n']",user_password);
    while ((c=getchar())!='\n'&&c!=EOF);
    printf("請輸入您的使用者信箱: ");
    scanf("%[^'\n']",user_mail);
    printf("使用者名稱 : %s\n",user_name);
    printf("使用者密碼 : %s\n",user_password);
    printf("使用者信箱 : %s\n",user_mail);
    printf("註冊完成,即將跳轉\n");
    system("pause");
    Library_menu();
}

void go_sign_in(void){
    PFunstring pfunstring=Compare_string;
    char c;
    char *pc=malloc(sizeof(char)*20);
    if (*user_name=='\0'||*user_password=='\0'||*user_mail){
        printf("由於您尚未註冊將,跳轉至註冊頁面\n");
        system("pause");
        go_sign_up();
    }else{
        label:
        while ((c=getchar())!='\n'&&c!=EOF);
        printf("請輸入您的用戶名稱: ");
        scanf("%[^'\n']",pc);
        if (!(*************pfunstring)(pc,user_name)){
            label1:
            while ((c=getchar())!='\n'&&c!=EOF);
            printf("請輸入您的用戶密碼: ");
            scanf("%[^'\n']",pc);
            if (!(*************pfunstring)(pc,user_password)){
                pfunvoid=Library_menu;
                (************pfunvoid)();
            }else{
                printf("用戶密碼輸入有錯誤\n");
                goto label1;
            }
        }else{
            printf("用戶名稱輸入有錯誤\n");
            goto label;
        }
        while ((c=getchar())!='\n'&&c!=EOF);
    }
    free(pc);
}

void go_Administrator(void){

}

void Library_menu(void){
    int user_input=0;char c='\0';
    label:
    for (;;){
        system("CLS");
        printf("感謝您的使用!\n");
        printf("1 ------ 我要借書\n");
        printf("2 ------ 我要還書\n");
        printf("3 ------ 我的帳戶資料\n");
        printf("4 ------ 查詢圖書館藏書\n");
        printf("5 ------ 查詢我的書籍\n");
        printf("6 ------ 我要提供書籍\n");
        printf("7 ------ 我要離開\n");
        printf("請輸入 : ");
        scanf("%d",&user_input);
        if (user_input==1){
            print_library(plibrary);
        }else if (user_input==2){
            Returning_books(plibrary);
        }else if (user_input==3){
            user_account();
        }else if (user_input==4){
            pflibrary=stock_book;
            (************pflibrary)(plibrary);
        }else if (user_input==5){

        }else if (user_input==6){
            pflibrary=Donation;
            (************pflibrary)(plibrary);
        }else if (user_input==7){
            exit(1);
        }else{
            printf("使用者輸入有錯誤\n");
            while ((c=getchar())!='\n'&&c!=EOF);
            goto label;
        }
    }
}

void initialization(void){
    plibrary=malloc(sizeof(library)*15);
    (plibrary+0)->pauthor="尾田榮一郎";
    (plibrary+0)->ptitle="航海王";
    (plibrary+0)->books=24;
    //(plibrary+0)->pnext=(plibrary+1);
    (plibrary+1)->pauthor="岩明均";
    (plibrary+1)->ptitle="寄生獸";
    (plibrary+1)->books=10;
    //(plibrary+1)->pnext=(plibrary+2);
    (plibrary+2)->pauthor="諫山創";
    (plibrary+2)->ptitle="進擊的巨人";
    (plibrary+2)->books=12;
    //(plibrary+2)->pnext=(plibrary+3);
    (plibrary+3)->pauthor="古館春一";
    (plibrary+3)->ptitle="排球少年";
    (plibrary+3)->books=15;
    //(plibrary+3)->pnext=(plibrary+4);
    (plibrary+4)->pauthor="三部敬";
    (plibrary+4)->ptitle="只有我不存在的城市";
    (plibrary+4)->books=14;
    //(plibrary+4)->pnext=(plibrary+5);
    (plibrary+5)->pauthor="大武政夫";
    (plibrary+5)->ptitle="極道超女";
    (plibrary+5)->books=10;
    //(plibrary+5)->pnext=(plibrary+6);
    (plibrary+6)->pauthor="涼川鈴";
    (plibrary+6)->ptitle="遊戲3人娘";
    (plibrary+6)->books=18;
    //(plibrary+6)->pnext=(plibrary+7);
    (plibrary+7)->pauthor="平本Akira";
    (plibrary+7)->ptitle="監獄學園";
    (plibrary+7)->books=11;
    //(plibrary+7)->pnext=(plibrary+8);
    (plibrary+8)->pauthor="瀧本祥子";
    (plibrary+8)->ptitle="爆肝工程師的異世界狂想曲";
    (plibrary+8)->books=15;
    //(plibrary+8)->pnext=(plibrary+9);
    (plibrary+9)->pauthor="白鳥士郎";
    (plibrary+9)->ptitle="龍王的工作";
    (plibrary+9)->books=10;
    (plibrary+10)->pauthor="竹宮悠由子";
    (plibrary+10)->ptitle="TIGER×DRAGON";
    (plibrary+10)->books=13;
    (plibrary+11)->pauthor="伏見司";
    (plibrary+11)->ptitle="情色漫畫老師";
    (plibrary+11)->books=17;
    (plibrary+12)->pauthor="新川直司";
    (plibrary+12)->ptitle="四月是你的謊言";
    (plibrary+12)->books=19;
    (plibrary+13)->pauthor="奧浩哉";
    (plibrary+13)->ptitle="殺戮重生犬屋敷";
    (plibrary+13)->books=9;
    (plibrary+14)->pauthor="渡邊信一郎";
    (plibrary+14)->ptitle="東京殘響";
    (plibrary+14)->books=13;
    for (int i=0;i<14;i++){
        (plibrary+i)->pnext=(plibrary+i+1);
    }
    (plibrary+14)->pnext=NULL;
    blocks=14;
    check=15;
    current=(plibrary+14);
    printf("書名:%s ",(plibrary+0)->ptitle);
    printf("作者:%s ",(plibrary+0)->pauthor);
    printf("冊數:%d ",(plibrary+0)->books);
    //free(plibrary);
}

void gotoxy(int Xposition, int Yposition){
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X=Xposition; scrn.Y=Yposition;
    SetConsoleCursorPosition(hOuput,scrn);
}

int Compare_string(char *puser,char *pcheck){
    while (*puser!='\0'){
        if (*puser==*pcheck){
        }else{
            return 1;
        }
        puser++;
        pcheck++;
    }
    return 0;
}

void print_library(library *pplibrary){
    //int check=0;
    char *pc=malloc(sizeof(char)*30);
    for (int i=0;i<15;i++){
        printf("書籍%2d  %s ",i+1,(pplibrary+i)->ptitle);
        printf(" %s  ",(pplibrary+i)->pauthor);
        printf(" %d\n",(pplibrary+i)->books);
    }
    label:
    check=0;
    printf("請輸入您要借用的書籍: ");
    scanf("%s",pc);
    for (int i=0;i<15;i++){
        if (!(Compare_string(pc,(pplibrary+i)->ptitle))){
            if ((pplibrary+i)->books>0){
                (pplibrary+i)->books--;
                printf("感謝您的借閱,您借的書籍是%s",(plibrary+i)->ptitle);
            }else{
                printf("非常抱歉,您目前借閱的書籍尚無庫存\n");
            }
        }else{
            check++;
        }
    }
    if (check==blocks+1){
        printf("沒有您輸入的書籍,請查核\n");
        goto label;
    }
    free(pc);
}

int Returning_books(library *pplibrary){
    char *pc=malloc(sizeof(char)*30);
    char c;
    int check=0;
    label:
    while ((c=getchar())!='\n'&&c!=EOF);
    printf("請輸入您要歸還的書籍: ");
    scanf("%s",pc);
    for (int i=0;i<15;i++){
        if (!(Compare_string(pc,(pplibrary+i)->ptitle))){
            if ((pplibrary+i)->books>0){
                (pplibrary+i)->books++;
                printf("感謝您的歸還,您歸還的書籍是%s",(plibrary+i)->ptitle);
            }else{
                printf("感謝您的歸還,您歸還的書籍是%s",(plibrary+i)->ptitle);
            }
        }else{
            check++;
        }
    }
    if (check==blocks+1){
        printf("您的輸入有錯誤,請查核\n");
        goto label;
    }
    free(pc);
    return 0;
}

void user_account(void){
    printf("使用者名稱 : %s\n",user_name);
    printf("使用者密碼 : %s\n",user_password);
    printf("使用者信箱 : %s\n",user_mail);
}

void Donation(library *pplibrary){
    char *pc=malloc(sizeof(char)*30);
    assert(pc!=NULL);
    char c;
    int check=0;
    while ((c=getchar())!='\n'&&c!=EOF);
    library *pbooks;
    pbooks=malloc(sizeof(library));
    assert(pbooks!=NULL);
    system("CLS");
    printf("感謝您的捐贈\n");
    printf("輸入您要捐贈的書籍: ");
    scanf("%[^'\n']",pc);
    while (pplibrary!=NULL){
        if (!(Compare_string(pc,pplibrary->ptitle))){
            printf("請輸入您要捐贈的數量: ");
            scanf("%s",pc);
            pplibrary->books+=atoi(pc);
            printf("您捐贈的書籍為%s,目前庫存增加為%d\n",(pplibrary)->ptitle,(pplibrary)->books);
            system("pause");
        }else{
            check++;
        }
        pplibrary=pplibrary->pnext;
    }
  /*  for (int i=0;i<blocks+1;i++){
        if (!(Compare_string(pc,(pplibrary+i)->ptitle))){
            if ((pplibrary+i)->books>0){
                (pplibrary+i)->books++;
                printf("您捐贈的書籍為%s,目前庫存增加為%d\n",(plibrary+i)->ptitle,(plibrary+i)->books);
                system("pause");
            }else{

            }
        }else{
            check++;
        }
    } */
    //system("pause");
    if (check==blocks+1){
        //printf("%s\n",(pplibrary+blocks)->ptitle);
        pbooks->ptitle=malloc(sizeof(char)*20);
        assert(pbooks->ptitle!=NULL);
        copy_string(pc,pbooks->ptitle);
        printf("請輸入您要捐贈的數量: ");
        scanf("%s",pc);
        pbooks->books=atoi(pc);
        pbooks->pauthor="待查證";
        //printf("%s %d\n",pbooks->ptitle,pbooks->books);
        current->pnext=pbooks;
        pbooks->pnext=NULL;
        current=current->pnext;
        blocks++;
        system("pause");
    }
    //system("pause");
    free(pc);
}

void stock_book(library *pplibrary){
    int i=0;
    while (pplibrary!=NULL){
        printf("%d %s ",i+1,pplibrary->ptitle);
        printf("  %s",pplibrary->pauthor);
        printf("  %d\n",pplibrary->books);
        i++;
        pplibrary=pplibrary->pnext;
    }
    system("pause");
    return ;
}

void copy_string(char *pc,char *pbook){
    if ((pc==NULL)||(pbook==NULL)){
        exit(1);
    }
    while (*pc!='\0'){
        *pbook=*pc;
        pc++;
        pbook++;
    }
}
