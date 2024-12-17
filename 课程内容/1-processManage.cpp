#include <stdio.h>
#include <stdlib.h>

#define getpch(type) (type *)malloc(sizeof(type))

#define NOTHING 0

// 自定义PCB块
typedef struct pcb
{
    // 进程名字
    char name[10];
    // 进程状态
    char state;
    // 进程需要运行的时间
    int ntime;
    // 进程已经运行的时间
    int rtime;
    struct pcb *link;
} PCB;

// 就绪队列，进程插入位置的变量
PCB *ready = NOTHING;
// 指向最后一个PCB指针
PCB *wait_queue_end = NOTHING;

// 阻塞进程队列
PCB *stop_queue_head = NOTHING, *stop_queue_end = NOTHING;

// 使用户仅能输入正整数
int geti()
{
    char ch;
    int i = 0;
    fflush(stdin);
    ch = getchar();

    while (ch == '\n')
    {
        // 输入不能为空
        fflush(stdin);
        ch = getchar();
    }

    while (ch != '\n')
    {
        // 判断是不是0-9的输入
        if (ch > '9' || ch < '0')
        {
            printf("\t输入有误!输入只能是正整数,请重新输入。。。\n");
            fflush(stdin);

            i = 0;
            ch = getchar();
        }
        else
        {
            i = i * 10 + (ch - '0');
            ch = getchar();
        }
    }

    return i;
}

// 插入进程
// 使用先进先出的顺序插入
void fcfs(PCB *p)
{
    // 如果ready指针是空的情况，这是第一个PCB
    if (!wait_queue_end)
    {
        wait_queue_end = p;
        wait_queue_end->link = NOTHING;
        ready = wait_queue_end;
        ready->link = wait_queue_end->link;
    }
    else
    {
        // 将p指针插入最后一个
        p->link = wait_queue_end->link;
        wait_queue_end->link = p;
        wait_queue_end = p;
    }
}

// 建立进程控制函数
void input()
{
    int i, num;
    printf("\n请输入新建进程的个数\n");
    num = geti();

    for (i = 0; i < num; i++)
    {
        printf("\n新建进程-%d\n", i + 1);
        PCB *p = getpch(PCB);

        printf("\n输入进程名:");
        scanf("%s", p->name);

        printf("\n输入进程运行时间:");
        p->ntime = geti();
        printf("\n");

        // 新建进程插入
        p->rtime = 0;
        p->state = 'W';
        p->link = NOTHING;
        fcfs(p);
    }
}

// 进程显示函数
void display(PCB *p)
{
    printf("\nname\t state\t ntime\t rtime\t \n");
    printf("|%s\t", p->name);
    printf(" |%c\t", p->state);
    printf(" |%d\t", p->ntime);
    printf(" |%d\t", p->rtime);
    printf("\n");
}

// 进程检测函数
void check()
{
    PCB *pr;
    if (ready != NOTHING)
    {
        printf("\n******当前正在运行的进程是:%s", ready->name);
        display(ready);

        pr = ready->link;
        printf("\n******当前就绪队列状态是:\n");
        while (pr != NOTHING)
        {
            display(pr);
            pr = pr->link;
        }
    }

    printf("\n******当前阻塞队列状态是:\n");
    pr = stop_queue_head;
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
    PCB *temp = ready;
    ready = ready->link;
    free(temp);
}

// 进程执行函数
void running()
{
    (ready->rtime)++;
    // 输出当前进程状态
    check();

    if (ready->rtime == ready->ntime)
    {
        destroy();
        return;
    }
}

// 阻塞
void block()
{
    // 如果当前阻塞队列为空
    if (!stop_queue_head)
    {
        // 将当前ready进程阻塞
        ready->state = 'B';
        stop_queue_end = ready;
        stop_queue_end->link = NOTHING;
        stop_queue_head = stop_queue_end;
        // 就绪指针下移
        ready = ready->link;
    }
    else
    {
        // 否则将当前进程加入阻塞队列末尾
        ready->state = 'B';
        stop_queue_end->link = ready;
        stop_queue_end = ready;
        stop_queue_end->link = NOTHING;
        // 就绪指针下移
        ready = ready->link;
    }
}

// 唤醒当前阻塞进程
void wake()
{
    // 如果当前stop为空
    if (stop_queue_head == NOTHING)
    {
        return;
    }

    // 将当前stop指针移动到ready状态
    PCB *temp_stop = stop_queue_head;
    wait_queue_end->link = stop_queue_head;
    wait_queue_end = stop_queue_head;
    wait_queue_end->state = 'W';
    wait_queue_end->link = NOTHING;

    // 更新stop指针
    stop_queue_head = temp_stop->link;
}

int main()
{
    // 初始化设置
    input();

    while (ready != NOTHING || stop_queue_head != NOTHING)
    {
        if (ready != NOTHING)
        {
            printf("\nThe execute name:%s\n", ready->name);
            ready->state = 'R';
            running();
        }
        else
        {
            check();
        }

        printf("\n按i键添加新进程,s键阻塞进程,w键唤醒进程.\n按其他键继续运行:");
        fflush(stdin);

        char ch;
        ch = getchar();

        if (ch == 'i' || ch == 'I')
        {
            input();
        }
        else if (ch == 's' || ch == 'S')
        {
            block();
        }
        else if (ch == 'w' || ch == 'W')
        {
            wake();
        }
    }

    printf("\n\n进程已经完成\n");
    getchar();

    return 0;
}
