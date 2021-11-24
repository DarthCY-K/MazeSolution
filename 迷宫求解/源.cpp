#include <stdio.h> 
#include <stdlib.h>
#include <conio.h> 
#include <string.h> 
#include <windows.h> 
#include <time.h> 
#define getpch(type) (type*)malloc(sizeof(type)) 
struct mulu                     /*定义目录结构体*/
{
    char name[15];              /*存放目录名*/

    char password[6];           /*如果用户目录时还保存用户密码*/
    char usr[15];               /*目录所属用户*/
    int time[3];                /*创建时间*/
    int son_nu;                 /*子目录数*/
    int wj_nu;                  /*目录下文件数*/
    struct mulu* parent;        /*指向父目录*/
    struct mulu* son[10];       /*最多可以创建十个子目录*/
    struct wenjian* wj[10];     /*最多可以存放十个文件*/

}*root, * p;                  /*p指针用来指向当前目录*/
struct wenjian          /*定义文件结构体*/
{

    char name[15];              /*存放文件名*/
    char usr[15];               /*文件所属用户*/
    int time[3];                /*文件最后修改时间*/
    struct mulu* parent;        /*指向文件所在的目录*/
}*q;
typedef struct mulu MULU;
typedef struct wenjian WJ;
char lujing[20][15];   /*用来记录个路径*/
int lj = 0;              /*记录根目录到当前目录级数,方便打印目录*/
char user[15];         /*记录当前使用系统的用户,便于判断其访问文件权
限*/
char cmd[28][20] =         /*本系统的指令集*/
{ {"CLS"},{"cls"},{"PWD"},{"pwd"},{"LS"},{"ls"},
{"MKDIR"},{"mkdir"},{"RMDIR"},{"rmdir"},{"CD"},
{"cd"},{"VI"},{"vi"},{"RM"},{"rm"},{"COPY"},{"copy"},
{"MV"},{"mv"},{"HELP"},{"help"},{"LOGOUT"},{"logout"},
{"MSD"},{"msd"},{"MVDIR"},{"mvdir"} }
void Gotoxy(int x, int y)
{
    int xx = 0x0b;
    HANDLE hOutput;
    COORD loc;
    loc.X = x;     loc.Y = y;
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, loc);
    return;
}
void ROOT()         /*初始化根目录root*/
{

    int i;
    root = getpch(MULU);
    p = root;
    strcpy(root->name, "root");    /*目录名为root*/
    strcpy(root->usr, root->name); /*目录属主root*/
    root->son_nu = 0;               /*用户个数为0*/
    root->wj_nu = 0;                /*文件个数为0*/
    root->parent = 0;               /*根目录是最上一级了*/
    for (i = 0; i < 10; i++)
    {

        root->son[i] = 0;
        root->wj[i] = 0;
    }
    strcpy(lujing[0], "root");     /*保存路径信息,
供打印路径使用*/
    lj += 1;
}
int LOGIN()   /*登陆函数,包括用户名和用户密码检验,在登陆过程中成功则
返回1,失败返回0*/
{
    char a[15];                /*用于存放用户名*/
    char b[6];                 /*用于存放密码*/
    char d;
    int i;
    int j = 100;                 /*设计标记j*/
    long int k;
    printf("请输入用户名:");
    scanf("%s", a);
    for (i = 0; i < 10; i++)        /*查找要登陆的用户是否存在,如存在则赋值
给j*/
    {
        if (strcmp(a, root->son[i]->name) == 0)
        {
            j = i;
        }
    }
    if (j == 100)
    {
        printf("该用户不存在!\n\n");    /*若j没改变即用户不存在*/
        d = getch();
        return 0;
    }
    printf("请输入密码:");                            /*检验密码*/
    scanf("%s", b);
    if (strcmp(b, root->son[j] -
    > password) == 0)
    {
        p = root->son[j];

        lj = 2;
        strcpy(lujing[lj], a);           /*登陆滚动条个性化设置*/
        system("clr");
        Gotoxy(1, 25);

        printf("=============================================================
            =================="); 
            Gotoxy(1, 25);
        for (i = 0; i < 79; i++)
        {

            for (k = 0; k < 2000000; k++) {}
            printf(">");
        }
        system("cls");
        printf("\n");
        strcpy(user, a);  /*记录当前登陆的用户*/
        return 1;
    }
    printf("密码有误!\n\n");
    d = getch();
    return 0;
}
int NEWUSER()   /*新用户创建函数,创建成功则返回1,失败返回0.*/
{
    struct tm* t;
    time_t curtime;
    curtime = time(NULL);
    t = gmtime(&curtime);
    char a[7]      char d;
    int i;
    long int j;
    if (root->son_nu >= 10)
    {
        printf("用户已达到最大数目\n\n");    /*判断系统是否达到最大用
户数目*/          return 0;
    }
    else
    {
        p = getpch(MULU);
        printf("请输入用户名(最长15位):");
        scanf("%s", p->name);
        for (i = 0; i < 10; i++)
        {
            if (root->son[i] != 0)
            {
                if (strcmp(p->name, root->son[i]->name) == 0)
                {
                    printf("该用户已存在!\n");
                    d = getch();
                    return 0;
                }
            }
        }
        printf("请输入位密码( 最长6位):");
        scanf("%s", p->password);
        /*判断两次用户密码是否一致*/          printf("再次输入密
            码:"); 
            scanf("%s", a);
        if (strcmp(a, p->password) != 0)

        {
            printf("两次密码不同,创建新用户失败!");
            d = getch();
            return 0;
        };
        strcpy(p->usr, p->name);
        p->son_nu = 0;
        p->wj_nu = 0;
        p->parent = root;
        for (i = 0; i < 10; i++)
        {
            p->son[i] = 0;
            p->wj[i] = 0;
        }            /*保存最后修改时间*/         // gettime(&t); 
        p->time[0] = t->tm_hour;
        p->time[1] = t->tm_min;
        p->time[2] = t->tm_sec;
        strcpy(lujing[lj], p->name);
        lj += 1;            /*登陆滚动条个性化设置*/
        system("clr");         Gotoxy(1, 25);

        printf("=============================================================
            =================="); 
            Gotoxy(1, 25);
        for (i = 0; i < 79; i++)
        {
            for (j = 0; j < 3000000; j++) {}             printf(">");
        }

        system("cls");
        printf("\n");
        strcpy(user, p->name);  /*记录当前登陆的用户*/
        for (i = 0; i < 10; i++)
        {
            if (root->son[i] == 0)
            {

                root->son[i] = p;

                root->son_nu += 1;
                return 1;
                system("cls");
                printf("\n");
                strcpy(user, p->name);  /*记录当前登陆的用户*/
                for (i = 0; i < 10; i++)
                {
                    if (root->son[i] == 0)
                    {
                        root->son[i] = p;
                        root->son_nu += 1;
                        return 1;
                    }
                }
            }
        }
        /********************************************************************
        **********/  void PWD()                            /*显示当前目录路径
        函数*/
        {
            int i;
            for (i = 0; i < lj; i++)
            {
                printf("%s/", lujing[i]);
            }
            printf("\n");
        }
        /********************************************************************
        **********/  void LS()    /*目录列表函数*/

        {
            int i, j;
            printf("名称           用户           类型    修改日期
                \
                n"); 

                printf("----------------------------------------------------------\n"
                );
            for (i = 0; i < 10; i++)                /*列目录属性*/
            {
                if (p->son[i] != 0)
                {
                    printf("%-15s%-15s目录    
                        ",p->son[i]->name,p->son[i]->usr); 

                        printf("%d:%d:%d\n", p->son[i]->time[0], p->son[i] -
            > time[1], p->son[i]->
                            time[2]);
                }
            }
            for (i = 0; i < 10; i++)                /*列文件属性*/
            {
                if (p->wj[i] != 0)
                {
                    printf("%-15s%-15s文件    
                        ",p->wj[i]->name,p->wj[i]->usr); 

                        printf("%d:%d:%d\n", (p->wj[i])->time[0], (p->wj[i])->time[1], (p->wj[i]
                            )->time[2]);
                }
            }
            printf("\n");
        }
        MKDIR()  /*新键目录函数*/
        {
            struct tm* t;
            time_t curtime;
            curtime = time(NULL);
            t = gmtime(&curtime);
            MULU* pp;
            int i;
            pp = getpch(MULU);
            scanf("%s", pp->name);             if (strcmp(p->name, "root") == 0)
            {

                printf("不能在该根目录下创建\n\n");    /*如果当前目录
                为根目录则不准建立*/         return;
            }
            if (p->son_nu >= 10)
            {
                printf("创建目录已达到最大数目\n\n");
                return
            }
            for (i = 0; i < 10; i++)
            {
                if (p->son[i] != 0)
                {
                    if (strcmp(p->son[i]->name, pp->name) == 0)
                    {
                        printf("该目录已存在:
                            \n\n"); 
                            return;
                    };   /*判断该目录是否存在*/
                }
            }
            strcpy(pp->usr, p->usr);
            pp->son_nu = 0;
            pp->wj_nu = 0;
            pp->parent = p;
            for (i = 0; i < 10; i++)
            {
                pp->son[i] = 0;
                pp->wj[i] = 0;
            }


            /*保存最后修改时间*/     //gettime(&t);       
            pp->time[0] = t->tm_hour;     pp->time[1] = t->tm_min;
            pp->time[2] = t->tm_sec;       printf("目录于%d:%d:%d创建成 
                功!\n\n",pp->time[0],pp->time[1],pp->time[2]);          for(i=0; i<10; 
                i++)
            {
                if (p->son[i] == 0)
                {
                    p->son[i] = pp;
                    p->son_nu += 1;
                    return;
                }
            }
        }
        /********************************************************************
        **********/  RMDIR()         /*删除目录函数*/
        {
            char a[15];
            MULU* pp;
            int i, j = 100;
            scanf("%s", a);
            for (i = 0; i < 10; i++)
            {
                if (p->son[i] != 0)
                {
                    if (strcmp(p->son[i]->name, a) == 0)
                    {
                        pp = p->son[i];
                        j = i;
                    }
                }
            }
            if (pp->son_nu != 0 || pp->wj_nu != 0)
            {
                printf("操作失败,目录不存在或非空!\n\n");
                return;      /*如果目录非空或不存在操作失败*/
            }
            if (j != 100)p->son[j] = 0;
            p->son_nu -= 1;
            free(pp);
            printf("操作成功!\n\n");
        }
        /********************************************************************
        **********/  CD()     /*改变当前工作目录*/
        {
            char a[15];
            int i;
            scanf("%s", a);
            if (strcmp(a, ".") == 0)
            {
                if (strcmp(p->name, "root") == 0)return;           /*最高
可以切换到根目录,如果在根目录下做cd .操作将失效*/
                p = p->parent;
                strcpy(lujing[lj - 1], 0);
                lj -= 1;
                return;
            }
            for (i = 0; i < 10; i++)                                /*切换
到与当前用户不同的用户目录时将失败*/

            {
                if (strcmp(p->son[i], a) == 0)
                {
                    if (strcmp(user, p->son[i]->usr) != 0)
                    {
                        printf("用户%s的文件查看被禁止,请以该用户登
                            陆!\n
                            \n",a); 
                            return;
                    }
                    p = p->son[i];
                    strcpy(lujing[lj], p->name);
                    lj += 1;
                    return;
                }
            }
            printf("目标目录不存在!\n\n");
            return;