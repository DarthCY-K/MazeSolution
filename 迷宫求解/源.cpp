#include <stdio.h> 
#include <stdlib.h>
#include <conio.h> 
#include <string.h> 
#include <windows.h> 
#include <time.h> 
#define getpch(type) (type*)malloc(sizeof(type)) 
struct mulu                     /*����Ŀ¼�ṹ��*/
{
    char name[15];              /*���Ŀ¼��*/

    char password[6];           /*����û�Ŀ¼ʱ�������û�����*/
    char usr[15];               /*Ŀ¼�����û�*/
    int time[3];                /*����ʱ��*/
    int son_nu;                 /*��Ŀ¼��*/
    int wj_nu;                  /*Ŀ¼���ļ���*/
    struct mulu* parent;        /*ָ��Ŀ¼*/
    struct mulu* son[10];       /*�����Դ���ʮ����Ŀ¼*/
    struct wenjian* wj[10];     /*�����Դ��ʮ���ļ�*/

}*root, * p;                  /*pָ������ָ��ǰĿ¼*/
struct wenjian          /*�����ļ��ṹ��*/
{

    char name[15];              /*����ļ���*/
    char usr[15];               /*�ļ������û�*/
    int time[3];                /*�ļ�����޸�ʱ��*/
    struct mulu* parent;        /*ָ���ļ����ڵ�Ŀ¼*/
}*q;
typedef struct mulu MULU;
typedef struct wenjian WJ;
char lujing[20][15];   /*������¼��·��*/
int lj = 0;              /*��¼��Ŀ¼����ǰĿ¼����,�����ӡĿ¼*/
char user[15];         /*��¼��ǰʹ��ϵͳ���û�,�����ж�������ļ�Ȩ
��*/
char cmd[28][20] =         /*��ϵͳ��ָ�*/
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
void ROOT()         /*��ʼ����Ŀ¼root*/
{

    int i;
    root = getpch(MULU);
    p = root;
    strcpy(root->name, "root");    /*Ŀ¼��Ϊroot*/
    strcpy(root->usr, root->name); /*Ŀ¼����root*/
    root->son_nu = 0;               /*�û�����Ϊ0*/
    root->wj_nu = 0;                /*�ļ�����Ϊ0*/
    root->parent = 0;               /*��Ŀ¼������һ����*/
    for (i = 0; i < 10; i++)
    {

        root->son[i] = 0;
        root->wj[i] = 0;
    }
    strcpy(lujing[0], "root");     /*����·����Ϣ,
����ӡ·��ʹ��*/
    lj += 1;
}
int LOGIN()   /*��½����,�����û������û��������,�ڵ�½�����гɹ���
����1,ʧ�ܷ���0*/
{
    char a[15];                /*���ڴ���û���*/
    char b[6];                 /*���ڴ������*/
    char d;
    int i;
    int j = 100;                 /*��Ʊ��j*/
    long int k;
    printf("�������û���:");
    scanf("%s", a);
    for (i = 0; i < 10; i++)        /*����Ҫ��½���û��Ƿ����,�������ֵ
��j*/
    {
        if (strcmp(a, root->son[i]->name) == 0)
        {
            j = i;
        }
    }
    if (j == 100)
    {
        printf("���û�������!\n\n");    /*��jû�ı伴�û�������*/
        d = getch();
        return 0;
    }
    printf("����������:");                            /*��������*/
    scanf("%s", b);
    if (strcmp(b, root->son[j] -
    > password) == 0)
    {
        p = root->son[j];

        lj = 2;
        strcpy(lujing[lj], a);           /*��½���������Ի�����*/
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
        strcpy(user, a);  /*��¼��ǰ��½���û�*/
        return 1;
    }
    printf("��������!\n\n");
    d = getch();
    return 0;
}
int NEWUSER()   /*���û���������,�����ɹ��򷵻�1,ʧ�ܷ���0.*/
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
        printf("�û��Ѵﵽ�����Ŀ\n\n");    /*�ж�ϵͳ�Ƿ�ﵽ�����
����Ŀ*/          return 0;
    }
    else
    {
        p = getpch(MULU);
        printf("�������û���(�15λ):");
        scanf("%s", p->name);
        for (i = 0; i < 10; i++)
        {
            if (root->son[i] != 0)
            {
                if (strcmp(p->name, root->son[i]->name) == 0)
                {
                    printf("���û��Ѵ���!\n");
                    d = getch();
                    return 0;
                }
            }
        }
        printf("������λ����( �6λ):");
        scanf("%s", p->password);
        /*�ж������û������Ƿ�һ��*/          printf("�ٴ�������
            ��:"); 
            scanf("%s", a);
        if (strcmp(a, p->password) != 0)

        {
            printf("�������벻ͬ,�������û�ʧ��!");
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
        }            /*��������޸�ʱ��*/         // gettime(&t); 
        p->time[0] = t->tm_hour;
        p->time[1] = t->tm_min;
        p->time[2] = t->tm_sec;
        strcpy(lujing[lj], p->name);
        lj += 1;            /*��½���������Ի�����*/
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
        strcpy(user, p->name);  /*��¼��ǰ��½���û�*/
        for (i = 0; i < 10; i++)
        {
            if (root->son[i] == 0)
            {

                root->son[i] = p;

                root->son_nu += 1;
                return 1;
                system("cls");
                printf("\n");
                strcpy(user, p->name);  /*��¼��ǰ��½���û�*/
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
        **********/  void PWD()                            /*��ʾ��ǰĿ¼·��
        ����*/
        {
            int i;
            for (i = 0; i < lj; i++)
            {
                printf("%s/", lujing[i]);
            }
            printf("\n");
        }
        /********************************************************************
        **********/  void LS()    /*Ŀ¼�б���*/

        {
            int i, j;
            printf("����           �û�           ����    �޸�����
                \
                n"); 

                printf("----------------------------------------------------------\n"
                );
            for (i = 0; i < 10; i++)                /*��Ŀ¼����*/
            {
                if (p->son[i] != 0)
                {
                    printf("%-15s%-15sĿ¼    
                        ",p->son[i]->name,p->son[i]->usr); 

                        printf("%d:%d:%d\n", p->son[i]->time[0], p->son[i] -
            > time[1], p->son[i]->
                            time[2]);
                }
            }
            for (i = 0; i < 10; i++)                /*���ļ�����*/
            {
                if (p->wj[i] != 0)
                {
                    printf("%-15s%-15s�ļ�    
                        ",p->wj[i]->name,p->wj[i]->usr); 

                        printf("%d:%d:%d\n", (p->wj[i])->time[0], (p->wj[i])->time[1], (p->wj[i]
                            )->time[2]);
                }
            }
            printf("\n");
        }
        MKDIR()  /*�¼�Ŀ¼����*/
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

                printf("�����ڸø�Ŀ¼�´���\n\n");    /*�����ǰĿ¼
                Ϊ��Ŀ¼��׼����*/         return;
            }
            if (p->son_nu >= 10)
            {
                printf("����Ŀ¼�Ѵﵽ�����Ŀ\n\n");
                return
            }
            for (i = 0; i < 10; i++)
            {
                if (p->son[i] != 0)
                {
                    if (strcmp(p->son[i]->name, pp->name) == 0)
                    {
                        printf("��Ŀ¼�Ѵ���:
                            \n\n"); 
                            return;
                    };   /*�жϸ�Ŀ¼�Ƿ����*/
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


            /*��������޸�ʱ��*/     //gettime(&t);       
            pp->time[0] = t->tm_hour;     pp->time[1] = t->tm_min;
            pp->time[2] = t->tm_sec;       printf("Ŀ¼��%d:%d:%d������ 
                ��!\n\n",pp->time[0],pp->time[1],pp->time[2]);          for(i=0; i<10; 
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
        **********/  RMDIR()         /*ɾ��Ŀ¼����*/
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
                printf("����ʧ��,Ŀ¼�����ڻ�ǿ�!\n\n");
                return;      /*���Ŀ¼�ǿջ򲻴��ڲ���ʧ��*/
            }
            if (j != 100)p->son[j] = 0;
            p->son_nu -= 1;
            free(pp);
            printf("�����ɹ�!\n\n");
        }
        /********************************************************************
        **********/  CD()     /*�ı䵱ǰ����Ŀ¼*/
        {
            char a[15];
            int i;
            scanf("%s", a);
            if (strcmp(a, ".") == 0)
            {
                if (strcmp(p->name, "root") == 0)return;           /*���
�����л�����Ŀ¼,����ڸ�Ŀ¼����cd .������ʧЧ*/
                p = p->parent;
                strcpy(lujing[lj - 1], 0);
                lj -= 1;
                return;
            }
            for (i = 0; i < 10; i++)                                /*�л�
���뵱ǰ�û���ͬ���û�Ŀ¼ʱ��ʧ��*/

            {
                if (strcmp(p->son[i], a) == 0)
                {
                    if (strcmp(user, p->son[i]->usr) != 0)
                    {
                        printf("�û�%s���ļ��鿴����ֹ,���Ը��û���
                            ½!\n
                            \n",a); 
                            return;
                    }
                    p = p->son[i];
                    strcpy(lujing[lj], p->name);
                    lj += 1;
                    return;
                }
            }
            printf("Ŀ��Ŀ¼������!\n\n");
            return;