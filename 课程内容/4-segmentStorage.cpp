#include <stdio.h>
#include <string.h>

struct duan {
	long capacity;// 段的长度
	long addr;	// 起始逻辑地址
	long realaddr; // 该段的实际起始地址
};

struct duanbiao
{
	struct duan duans[10];
	char processname[20];//进程的名字
	int isdiaoyong;	// 是否被调用
	int num;	// 段的数目
	long total;	// 进程的总占用量
};

long neicun = 0;
int duanbiaonum = 0;
long zhanyong = 0;
long baseaddr = 0;
struct duanbiao duanbiaos[10];

void show1(int i);
void show();

void diaodu()
{
	printf("要调度的进程是: P");

	int n;
	scanf("%d", &n);

	if (n > duanbiaonum)
	{
		printf("段表不存在\n");
	}
	else if (duanbiaos[n - 1].isdiaoyong == 1)
	{
		printf("操作错误，该进程已经被调入内存\n");
	}
	else if (duanbiaos[n - 1].total > neicun - zhanyong)
	{
		printf("内存空间不足，调度不成功\n");
	}
	else
	{
		printf("下面对进程%s进行地址转化:\n", duanbiaos[n - 1].processname);
		for (int j = 0; j < duanbiaos[n-1].num; j++)
		{
			printf("正在进行第%d段的地址转换，请稍后...\n");
			duanbiaos[n - 1].duans[j].realaddr = duanbiaos[n - 1].duans[j].addr + zhanyong;
			printf("第%d段的地址转换成功\n", j + 1);
		}
		// 待补全
		duanbiaos[n - 1].isdiaoyong = 1;
		printf("调度后的结果是:\n");
		show1(n - 1);
	}
}

void zhuanhuan()
{
	int n, i, j;
	printf("请输入进程:P");
	scanf("%d", &n);

	if (n > duanbiaonum)
	{
		printf("进程不存在或没被调度\n");
	}
	else if (duanbiaos[n - 1].isdiaoyong == 1)
	{
		printf("请输入段号:\n");
		scanf("%d", &i);

		printf("请输入偏移地址:\n");
		scanf("%d", &j);

		if (i > duanbiaos[n - 1].num)
		{
			printf("段号超出范围\n");
		}
		else if (j > duanbiaos[n - 1].duans[i - 1].capacity)
		{
			printf("段内偏移地址超出范围\n");
		}
		else
		{
			printf("转换后的地址为%d\n", duanbiaos[n - 1].duans[i - 1].realaddr);
		}
	}
	else
	{
		printf("该进程没有调入内存\n");
	}
}


void apply()
{
	printf("请输入进程的名字:");
	scanf("%s", duanbiaos[duanbiaonum].processname);

	printf("请输入该进程的段数:\n");
	scanf("%d", &duanbiaos[duanbiaonum].num);

	if (duanbiaos[duanbiaonum].num > 10)
	{
		printf("段数太多，申请失败\n");
		return;
	}

	int paddr = 0;
	for (int j = 0; j < duanbiaos[duanbiaonum].num; j++)
	{
		printf("进程第%d段的大小是:", j + 1);
		scanf("%ld", &duanbiaos[duanbiaonum].duans[j].capacity);
		// 待补全
	}

	duanbiaos[duanbiaonum].isdiaoyong = 0;
	duanbiaos[duanbiaonum].total = paddr;
	duanbiaonum++;
}

void show1(int i)
{
	printf("进程P%d:\n", i + 1);
	printf("名字:%s\n", duanbiaos[i].processname);
	printf("该进程所占用的存储空间:%ld\n", duanbiaos[i].total);

	if (duanbiaos[i].isdiaoyong == 0)
	{
		printf("进程状态: 未调用\n");
	}
	else
	{
		printf("进程状态: 已调用\n");
	}

	printf("________________________________________\n");
	printf("段号	起始地址	内存起始地址	大小\n");
	for (int j = 0; j < duanbiaos[i].num; j++)
	{
		printf("%d%llld", j + 1, duanbiaos[i].duans[j].addr);

		if (duanbiaos[i].isdiaoyong == 0)
		{
			printf("        ");
		}
		else
		{
			printf("%llld", duanbiaos[i].duans[j].capacity);
		}
	}
	printf("________________________________________\n");
}


void show()
{
	for (int i = 0; i < duanbiaonum; i++)
	{
		show1(i);
	}
}

int main()
{
	char c;
	printf("请输入内存的大小:");
	scanf("%ld", &neicun);
	printf("************************************************\n");
	printf("1：申请内存a\t2:显示进程s\t3:调度进程d\t4:地址转换z\t5:退出q\n");
	printf("************************************************\n");

	while (1)
	{
		printf("请选择服务种类:");
		scanf("%c", &c);

		if (c == 'e')
		{
			printf("服务完毕\n");
			break;
		}
		else if (c == 'a')
		{
			apply();
		}
		else if (c == 's')
		{
			show();
		}
		else if (c == 'd')
		{
			diaodu();
		}
		else if (c == 'z')
		{
			zhuanhuan();
		}
		else
		{
			printf("error！请重新输入！\n");
		}
	}

	return 0;
}

