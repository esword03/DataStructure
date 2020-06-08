#include <stdio.h>
#include <iostream>
#include<string>
#include<time.h>
#include<math.h>
using namespace std;
#define Bsize 4
#define Psize 15
typedef struct page
{
	int content;//ҳ���
	int timer;//�����ʱ��
}page1;
page1 block[Bsize];//ҳ����
page1 page[Psize];//ҳ��Ŵ�


int pageChange=0;//ҳ���û�����
void Init(void)
{//��ʼ��
	int QString[15] = {1,2,4,3,6,3,7,4,3,2,5,5,3,8,1};

	for (int i = 0; i<Bsize; i++)
	{
		block[i].content = -1;
		block[i].timer = 0;
	}

	for (int i = 0; i<Psize; i++)
	{
		page[i].content = QString[i];
		page[i].timer = 0;
	}

}
int findSpace(void)
{//�����Ƿ��п����ڴ�
	for (int i = 0; i<Bsize; i++)
		if (block[i].content == -1)
			return i;//�ҵ������ڴ棬����BLOCK��λ��
	return -1;
}
int findExist(int curpage)
{//�����ڴ����Ƿ��и�ҳ��
	for (int i = 0; i<Bsize; i++)
		if (block[i].content == page[curpage].content)
			return i;//�ҵ��ڴ����и�ҳ�棬����BLOCK��λ��
	return -1;
}
int  findReplace(void)
{//����Ӧ���û���ҳ�棬���û���ҳ���Timerֵ���
	int pos = 0;
	for (int i = 0; i<Bsize; i++)
		if (block[i].timer >= block[pos].timer)
			pos = i;//�ҵ�Ӧ���û�ҳ�棬����BLOCK��λ��
	return pos;
}

void  display(void)
{//��ʾ
	for (int i = 0; i<Bsize; i++)
		if (block[i].content != -1)
			cout << block[i].content << " ";
	cout << endl;
}
void  Optimal(void)
{//OPTIMAL�㷨
	int exist, space, position;
	for (int i = 0; i<Psize; i++)
	{
		exist = findExist(i);
		if (exist != -1)
		{
			cout << "��ȱҳ" << endl;
		}
		else
		{
			space = findSpace();
			if (space != -1)
			{
				block[space] = page[i];//
				display();
			}
			else
			{//û���ҵ����з���������һ��ҳ������û�
				pageChange++;
				for (int k = 0; k<Bsize; k++)
					for (int j = i; j<Psize; j++)
					{
						if (block[k].content != page[j].content)
						{
							block[k].timer = 1000;
						}//���������ã�����TIMERΪһ���ܴ���
						else
						{
							block[k].timer = j;
							break;
						}
					}
				position = findReplace();
				block[position] = page[i];
				display();
				
			}
		}
	}
	cout << "ҳ������" << Bsize << endl;
	cout << "ȱҳ������" << pageChange+Bsize << endl;
	cout << "ҳ���û�������" << pageChange << endl;
}
void LRU(void)
{//LRU�㷨
	int exist, space, position;
	for (int i = 0; i<Psize; i++)
	{
		exist = findExist(i);
		if (exist != -1)
		{
			cout << "��ȱҳ" << endl;
			block[exist].timer = 0;
		}
		else
		{
			space = findSpace();
			if (space != -1)
			{
				block[space] = page[i];

				display();
			}
			else
			{//û���ҵ����з���������һ��ҳ������û�
				pageChange++;
				position = findReplace();
				block[position] = page[i];
				display();
			}
		}
		for (int j = 0; j<Bsize; j++)
			block[j].timer++;//BLOCK������ҳ��TIMER++
	}
	cout << "ҳ������" << Bsize << endl;
	cout << "ȱҳ������" << pageChange+Bsize << endl;
	cout << "ҳ���û�������" << pageChange << endl;
}
void FIFO(void)
{

	int exist, space, position;

	for (int i = 0; i<Psize; i++)
	{
		exist = findExist(i);
		if (exist != -1)
		{
			cout << "��ȱҳ" << endl;
		}

		else
		{  //�ҵ����з���
			space = findSpace();
			if (space != -1)
			{
				block[space] = page[i];
				display();
			}
			else
			{//û���ҵ����з���������һ��ҳ������û�
				pageChange++;
				position = findReplace();
				block[position] = page[i];
				display();
			}
		}
		for (int j = 0; j<Bsize; j++)
			block[j].timer++;//BLOCK������ҳ��TIMER++
	}
	cout << "ҳ������" << Bsize << endl;
	cout << "ȱҳ������" << pageChange+Bsize << endl;
	cout << "ҳ���û�������" << pageChange << endl;
}
void BlockClear(void)
{
	pageChange = 0;//��ʼ���û���
	for (int i = 0; i<Bsize; i++)
	{
		block[i].content = -1;
		block[i].timer = 0;
	}
}
void main(void) {
	Init();
	cout << "ѡ��1Ӧ��Optimal�㷨" << endl;
	cout << "ѡ��2Ӧ��FIFO�㷨" << endl;
	cout << "ѡ��3Ӧ��LRU�㷨" << endl;
	cout << "ѡ��0�˳�" << endl;
	int select=1;


	while (select)
	{
		cin >> select;
		switch (select)
		{
		case 0:
			break;
		case 1:
			cout << "Optimal�㷨�������:" << endl;
			Optimal();
			BlockClear();
			cout << "----------------------" << endl;
			break;
		case 2:
			cout << "FIFO�㷨�������:" << endl;
			FIFO();
			BlockClear();
			cout << "----------------------" << endl;
			break;

		case 3:
			cout << "LRU�㷨�������:" << endl;
			LRU();
			BlockClear();
			cout << "----------------------" << endl;
			break;
		default:
			cout << "��������ȷ���ܺ�" << endl;
			break;
		}

	}
}
