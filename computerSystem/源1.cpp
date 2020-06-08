
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdio>
#include<string>
#include "PCBinit.h"
#define INF 0x7fffffff
using namespace std;

void printPCB()  //��ʾ����PCB������״̬
{
	cout << "\n����\tҪ������ʱ��\t����ʱ��\t�ȴ�ʱ��\t���н���ʱ��\t��תʱ��\t��Ӧʱ��" << endl;
	for (int i = 0; i<6; i++)
	{
			cout << pcb[i].name << "\t" << pcb[i].serverTime << "\t\t" <<
			pcb[i].arriveTime << "\t\t" << pcb[i].waitTime << "\t\t" <<
			pcb[i].finishTime << "\t\t" << pcb[i].turnAround << "\t\t" <<
			pcb[i].responseTime << endl;
	}
}

void resultPrint()       //��ʾ�������
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
	printf("CPU������Ϊ��%.2f%%\n", (float)totaltime / (float)nowTime * 100);
	printf("ϵͳ������Ϊ��%.2f\n", 6.0 / nowTime);
	printf("ƽ����תʱ��Ϊ��%.2f\n", (float)totalroundtime / 6);
	printf("ƽ���ȴ�ʱ��Ϊ��%.2f\n", (float)totalwaitime / 6);
	printf("����Ӧʱ��Ϊ��%d\n", totalresponsetime);
}
bool name(const struct PCB &a, const struct PCB &b)//�������Ƚ�
{
	return a.name < b.name;
}
bool srtf(const struct PCB &a, const struct PCB &b)//�ȽϺ���
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
	initial();//��ʼ��
	sort(pcb, pcb + 6, fcfs);
	for (int i = 1; i < 6; i++)
	{
		pcb[i - 1].next = &pcb[i];
	}
	struct PCB* head = &pcb[0];
	struct PCB* pro = head;
	while (pro)
	{
		if (pro->status)   //�����̴��ھ���״̬�������н���
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
	sort(pcb, pcb + 6, name);//��������������
	resultPrint();           //��ӡ������Ϣ
}

void SJF()
{
	initial();
	sort(pcb, pcb + 6, sjf);
	while (true)
	{
		int m = INF;
		int index = -1;
		for (int i = 0; i < 6; i++)       //Ѱ�ҷ���ʱ����̵ľ�������
		{
			if (pcb[i].status && nowTime >= pcb[i].arriveTime && pcb[i].serverTime < m)
			{
				m = pcb[i].serverTime;
				index = i;
			}
		}
		if (m == INF)                      //m=INF˵�����н����ѽ�����ǰʱ��û�е������
		{
			int cnt = 0;
			for (int i = 0; i < 6; i++)           //�ж��Ƿ����еĽ��̶������н���
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
		struct PCB* pro = &pcb[index];  //ѡ��һ������
		pro->waitTime = nowTime - pro->arriveTime;
		pro->runTime = pro->serverTime;       //���н���ֱ�����̽���
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
	initial();                             //��ʼ�����н���
	sort(pcb, pcb + 6, priority);        //������ʱ������ȼ�����
	while (true)
	{
		int m = INF;
		int index = -1;
		for (int i = 0; i < 6; i++)       //Ѱ�����ȼ���ߵ��ѵ����������
		{
			if (pcb[i].status && nowTime >= pcb[i].arriveTime && pcb[i].priority < m)
			{
				m = pcb[i].priority;
				index = i;
			}
		}
		if (m == INF)                      //m=INF˵�����н����ѽ�����ǰʱ��û�е������
		{
			int cnt = 0;
			for (int i = 0; i < 6; i++)           //�ж��Ƿ����еĽ��̶������н���
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
		pro->runTime++;                //��������һ��ʱ��Ƭ
		pro->priority++;                //���ȼ��½�
		nowTime++;
		if (pro->runTime == pro->serverTime)   //����ʱ����ڷ���ʱ�䣬˵�����̽��������б�ǲ���¼����ʱ��
		{
			pro->status = false;
			pro->finishTime = nowTime;
			pro->turnAround = pro->finishTime - pro->arriveTime;
			pro->responseTime = pro->waitTime + pro->serverTime;
		}
		for (int i = 0; i < 6; i++)      //����δ��ִ�еľ������̵ȴ�ʱ��+1
		{
			if (pcb[i].status && pcb[i].arriveTime < nowTime && pro != &pcb[i])
			{
				pcb[i].waitTime++;
			}
		}
	}
	sort(pcb, pcb + 6, name);            //�������������
	resultPrint();                       //��ӡ������Ϣ
}

void SRTF()
{
	initial();//��ʼ���������ơ���ʼʱ�䡢����ʱ������ȼ�
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
		int m = INF;                //INF��ʾ��������������Ϊ0x7fffffff
		int index = -1;
		for (int i = 0; i < 6; i++)   //ѭ���ҳ�ʣ������ʱ����̵ľ�������
		{
			if (pcb[i].status && nowTime >= pcb[i].arriveTime && pcb[i].serverTime - pcb[i].runTime < m)
			{
				m = pcb[i].serverTime - pcb[i].runTime;
				index = i;
			}
		}
		if (m == INF)                      //m=INF˵�����н����ѽ�����ǰʱ��û�е������
		{
			int cnt = 0;
			for (int i = 0; i < 6; i++)           //�ж��Ƿ����еĽ��̶������н���
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
		pro = &pcb[index];          //ѡ�н���
		pro->runTime++;            //����һ����λʱ��
		nowTime++;
		if (pro->runTime == pro->serverTime)   //����ʱ��=����ʱ�䣬˵�����̽�������¼����ʱ�䲢��ǽ���״̬
		{
			pro->status = false;
			pro->finishTime = nowTime;
			pro->turnAround = pro->finishTime - pro->arriveTime;
			pro->responseTime = pro->waitTime + pro->serverTime;
		}
		for (int i = 0; i < 6; i++)              //�����������̵ĵȴ�ʱ��+1
		{
			if (pcb[i].status && pcb[i].arriveTime < nowTime && pro != &pcb[i])
			{
				pcb[i].waitTime++;
			}
		}
	}
	sort(pcb, pcb + 6, name);                     //���������ƽ�������
	resultPrint();                                //��ӡ���н�����Ϣ
}
void RoundRobin()
{
	initial();                                 //��ʼ������
	sort(pcb, pcb + 6, fcfs);                //����FCFS��ͬ�Ĺ�������
	for (int i = 1; i < 6; i++)              //���������ɻ�״����
	{
		pcb[i - 1].next = &pcb[i];
	}
	struct PCB* head = &pcb[0];
	pcb[5].next = head;
	struct PCB* pro = head;
	int cnt;
	while (true)
	{
		if (pro->status && pro->arriveTime <= nowTime)         //����ѯ���Ľ��̾���ʱִ��һ��ʱ�䵥λ
		{
			pro->runTime++;
			nowTime++;
			if (pro->runTime == pro->serverTime)   //����ʱ����ڷ���ʱ��ʱ���̽���
			{
				pro->finishTime = nowTime;
				pro->status = false;
				pro->responseTime = pro->waitTime + pro->serverTime;
				pro->turnAround = pro->finishTime - pro->arriveTime;
			}
			for (int i = 0; i < 6; i++)                //��������״̬�Ľ��̵ȴ�ʱ��+1
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
		for (int i = 0; i < 6; i++)           //�ж��Ƿ����еĽ��̶������н���
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
