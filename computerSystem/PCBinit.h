#include<iostream>
using namespace std;
int nowTime = 0;
struct PCB {
	string name;
	int arriveTime;    //����ʱ��
	int runTime;       //��ǰ���е�ʱ��
	int serverTime;    //Ҫ�����е�ʱ��
	int finishTime;		//���ʱ��
	int priority;       //���ȼ�
	int turnAround;
	int waitTime;
	int responseTime;
	struct PCB* next;
	bool status;
	bool operator<(const struct PCB &a)const
	{
		if (priority != a.priority)
			return priority > a.priority;
		return serverTime - runTime > a.serverTime - a.runTime;
	}
}pcb[6];


void initial()
{
	int data[6][3] = { { 0,6,3 },{5,10,4}, { 10,50,1 },{ 15,20,5 },{ 40,10,6 },{ 80,40,3 } };
	nowTime = 0;
	char c = 'A';
	for (int i = 0; i < 6; i++)
	{
		pcb[i].name = c;
		c++;
		pcb[i].arriveTime = data[i][0];
		pcb[i].serverTime = data[i][1];
		pcb[i].priority = data[i][2];
		pcb[i].next = NULL;
		pcb[i].runTime = 0;
		pcb[i].status = true;
		pcb[i].waitTime = 0;
		pcb[i].responseTime = 0;
		pcb[i].turnAround = 0;
	}
}
