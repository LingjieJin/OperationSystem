#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// 空闲状态
#define Free 0	
// 已用状态
#define Busy 1	
// 完成
#define OK 1	
// 出错
#define ERROR 0
//  最大内存空间为640KB
#define MAX_LENGTH 640	

typedef int Status;
int flag;

typedef struct freearea
{
	long size;	// 分区大小
	long address;	// 分区地址
	int state;	// 状态
}ElemType;

// 线性表的双向链表存储结构
typedef struct DuLNode
{
	ElemType data;
	struct DuLNode* prior;
	struct DuLNode* next;
}DuLNode, * DuLinkList;

DuLinkList block_first;	// 头结点
DuLinkList block_last;	// 尾结点

Status alloc(int);
Status free_mem(int);
Status First_fit(int);
Status Best_fit(int);
Status Worst_fit(int);

void Show();
Status InitBlock();

Status InitBlock()
{
	block_first = (DuLinkList)malloc(sizeof(DuLNode));
	block_last = (DuLinkList)malloc(sizeof(DuLNode));

	block_first->prior = NULL;
	block_first->next = block_last;
	block_last->prior = block_first;
	block_last->next = NULL;

	block_last->data.address = 0;
	block_last->data.size = MAX_LENGTH;
	block_last->data.state = Free;

	return OK;
}


Status alloc(int ch)
{
	int request = 0;
	printf("请输入需要分配的主存大小(单位KB):");
	scanf("%d", &request);
	if (request < 0 || request == 0)
	{
		printf("分配大小不合适，请重试\n");
		return ERROR;
	}

	// 选择最佳适应算法
	if (ch == 2)
	{
		if (Best_fit(request) == OK)
		{
			printf("分配成功\n");
		}
		else
		{
			printf("内存不足，分配失败\n");
		}
		return OK;
	}
	// 选择最差适应算法
	else if (ch == 3)
	{
		if (Worst_fit(request) == OK)
		{
			printf("分配成功\n");
		}
		else
		{
			printf("内存不足，分配失败\n");
		}
		return OK;
	}
	// 默认使用首次适应算法
	else
	{
		if (First_fit(request) == OK)
		{
			printf("分配成功\n");
		}
		else
		{
			printf("内存不足，分配失败\n");
		}
		return OK;
	}

}

// 将新的节点插入到某节点后
void InsertNodeAfter(DuLNode* p, DuLNode* newNode)
{
	if (p == NULL || newNode == NULL)
	{
		return;
	}

	newNode->prior = p;
	newNode->next = p->next;

	if (p->next != NULL)
	{
		p->next->prior = newNode;
	}
	p->next = newNode;
}


// 首次适应算法
Status First_fit(int request)
{
	DuLNode* temp = (DuLNode*)malloc(sizeof(DuLNode));
	if (temp == NULL)
	{
		return ERROR;
	}

	temp->data.size = request;
	temp->data.state = Busy;

	DuLNode* p = block_first->next;
	while (p)
	{
		if (p->data.state == Free && p->data.size == request) {
			p->data.state = Busy;

			free(temp);
			return OK;
		}

		if (p->data.state == Free && p->data.size > request)
		{
			DuLNode* newfreeblock = (DuLNode*)malloc(sizeof(DuLNode));
			if (newfreeblock == NULL)
			{
				return ERROR;
			}
			newfreeblock->data.size = p->data.size - request;
			newfreeblock->data.state = Free;

			InsertNodeAfter(p, newfreeblock);

			p->data.size = request;
			p->data.state = Busy;

			free(temp);

			return OK;
		}
		p = p->next;
	}

	free(temp);

	return ERROR;

}


Status Best_fit(int request)
{
	DuLNode* p = block_first->next;
	DuLNode* best_fit = NULL;
	int main_leftover = INT_MAX;

	while (p)
	{
		if (p->data.state == Free && p->data.size >= request) {
			int leftover = p->data.size - request;
			if (leftover < main_leftover)
			{
				main_leftover = leftover;
				best_fit = p;
			}
		}
		p = p->next;
	}

	if (best_fit == NULL)
	{
		return ERROR;
	}

	if (best_fit->data.size == request)
	{
		best_fit->data.state = Busy;
	}
	else
	{
		DuLNode* newfreeblock = (DuLNode*)malloc(sizeof(DuLNode));
		if (newfreeblock == NULL)
		{
			return ERROR;
		}

		newfreeblock->data.size = main_leftover;
		newfreeblock->data.state = Free;

		newfreeblock->prior = best_fit;
		newfreeblock->next = best_fit->next;

		if (best_fit->next)
		{
			best_fit->next->prior = newfreeblock;
		}
		best_fit->next = newfreeblock;

		best_fit->data.size = request;
		best_fit->data.state = Busy;

	}

	return OK;
}

// 最差适应算法
Status Worst_fit(int request)
{
	DuLNode* p = block_first->next;
	DuLNode* q = NULL;
	int max_leftover = 0;

	while (p)
	{
		if (p->data.state == Free && p->data.size >= request) {
			if (q == NULL || p->data.size > q->data.size)
			{
				q = p;
				max_leftover = p->data.size - request;
			}
		}
		p = p->next;
	}

	if (q == NULL)
	{
		return ERROR;
	}

	if (q->data.size == request)
	{
		q->data.state = Busy;
	}
	else
	{
		DuLNode* newfreenode = (DuLNode*)malloc(sizeof(DuLNode));
		if (newfreenode == NULL)
		{
			return ERROR;
		}

		newfreenode->data.size = max_leftover;
		newfreenode->data.state = Free;

		q->data.size = request;
		q->data.state = Busy;
	}

	return OK;
}


Status free_mem(int flag)
{
	DuLNode* p = block_first;

	for (int i = 0; i <= flag; i++)
	{
		if (p != NULL)
		{
			p = p->next;
		}
		else
		{
			return ERROR;
		}
	}

	if (p->data.state == Free)
	{
		printf("该块本为空闲\n");
		return ERROR;
	}
	p->data.state = Free;

	if (p == block_last)
	{
		if (p->prior == block_first)
		{
			p->data.state = Free;
		}
		else
		{
			if (p->prior->data.state == Busy)
			{
				p->data.state == Free;
			}
			else
			{
				p->prior->data.size += p->data.size;
				p->prior->next = p->next;
				p->next->prior = p->prior;
				p = p->prior;
			}
		}
		return OK;
	}

	if (p->prior != block_first && p->prior->data.state == Free)
	{
		// 与前面的空闲块相连
		p->prior->data.size += p->data.size;
		p->prior->next = p->next;
		p->next->prior = p->prior;
		p = p->prior;
		return OK;
	}

	if (p->next != block_last && p->next->data.state == Free)
	{
		// 与后面的空闲块相连
		p->data.size += p->next->data.size;
		p->next->next->prior = p;
		p->next = p->next->next;
		return OK;
	}

	if (p->next == block_last && p->next->data.state == Free)
	{
		// 与最后的空闲块相连
		p->data.size += p->next->data.size;
		p->next = NULL;
		return OK;
	}

	printf("\n未知错误\n");
	return ERROR;
}


void Show()
{
	int flag = 0;
	printf("\n主存分配情况:\n");
	printf("+++++++++++++++++++++++++++++++++\n\n");

	DuLNode* p = block_first->next;
	printf("分区号\t起始地址\t分区大小\t状态\n\n");

	while (p)
	{
		printf("%d\t", flag++);
		printf("%ld\t\t", p->data.address);
		printf("%ld KB\t\t", p->data.size);

		if (p->data.state == Free)
		{
			printf("空闲\n\n");
		}
		else
		{
			printf("已分配\n\n");
		}
		p = p->next;
	}

	printf("+++++++++++++++++++++++++++++++++\n\n");
}


int main()
{
	int ch;
	printf("请输入所使用的内存分配算法:\n");
	printf("1:首次适应算法\n2:最佳适应算法\n3:最差适应算法\n");

	scanf("%d", &ch);
	while (ch < 1 || ch > 3)
	{
		printf("输入错误\n");
		scanf("%d", &ch);
	}

	InitBlock();
	int choice;

	while (1)
	{
		Show();
		printf("请输入你的操作:");
		printf("1分配内存\n2回收内存\n0退出\n");
		scanf("%d", &choice);

		if (choice == 1)
		{
			alloc(ch);
		}
		else if (choice == 2)
		{
			int flag;
			printf("请输入释放的分区号:");
			scanf("%d", &flag);
			free_mem(flag);
		}
		else if (choice == 0)
		{
			break;
		}
		else
		{
			printf("输入有误，请重新输入\n");
			continue;
		}
	}


	return 0;
}

