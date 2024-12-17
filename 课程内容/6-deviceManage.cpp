#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pcb
{
	char name[10];
	char devname[10];
	struct pcb* next;
}PCB; // 进程

// 执行队列
PCB* run;

typedef struct chct
{
	char identify[10];  // 表示
	int state;  // 设备状态
	PCB* blocking;  // 阻塞队列指针
}CHCT;  // 通道控制表

CHCT* CH1, * CH2; // 设置两个通道 ch1, ch2

typedef struct coct
{
	char identify[10]; // 标识
	int state;  // 涩北状态
	CHCT* chct;
	PCB* blocking;
	struct coct* next;
}COCT; // 控制器控制表

COCT* cohead;

typedef struct dct
{
	char identify[10];
	char type;
	int state;
	int times;
	PCB* blocking;
	COCT* coct;
}DCT; // 设备控制表

typedef struct sdt
{
	char identify[10];
	char type;
	DCT* dct;
	struct sdt* next;
}SDT; // 系统设备表

SDT* head;
SDT* checkdel;

void Init()
{
	// 进程控制块
	PCB* ch1block, * ch2block, * co1block, * co2block, * co3block;
	PCB* d1block, * d2block, * d3block, * d4block;

	COCT* CO1, * CO2, * CO3;
	DCT* d1, * d2, * d3, * d4;
	SDT* s1, * s2, * s3, * s4;

	//
	run = (PCB*)malloc(sizeof(PCB));
	run->next = NULL;

	CH1 = (CHCT*)malloc(sizeof(CHCT));
	CH2 = (CHCT*)malloc(sizeof(CHCT));
	strcpy(CH1->identify, "ch1");
	strcpy(CH2->identify, "ch2");
	CH1->state = 0;
	CH2->state = 0;

	ch1block = (PCB*)malloc(sizeof(PCB));
	ch1block->next = NULL;
	ch2block = (PCB*)malloc(sizeof(PCB));
	ch2block->next = NULL;

	CH1->blocking = ch1block;
	CH2->blocking = ch2block;

	cohead = (COCT*)malloc(sizeof(COCT));
	cohead->next = NULL;
	CO1 = (COCT*)malloc(sizeof(COCT));
	cohead->next = CO1;
	CO1->next = NULL;

	CO2 = (COCT*)malloc(sizeof(COCT));
	CO1->next = CO2;
	CO2->next = NULL;

	CO3 = (COCT*)malloc(sizeof(COCT));
	CO2->next = CO3;
	CO3->next = NULL;

	CO1->state = 0;
	CO2->state = 0;
	CO3->state = 0;

	co1block = (PCB*)malloc(sizeof(PCB));
	co1block->next = NULL;
	co2block = (PCB*)malloc(sizeof(PCB));
	co2block->next = NULL;
	co3block = (PCB*)malloc(sizeof(PCB));
	co3block->next = NULL;
	strcpy(CO1->identify, "co1");
	strcpy(CO2->identify, "co2");
	strcpy(CO3->identify, "co3");

	CO1->chct = CH1;
	CO2->chct = CH1;
	CO3->chct = CH2;
	CO1->blocking = co1block;
	CO2->blocking = co2block;
	CO3->blocking = co3block;

	//
	d1block = (PCB*)malloc(sizeof(PCB));
	d2block = (PCB*)malloc(sizeof(PCB));
	d3block = (PCB*)malloc(sizeof(PCB));
	d4block = (PCB*)malloc(sizeof(PCB));
	d1block->next = NULL;
	d2block->next = NULL;
	d3block->next = NULL;
	d4block->next = NULL;

	d1 = (DCT*)malloc(sizeof(DCT));
	strcpy(d1->identify, "P"); // P表示打印机设备

	d2 = (DCT*)malloc(sizeof(DCT));
	strcpy(d2->identify, "T"); // P表示显示器设备

	d3 = (DCT*)malloc(sizeof(DCT));
	strcpy(d3->identify, "K"); // P表示键盘设备

	d4 = (DCT*)malloc(sizeof(DCT));
	strcpy(d4->identify, "M"); // P表示鼠标设备

	d1->coct = CO1;
	d2->coct = CO2;
	d3->coct = CO3;
	d4->coct = CO3;

	d1->state = 0;
	d2->state = 0;
	d3->state = 0;
	d4->state = 0;

	d1->type = 'o';
	d2->type = 'o';
	d3->type = 'i';
	d4->type = 'i';

	d1->blocking = d1block;
	d2->blocking = d2block;
	d3->blocking = d3block;
	d4->blocking = d4block;

	//
	head = (SDT*)malloc(sizeof(SDT));
	head->next = NULL;
	s1 = (SDT*)malloc(sizeof(SDT));
	s2 = (SDT*)malloc(sizeof(SDT));
	s3 = (SDT*)malloc(sizeof(SDT));
	s4 = (SDT*)malloc(sizeof(SDT));
	head->next = s1;
	s1->next = s2;
	s2->next = s3;
	s3->next = s4;
	s4->next = NULL;
	s1->dct = d1;
	s2->dct = d2;
	s3->dct = d3;
	s4->dct = d4;
	strcpy(s1->identify, "P");
	strcpy(s2->identify, "T");
	strcpy(s3->identify, "K");
	strcpy(s4->identify, "M");
	s1->type = 'o';
	s2->type = 'o';
	s3->type = 'i';
	s4->type = 'i';

	//
	SDT* temp = head->next;
}


// 添加设备时候，添加新控制器，把控制器加到最后
void addControl(COCT* temp)
{
	// 遍历找到最后一个控制器
	COCT* cotemp = cohead;
	while (cotemp->next != NULL)
	{
		cotemp = cotemp->next;
	}
	cotemp->next = temp;
	temp->next = NULL;
}

// 查看所有的控制器
void showAllCOntrol()
{
	COCT* temp = cohead->next;
	while (temp != NULL)
	{
		printf("%s ", temp->identify);
		temp = temp->next;
	}
	printf("\n");
}

// 查找要连接的控制器
COCT* findControl(char a[])
{
	COCT* temp = cohead->next;
	while (temp != NULL)
	{
		if (!strcmp(temp->identify, a)) {
			return temp;
		}
		temp = temp->next;
	}

	// 最后一个必定是NULL
	return temp;
}

// 删除设备 判断是不是同时删除控制器，等于1删除，0不删除
int sf_deleteControl(char a[], char b[])
{
	SDT* temp;
	temp = head->next;
	while (temp != NULL)
	{
		if (strcmp(temp->identify, a) && (!strcmp(temp->dct->coct->identify, b)))
		{
			return 0;
		}
		temp = temp->next;
	}

	return 1;
}

// 删除设备的同时删除控制器
void deleteControl(COCT* te)
{
	COCT* temp = cohead;
	while (temp->next != te)
	{
		temp = temp->next;
	}
	// 确保一定能找到设备
	temp->next = te->next;
	free(te);
}

// 添加设备 查找设备是不是已经存在
int sf_exist(char a[])
{
	SDT* temp;
	if (head->next == NULL)
	{
		return 0;
	}
	else
	{
		temp = head->next;
		while (temp != NULL)
		{
			if (!strcmp(a, temp->identify)) {
				checkdel = temp;

				return 1;
			}
			temp = temp->next;
		}
		return 0;
	}
}


// 申请设备时候，如果忙，将设备挂到等待列表
void addWaitPCB(PCB* p1, PCB* p2)
{
	PCB* temp = p1;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}temp->next = p2;
	p2->next = NULL;
}


// 回收设备的时候，对PCB操作
void deletePCB(char a[])
{
	PCB* temp2 = run->next, * temp = run;
	while (temp2 != NULL)
	{
		if (!strcmp(temp2->devname, a)) {
			temp->next = temp2->next;
			free(temp2);
			break;
		}
		temp = temp2;
		temp2 = temp->next;
	}
}

// 判断等待队列是不是空
int sf_isPCBNull(PCB* temp)
{
	if (temp->next == NULL)
	{
		return 0;
	}

	return 1;
}


// 查看所有设备状态
void showMenu()
{
	PCB* ptemp = run->next;
	SDT* temp = head->next;
	DCT* dtemp;
	COCT* cotemp;
	CHCT* chtemp;

	printf("SDT		i/o		COCT		CHCT\n");
	while (temp != NULL)
	{
		dtemp = temp->dct;
		cotemp = dtemp->coct;
		chtemp = cotemp->chct;
		printf("%s[%d]\t\t%c\t\t%s[%d]\t\t%s[%d]\n", dtemp->identify, dtemp->state, dtemp->type,
			cotemp->identify, cotemp->state,
			chtemp->identify, chtemp->state);
		temp = temp->next;
	}

	while (ptemp != NULL)
	{
		printf("进程%s申请了设备%s\n", ptemp->name, ptemp->devname);
		ptemp = ptemp->next;
	}
	printf("\n");
}

// 设备独立性时候查找要查找的类型是不是存在
int sf_typeexist(char ch)
{
	SDT* temp;
	if (head->next == NULL)
	{
		return 0;
	}
	else
	{
		temp = head->next;
		while (temp != NULL)
		{
			if (temp->type == ch) {
				return 1;
			}
			temp = temp->next;

		}
	}
	return 0;
}


// 增加设备
void addDevice()
{
	printf("增加设备\n");
	SDT* stemp, * s2temp;
	COCT* cotemp;
	DCT* temp;
	char temptype;
	PCB* tempblock, * cotempblock;

	char choice;
	char eqary[10], coary[10];
	scanf("%s", eqary);
	if (sf_exist(eqary) == 1)
	{
		// 设备存在
		printf("设备已存在\n");

		return;
	}

	// 设备不存在
	tempblock = (PCB*)malloc(sizeof(PCB));
	tempblock->next = NULL;

	temp = (DCT*)malloc(sizeof(DCT));
	strcpy(temp->identify, eqary);
	temp->blocking = tempblock;
	temp->state = 0;

	printf("输入设备类型:\n");
	scanf("%s", &temptype);
	temp->type = temptype;

	stemp = (SDT*)malloc(sizeof(SDT));
	stemp->next = NULL;
	stemp->dct = temp;
	stemp->type = temptype;
	strcpy(stemp->identify, eqary);

	s2temp = head;
	while (s2temp->next != NULL)
	{
		s2temp = s2temp->next;
	}
	s2temp->next = stemp;
	stemp->next = NULL;

	printf("是否添加控制器?(y/n)\n");
	scanf("%c", &choice);
	if (choice == 'y' || choice == 'Y')
	{
		// 添加新控制器
		printf("输入控制器名称:\n");
		scanf("%s", coary);
		cotempblock = (PCB*)malloc(sizeof(PCB));
		cotempblock->next = NULL;

		cotemp = (COCT*)malloc(sizeof(COCT));
		cotemp->next = NULL;
		strcpy(cotemp->identify, coary);
		cotemp->state = 0;
		cotemp->blocking = cotempblock;

		addControl(cotemp);
		temp->coct = cotemp;
		printf("请选择连接的通道:1/2\n");

		int i;
		scanf("%d", i);
		if (i == 1)
		{
			cotemp->chct = CH1;
		}
		else
		{
			cotemp->chct = CH2;
		}
	}
	else
	{
		// 不添加控制器
		showAllCOntrol();
		printf("谁连接控制器的名称:\n");
		scanf("$s", coary);
		cotemp = findControl(coary);
		temp->coct = cotemp;
	}
	printf("设备%s添加成功！\n", eqary);

}


// 删除设备
void deleteDevice()
{
	// 删除设备的同时删除PCb
	printf("删除设备\n");
	COCT* temp;
	SDT* stemp;
	char chary[10];
	char tempary[10];

	scanf("%s", chary);
	if (sf_exist(chary) == 0)
	{
		printf("删除设备不存在\n");
	}
	else if (checkdel->dct->state == 1)
	{
		printf("设备正在使用，无法删除\n");
	}
	else
	{
		deletePCB(chary);
		strcpy(tempary, checkdel->dct->coct->identify);

		if (sf_deleteControl(chary, tempary))
		{
			// 删除控制器
			temp = checkdel->dct->coct;
			deleteControl(temp);
		}
		// 补充代码

		printf("设备%s删除成功\n", chary);
	}
}
// 申请设备
void applyDevice()
{
	printf("申请设备\n");
	PCB* ptemp;
	DCT* dtemp;
	COCT* cotemp;
	CHCT* chtemp;
	char pname[10], eqname[10];
	printf("输入申请设备的进程:");
	scanf("%s", pname);
	printf("输入申请的设备名称:");
	scanf("%s", eqname);
	if (sf_exist(eqname) == 0)
	{
		printf("设备不存在\n");
	}
	else
	{
		ptemp = (PCB*)malloc(sizeof(PCB));
		strcpy(ptemp->name, pname);
		ptemp->next = NULL;
		dtemp = checkdel->dct;

		// 此处考虑状态的改变
		if (dtemp->state == 1)
		{
			// 设备忙
			addWaitPCB(dtemp->blocking, ptemp);
			printf("进程%s被挂在设备%s的等待队列上\n", ptemp->name, dtemp->identify);

		}
		else
		{
			cotemp = dtemp->coct;
			if (cotemp->state == 1)
			{
				// 控制器忙
				addWaitPCB(cotemp->blocking, ptemp);
				printf("进程%s被挂在设备%s的等待队列上\n", ptemp->name, dtemp->identify);
			}
			else
			{
				// 控制器不忙
				chtemp = cotemp->chct;
				if (chtemp->state == 1)
				{
					// 通道忙
					// 增加代码
					printf("进程%s被挂在设备%s的等待队列上\n", ptemp->name, dtemp->identify);
				}
				else
				{
					// 通道不忙
					addWaitPCB(run, ptemp);
					dtemp->state = 1;
					cotemp->state = 1;
					chtemp->state = 1;
					strcpy(ptemp->devname, eqname);
					printf("进程%s申请设备%s成功\n", pname, eqname);
				}
			}
		}
	}
}


// 回收设备
void recycleDevice()
{
	printf("回收设备\n");
	PCB* pctemp1, * pctemp2;
	DCT* dtemp;
	COCT* cotemp;
	CHCT* chtemp;
	char eqname[10];
	scanf("%s", eqname);
	if (sf_exist(eqname) == 0)
	{
		printf("设备不存在\n");
	}
	else if (checkdel->dct->state == 0)
	{
		// 设备存在，不需要回收
		printf("设备处于空闲状态，不需要回收\n");
	}
	else
	{
		// 需要回收
		deletePCB(eqname);

		dtemp = checkdel->dct;
		cotemp = dtemp->coct;
		chtemp = cotemp->chct;
		dtemp->state = 0;
		cotemp->state = 0;
		chtemp->state = 0;

		if (sf_isPCBNull(chtemp->blocking))
		{
			// 如果通道等待队列不空
			pctemp1 = chtemp->blocking;
			pctemp2 = pctemp1->next;
			pctemp1->next = pctemp2->next;
			pctemp2->next = NULL;
			strcpy(pctemp2->devname, eqname);
			addWaitPCB(run, pctemp2);
			dtemp->state = 1;
			cotemp->state = 1;
			chtemp->state = 1;
		}
		else
		{
			if (sf_isPCBNull(cotemp->blocking))
			{
				// 如果控制器的等待队列不空
				pctemp1 = cotemp->blocking;
				pctemp2 = pctemp1->next;
				pctemp1->next = pctemp2->next;
				pctemp2->next = NULL;
				strcpy(pctemp2->devname, eqname);
				addWaitPCB(run, pctemp2);
				dtemp->state = 1;
				cotemp->state = 1;
				chtemp->state = 1;
			}
			else
			{
				if (sf_isPCBNull(dtemp->blocking))
				{
					// 如果设备的等待队列不空
					pctemp1 = cotemp->blocking;
					pctemp2 = pctemp1->next;
					pctemp1->next = pctemp2->next;
					pctemp2->next = NULL;
					strcpy(pctemp2->devname, eqname);
					addWaitPCB(run, pctemp2);
					dtemp->state = 1;
					cotemp->state = 1;
					chtemp->state = 1;
				}
			}
		}
		printf("设备%s回收成功\n", eqname);
	}
}


void Independence()
{
	printf("设备独立性--申请设备:\n");

	char type, pname[10];
	PCB* ptemp;
	DCT* dtemp;
	COCT* cotemp;
	CHCT* chtemp;
	SDT* temp, * temp2;

	scanf("%s %c", pname, &type);
	if (type == 'o' || type == 'i')
	{
		if (sf_typeexist(type) == 0)
		{
			printf("要申请的该类设备不存在\n");

		}
		else
		{
			temp = head->next;
			while (temp != NULL)
			{
				if (temp->type == type && temp->dct->state == 0)
				{
					// 当设备类型相同，并且设备空闲
					temp2 = temp;
					break;
				}
				else if (temp->type == type)
				{
					temp2 = temp;
				}
				temp = temp->next;
			}

			sf_exist(temp2->identify);
			ptemp = (PCB*)malloc(sizeof(PCB));
			strcpy(ptemp->name, pname);
			ptemp->next = NULL;
			dtemp = checkdel->dct;

			if (temp2->dct->state == 0)
			{
				// 当设备不忙的时候
				cotemp = dtemp->coct;
				if (cotemp->state == 1)
				{
					// 控制器忙
					addWaitPCB(cotemp->blocking, ptemp);
					printf("进程%s被挂在控制器%s的等待队列上\n", ptemp->name, cotemp->identify);
				}
				else
				{
					// 控制器不忙
					chtemp = cotemp->chct;
					if (chtemp->state == 1)
					{
						// 通道忙
						addWaitPCB(cotemp->blocking, ptemp);
						printf("进程%s被挂在控制器%s的等待队列上\n", ptemp->name, chtemp->identify);
					}
					else
					{
						// 通道不忙
						addWaitPCB(run, ptemp);
						dtemp->state = 1;
						cotemp->state = 1;
						chtemp->state = 1;
						strcpy(ptemp->devname, temp2->identify);
						printf("进程%s申请设备%s成功\n", pname, temp2->identify);
					}
				}
			}
			else
			{
				// 当设备忙的时候
				addWaitPCB(dtemp->blocking, ptemp);
				printf("进程%s被挂在控制器%s的等待队列上\n", ptemp->name, dtemp->identify);
			}
		}
	}
	else
	{
		printf("输入设备的类型错误\n");
	}

}


void Show()
{
	printf("A: 增加设备\n");
	printf("D: 删除设备\n");
	printf("S: 申请设备\n");
	printf("H: 回收设备\n");
	printf("I: 设备独立性\n");
	printf("Q: 推出\n");
}

int main()
{
	printf("设备管理实验\n");
	printf("\n");
	printf("相关指令:\n");
	Init();
	Show();

	char choice;
	while (1)
	{
		showMenu();
		Show();
		printf("选择指令:\n");
		scanf("%c", &choice);
		switch (choice)
		{
		case 'a':
		case 'A':
			addDevice();
			break;
		case 'd':
		case 'D':
			deleteDevice();
			break;
		case 's':
		case 'S':
			applyDevice();
			break;
		case 'h':
		case 'H':
			recycleDevice();
			break;
		case 'q':
		case 'Q':
			exit(0);
		case 'i':
		case 'I':
			Independence();
			break;
		default:
			printf("指令错误\n");
			break;
		}
	}

	return 0;
}