
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdio>
#include<string>
#include "PCBinit.h"
#define INF 0x7fffffff
using namespace std;

void printPCB()  //显示单个PCB的运行状态
{
	cout << "\n进程\t要求运行时间\t到达时间\t等待时间\t运行结束时间\t周转时间\t响应时间" << endl;
	for (int i = 0; i<6; i++)
	{
			cout << pcb[i].name << "\t" << pcb[i].serverTime << "\t\t" <<
			pcb[i].arriveTime << "\t\t" << pcb[i].waitTime << "\t\t" <<
			pcb[i].finishTime << "\t\t" << pcb[i].turnAround << "\t\t" <<
			pcb[i].responseTime << endl;
	}
}

void resultPrint()       //显示评估结果
{
	int totaltime = 0;
	int totalroundtime = 0;
	int totalwaitime = 0;
	int totalresponsetime = 0;
	for (int i = 0; i<6; i++)
	{
		totaltime += pcb[i].runTime;
		totalroundtime += pcb[i].turnAround;
		totalwaitime += pcb[i].waitTime;
		totalresponsetime += pcb[i].responseTime;
	}
	printPCB();
	printf("CPU利用率为：%.2f%%\n", (float)totaltime / (float)nowTime * 100);
	printf("系统吞吐量为：%.2f\n", 6.0 / nowTime);
	printf("平均周转时间为：%.2f\n", (float)totalroundtime / 6);
	printf("平均等待时间为：%.2f\n", (float)totalwaitime / 6);
	printf("总响应时间为：%d\n", totalresponsetime);
}
bool name(const struct PCB &a, const struct PCB &b)//进程名比较
{
	return a.name < b.name;
}
bool srtf(const struct PCB &a, const struct PCB &b)//比较函数
{
	if (a.arriveTime != b.arriveTime)
		return a.arriveTime < b.arriveTime;
	else if (a.serverTime != b.serverTime)
		return a.serverTime < b.serverTime;
	else return a.priority < b.priority;
}
bool priority(const struct PCB &a, const struct PCB &b)
{
	if (a.arriveTime != b.arriveTime)
		return a.arriveTime < b.arriveTime;
	return a.priority < b.priority;
}
bool sjf(const struct PCB &a, const struct PCB &b)
{
	if (a.arriveTime != b.arriveTime)
		return a.arriveTime < b.arriveTime;
	else if (a.serverTime != b.serverTime)
		return a.serverTime < b.serverTime;
	else return a.priority < b.priority;
}
bool fcfs(const struct PCB &a, const struct PCB &b)   
{
	if (a.arriveTime == b.arriveTime)
		return a.priority < b.priority;
	return a.arriveTime < b.arriveTime;
}
void FCFS()
{
	initial();//初始化
	sort(pcb, pcb + 6, fcfs);
	for (int i = 1; i < 6; i++)
	{
		pcb[i - 1].next = &pcb[i];
	}
	struct PCB* head = &pcb[0];
	struct PCB* pro = head;
	while (pro)
	{
		if (pro->status)   //若进程处于就绪状态，则运行进程
		{
			if (nowTime > pro->arriveTime)
				pro->waitTime = nowTime - pro->arriveTime;
			else
			{
				nowTime = pro->arriveTime;
				pro->waitTime = 0;
			}
			pro->runTime = pro->serverTime;
			pro->responseTime = pro->waitTime + pro->serverTime;
			pro->finishTime = nowTime + pro->runTime;
			nowTime = pro->finishTime;
			pro->turnAround = pro->finishTime - pro->arriveTime;
			pro->status = false;
		}
		pro = pro->next;
	}
	sort(pcb, pcb + 6, name);//按进程名称排序
	resultPrint();           //打印进程信息
}

void SJF()
{
	initial();
	sort(pcb, pcb + 6, sjf);
	while (true)
	{
		int m = INF;
		int index = -1;
		for (int i = 0; i < 6; i++)       //寻找服务时间最短的就绪进程
		{
			if (pcb[i].status && nowTime >= pcb[i].arriveTime && pcb[i].serverTime < m)
			{
				m = pcb[i].serverTime;
				index = i;
			}
		}
		if (m == INF)                      //m=INF说明所有进程已结束或当前时间没有到达进程
		{
			int cnt = 0;
			for (int i = 0; i < 6; i++)           //判断是否所有的进程都已运行结束
			{
				if (!pcb[i].status)cnt++;
			}
			if (cnt >= 6)
				break;
			else
			{
				for (int i = 0; i < 6; i++)
				{
					if (pcb[i].status && pcb[i].arriveTime < m)
					{
						m = pcb[i].arriveTime;
						index = i;
					}
				}
				nowTime = pcb[index].arriveTime;
			}
		}
		struct PCB* pro = &pcb[index];  //选中一个进程
		pro->waitTime = nowTime - pro->arriveTime;
		pro->runTime = pro->serverTime;       //运行进程直到进程结束
		nowTime += pro->serverTime;
		pro->finishTime = nowTime;
		pro->status = false;
		pro->turnAround = pro->finishTime - pro->arriveTime;
		pro->responseTime = pro->waitTime + pro->serverTime;
	}
	sort(pcb, pcb + 6, sjf);
	resultPrint();
}

void Priority()
{
	initial();                             //初始化所有进程
	sort(pcb, pcb + 6, priority);        //按到达时间和优先级排序
	while (true)
	{
		int m = INF;
		int index = -1;
		for (int i = 0; i < 6; i++)       //寻找优先级最高的已到达就绪进程
		{
			if (pcb[i].status && nowTime >= pcb[i].arriveTime && pcb[i].priority < m)
			{
				m = pcb[i].priority;
				index = i;
			}
		}
		if (m == INF)                      //m=INF说明所有进程已结束或当前时间没有到达进程
		{
			int cnt = 0;
			for (int i = 0; i < 6; i++)           //判断是否所有的进程都已运行结束
			{
				if (!pcb[i].status)cnt++;
			}
			if (cnt >= 6)
				break;
			else
			{
				for (int i = 0; i < 6; i++)
				{
					if (pcb[i].status && pcb[i].arriveTime < m)
					{
						m = pcb[i].arriveTime;
						index = i;
					}
				}
				nowTime = pcb[index].arriveTime;
			}
		}
		struct PCB *pro = &pcb[index];
		pro->runTime++;                //进程运行一个时间片
		pro->priority++;                //优先级下降
		nowTime++;
		if (pro->runTime == pro->serverTime)   //运行时间等于服务时间，说明进程结束，进行标记并记录结束时间
		{
			pro->status = false;
			pro->finishTime = nowTime;
			pro->turnAround = pro->finishTime - pro->arriveTime;
			pro->responseTime = pro->waitTime + pro->serverTime;
		}
		for (int i = 0; i < 6; i++)      //所有未被执行的就绪进程等待时间+1
		{
			if (pcb[i].status && pcb[i].arriveTime < nowTime && pro != &pcb[i])
			{
				pcb[i].waitTime++;
			}
		}
	}
	sort(pcb, pcb + 6, name);            //按名称排序进程
	resultPrint();                       //打印进程信息
}

void SRTF()
{
	initial();//初始化进程名称、开始时间、运行时间和优先级
	sort(pcb, pcb + 6, srtf);
	for (int i = 1; i < 6; i++)
	{
		pcb[i - 1].next = &pcb[i];
	}
	struct PCB* head = &pcb[0];
	struct PCB* pro = head;
	pcb[5].next = head;
	while (true)
	{
		int m = INF;                //INF表示无穷大的数，具体为0x7fffffff
		int index = -1;
		for (int i = 0; i < 6; i++)   //循环找出剩余运行时间最短的就绪进程
		{
			if (pcb[i].status && nowTime >= pcb[i].arriveTime && pcb[i].serverTime - pcb[i].runTime < m)
			{
				m = pcb[i].serverTime - pcb[i].runTime;
				index = i;
			}
		}
		if (m == INF)                      //m=INF说明所有进程已结束或当前时间没有到达进程
		{
			int cnt = 0;
			for (int i = 0; i < 6; i++)           //判断是否所有的进程都已运行结束
			{
				if (!pcb[i].status)cnt++;
			}
			if (cnt >= 6)
				break;
			else
			{
				for (int i = 0; i < 6; i++)
				{
					if (pcb[i].status && pcb[i].arriveTime < m)
					{
						m = pcb[i].arriveTime;
						index = i;
					}
				}
				nowTime = pcb[index].arriveTime;
			}
		}
		pro = &pcb[index];          //选中进程
		pro->runTime++;            //运行一个单位时间
		nowTime++;
		if (pro->runTime == pro->serverTime)   //运行时间=服务时间，说明进程结束，记录结束时间并标记结束状态
		{
			pro->status = false;
			pro->finishTime = nowTime;
			pro->turnAround = pro->finishTime - pro->arriveTime;
			pro->responseTime = pro->waitTime + pro->serverTime;
		}
		for (int i = 0; i < 6; i++)              //其他就绪进程的等待时间+1
		{
			if (pcb[i].status && pcb[i].arriveTime < nowTime && pro != &pcb[i])
			{
				pcb[i].waitTime++;
			}
		}
	}
	sort(pcb, pcb + 6, name);                     //按进程名称进行排序
	resultPrint();                                //打印所有进程信息
}
void RoundRobin()
{
	initial();                                 //初始化进程
	sort(pcb, pcb + 6, fcfs);                //按照FCFS相同的规则排序
	for (int i = 1; i < 6; i++)              //将进程连成环状链表
	{
		pcb[i - 1].next = &pcb[i];
	}
	struct PCB* head = &pcb[0];
	pcb[5].next = head;
	struct PCB* pro = head;
	int cnt;
	while (true)
	{
		if (pro->status && pro->arriveTime <= nowTime)         //当轮询到的进程就绪时执行一个时间单位
		{
			pro->runTime++;
			nowTime++;
			if (pro->runTime == pro->serverTime)   //运行时间等于服务时间时进程结束
			{
				pro->finishTime = nowTime;
				pro->status = false;
				pro->responseTime = pro->waitTime + pro->serverTime;
				pro->turnAround = pro->finishTime - pro->arriveTime;
			}
			for (int i = 0; i < 6; i++)                //其他就绪状态的进程等待时间+1
			{
				if (pro != &pcb[i] && pcb[i].status && pcb[i].arriveTime < nowTime)
				{
					pcb[i].waitTime++;
				}
			}
			pro = pro->next;
			continue;
		}
		cnt = 0;
		for (int i = 0; i < 6; i++)           //判断是否所有的进程都已运行结束
		{
			if (!pcb[i].status)cnt++;
		}
		if (cnt >= 6)
			break;
		else
		{
			int cnt2 = 0;
			for (int i = 0; i < 6; i++)
			{
				if (pcb[i].status && pcb[i].arriveTime > nowTime)
				{
					cnt2++;
				}
			}
			if (cnt2 == 6 - cnt)
				nowTime++;
			pro = pro->next;
		}
	}
	sort(pcb, pcb + 6, name);
	resultPrint();
}
int main()
{
	cout << "1.FCFS" << endl;
	cout << "2.SJF" << endl;
	cout << "3.Priority" << endl;
	cout << "4.SRTF" << endl;
	cout << "5.Round Robin" << endl;
	cout << endl;
	int ch;
	cin >> ch;
	bool flag = true;
	while (flag)
	{
		flag = false;
		switch (ch)
		{
		case 1:
			FCFS();
			break;
		case 2:
			SJF();
			break;
		case 3:
			Priority();
			break;
		case 4:
			SRTF();
			break;
		case 5:
			RoundRobin();
			break;
		}
	}
}
