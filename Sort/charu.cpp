#include <iostream>
using namespace std;

#include <assert.h>

//直接插入排序
void InsertSort(int* a, size_t n)
{
	assert(a);
	for (size_t i = 1; i < n; ++i)//用end的位置控制边界
	{
		//单趟排序
		int end = i - 1;
		int tmp = a[i];
		while (end >= 0)//循环继续条件
		{
			if (a[end] > tmp)
			{
				a[end + 1] = a[end];
				--end;
			}
			else
				break;
		}
		a[end + 1] = tmp;
	}
}
void __MergeSort(int *a, int left, int right, int * tmp)
{
	if (left >= right) //退出条件
		return;
	if (right - left + 1 <10)//优化
	{
		InsertSort(a + left, right - left + 1);
	}
	int mid = left + ((right - left) >> 1);
	__MergeSort(a, left, mid, tmp); // 递归左半数组
	__MergeSort(a, mid + 1, right, tmp); // 递归右半数组

										 //将排好序的两部分数组归并（排序）

	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;
	int index = left;

	while (begin1 <= end1 && begin2 <= end2)// 循环条件：任一个数组排序完，则终止条件，最后将没有比较完的数组直接一一拷过去
	{
		if (a[begin1] <= a[begin2])
		{
			tmp[index++] = a[begin1++];
		}
		else
		{
			tmp[index++] = a[begin2++];
		}
	}

	while (begin1 <= end1)//右半数组走完了
	{
		tmp[index++] = a[begin1++];
	}
	while (begin2 <= end2)//左半数组走完了
	{
		tmp[index++] = a[begin2++];
	}

	//tmp数组已经排好序,将数组内容拷到原数组，递归向上一层走
	index = left;
	while (index <= right)
	{
		a[index] = tmp[index];
		++index;
	}
}

// 归并排序
void MergeSort(int *a, size_t n)
{
	int *tmp = new int[n]; // 开一个第三方数组来存取左右排好序归并后的序列
	__MergeSort(a, 0, n - 1, tmp);
	delete[] tmp; // 最后释放第三方空间
}

void Print(int a[], int len)
{
	cout << endl;

	for (int i = 0; i < len; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

void test()
{
	//升序排序
	int a[] = { 0,23,46,75,46,1,35,64};
	/*  int a[] = {2,5,4,0,9,3,6,8,7,1};*/
	int len = sizeof(a) / sizeof(a[0]);
	cout << "before sort :";
	Print(a, len);

	MergeSort(a, len);
	cout << "after sort :";
	Print(a, len);

}

int main()
{
	test();
	return 0;
}
