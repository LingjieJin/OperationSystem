#include <stdio.h>
#include <stdlib.h>

#define getpch(type) (type*)malloc(sizeof(type))

#define NOTHING 0

void check();

int signal = 0;

typedef struct pcb
{
    /* data */
    // 进程名字
    char name[10];
    // 进程状态  
    char state;
    // 进程需要运行的时间
    int ntime;
    // 进程已经运行的时间
    int rtime;
    int oncerun;
    struct pcb *link;
}PCB;

// 就绪队列，进程插入位置的变量
PCB *ready = NOTHING;
// 当前尾指针
PCB *pfend = NOTHING;
// 新建进程指针
PCB *p = NOTHING;
PCB *stop = NOTHING, *stopend = NOTHING;

// 使用户仅能输入证书
int geti()
{
    char ch;
    int i=0;
    fflush(stdin);
    ch = getchar();

    while (ch=='\n')
    {
        // 输入不能为空
        fflush(stdin);
        ch = getchar();
    }

    while (ch != '\n')
    {
        if(ch>'9' || ch < '0')
        {
            printf("\t输入有误!输入只能是正整数,请重新输入。。。\n");
            fflush(stdin);

            i=0;
            ch=getchar();
        }
        else
        {
            i = i*10 + (ch - '0');
            ch = getchar();
        }
    }

    return i;
}

void SJF()
{
    if(!ready)
    {

    }
    else
    {
        PCB *tp = ready, *tempp;
        if(ready->oncerun == 1)
        {
            tp = tp->link;
        }

        while (tp != NOTHING && p->ntime >= tp->ntime)
        {
            tempp = tp;
            tp = tp->link;
        }

        if(tp == ready)
        {
            if(ready->oncerun == 0)
            {

            }
            else
            {

            }
        }
        else if(tp == NOTHING)
        {

        }
        else
        {

        }
    }
}

// 插入进程
void insert()
{
    if(!ready)
    {
        ready = p;
        pfend = p;
    }
    else
    {
        // 在尾部插入
        p->link = pfend->link;
        pfend->link = p;
        pfend = p;
    }
}

// 建立进程控制函数
void input()
{
    int i, num;
    printf("\n请输入进程的个数\n");
    num = geti();

    for ( i = 0; i < num; i++)
    {
        printf("\n进程号NO.%d\n", i+1);
        p=getpch(PCB);

        printf("\n输入进程名:");
        scanf("%s", p->name);

        printf("\n输入进程运行时间:");
        p->ntime = geti();

        printf("\n");
        p->rtime = 0;
        p->state = 'W';
        p->oncerun = 0;
        p->link = NOTHING;
        insert();
    }
}

// 建立进程显示函数
void display(PCB *pr)
{
    printf("\nname\t state\t ntime\t rtime\t ltime\t \n");
    printf("|%s\t", pr->name);
    printf(" |%c\t", pr->state);
    printf(" |%d\t", pr->ntime);
    printf(" |%d\t", pr->rtime);
    printf("\n");
}

// 进程查看函数
void check()
{
    PCB *pr;
    if(ready != NOTHING)
    {
        printf("\n******当前正在运行的进程是:%s", ready->name);
        display(ready);

        pr = ready->link;
        printf("\n******当前就绪队列状态是:\n");
        while (pr!=NOTHING)
        {
            display(pr);
            pr = pr->link;
        }
    }
    printf("\n******当前阻塞队列状态是:\n");
    pr = stop;
    while (pr != NOTHING)
    {
        display(pr);
        pr = pr->link;
    }
}


// 进程摧毁函数
void destroy()
{
    printf("\n进程{%s}已完成。\n", ready->name);
    p = ready;
    ready = ready->link;
    free(p);
}


// 建立进程就绪函数
void running()
{
    ready->oncerun = 1;
    (ready->rtime)++;
    check();

    if(ready->rtime == ready->ntime)
    {
        destroy();
        return;
    }
}

void block()
{
    if(!stop)
    {
        ready->state = 'B';
        stop = ready;
        stopend = ready;
    }
    else
    {
        ready->state = 'B';
        stopend->link = ready;
        stopend = ready;
    }
    ready = ready->link;
    stopend->link = NOTHING;
}

void wake()
{
    if(stop == NOTHING)
    {
        pfend->link = stop;
        pfend = stop;
    }
    else
    {
        ready = stop;
        pfend = stop;
    }
    stop = stop->link;
    pfend->link = NOTHING;
}

int main()
{
    char ch;
    input();

    while (ready != NOTHING || stop != NOTHING)
    {
        if(ready != NOTHING)
        {
            printf("\nThe execute name:%s\n", ready->name);
            ready->state = 'R';
            running();
        }
        else
        {
            check();
        }

        printf("\n按i键添加新进程...s键阻塞进程...w键唤醒进程\n按其他键继续运行...");
        fflush(stdin);
        ch = getchar();

        if(ch == 'i' || ch == 'I')
        {
            input();
        }
        else if (ch == 's' || ch == 'S')
        {
            block();
        }
        else if(ch == 'w' || ch == 'W')
        {
            wake();
        }
    }

    printf("\n\n进程已经完成\n");
    getchar();
    
    return 0;
}

