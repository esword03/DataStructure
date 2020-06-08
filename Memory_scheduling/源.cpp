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
	int content;//页面号
	int timer;//被访问标记
}page1;
page1 block[Bsize];//页框数
page1 page[Psize];//页面号串


int pageChange=0;//页面置换次数
void Init(void)
{//初始化
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
{//查找是否有空闲内存
	for (int i = 0; i<Bsize; i++)
		if (block[i].content == -1)
			return i;//找到空闲内存，返回BLOCK中位置
	return -1;
}
int findExist(int curpage)
{//查找内存中是否有该页面
	for (int i = 0; i<Bsize; i++)
		if (block[i].content == page[curpage].content)
			return i;//找到内存中有该页面，返回BLOCK中位置
	return -1;
}
int  findReplace(void)
{//查找应予置换的页面，被置换的页面的Timer值最大
	int pos = 0;
	for (int i = 0; i<Bsize; i++)
		if (block[i].timer >= block[pos].timer)
			pos = i;//找到应予置换页面，返回BLOCK中位置
	return pos;
}

void  display(void)
{//显示
	for (int i = 0; i<Bsize; i++)
		if (block[i].content != -1)
			cout << block[i].content << " ";
	cout << endl;
}
void  Optimal(void)
{//OPTIMAL算法
	int exist, space, position;
	for (int i = 0; i<Psize; i++)
	{
		exist = findExist(i);
		if (exist != -1)
		{
			cout << "不缺页" << endl;
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
			{//没有找到空闲分区，需找一个页面进行置换
				pageChange++;
				for (int k = 0; k<Bsize; k++)
					for (int j = i; j<Psize; j++)
					{
						if (block[k].content != page[j].content)
						{
							block[k].timer = 1000;
						}//将来不会用，设置TIMER为一个很大数
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
	cout << "页框数：" << Bsize << endl;
	cout << "缺页数量：" << pageChange+Bsize << endl;
	cout << "页面置换数量：" << pageChange << endl;
}
void LRU(void)
{//LRU算法
	int exist, space, position;
	for (int i = 0; i<Psize; i++)
	{
		exist = findExist(i);
		if (exist != -1)
		{
			cout << "不缺页" << endl;
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
			{//没有找到空闲分区，需找一个页面进行置换
				pageChange++;
				position = findReplace();
				block[position] = page[i];
				display();
			}
		}
		for (int j = 0; j<Bsize; j++)
			block[j].timer++;//BLOCK中所有页面TIMER++
	}
	cout << "页框数：" << Bsize << endl;
	cout << "缺页数量：" << pageChange+Bsize << endl;
	cout << "页面置换数量：" << pageChange << endl;
}
void FIFO(void)
{

	int exist, space, position;

	for (int i = 0; i<Psize; i++)
	{
		exist = findExist(i);
		if (exist != -1)
		{
			cout << "不缺页" << endl;
		}

		else
		{  //找到空闲分区
			space = findSpace();
			if (space != -1)
			{
				block[space] = page[i];
				display();
			}
			else
			{//没有找到空闲分区，需找一个页面进行置换
				pageChange++;
				position = findReplace();
				block[position] = page[i];
				display();
			}
		}
		for (int j = 0; j<Bsize; j++)
			block[j].timer++;//BLOCK中所有页面TIMER++
	}
	cout << "页框数：" << Bsize << endl;
	cout << "缺页数量：" << pageChange+Bsize << endl;
	cout << "页面置换数量：" << pageChange << endl;
}
void BlockClear(void)
{
	pageChange = 0;//初始化置换数
	for (int i = 0; i<Bsize; i++)
	{
		block[i].content = -1;
		block[i].timer = 0;
	}
}
void main(void) {
	Init();
	cout << "选择1应用Optimal算法" << endl;
	cout << "选择2应用FIFO算法" << endl;
	cout << "选择3应用LRU算法" << endl;
	cout << "选择0退出" << endl;
	int select=1;


	while (select)
	{
		cin >> select;
		switch (select)
		{
		case 0:
			break;
		case 1:
			cout << "Optimal算法结果如下:" << endl;
			Optimal();
			BlockClear();
			cout << "----------------------" << endl;
			break;
		case 2:
			cout << "FIFO算法结果如下:" << endl;
			FIFO();
			BlockClear();
			cout << "----------------------" << endl;
			break;

		case 3:
			cout << "LRU算法结果如下:" << endl;
			LRU();
			BlockClear();
			cout << "----------------------" << endl;
			break;
		default:
			cout << "请输入正确功能号" << endl;
			break;
		}

	}
}
