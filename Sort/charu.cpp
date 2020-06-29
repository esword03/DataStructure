#include <iostream>
using namespace std;

#include <assert.h>

//ֱ�Ӳ�������
void InsertSort(int* a, size_t n)
{
	assert(a);
	for (size_t i = 1; i < n; ++i)//��end��λ�ÿ��Ʊ߽�
	{
		//��������
		int end = i - 1;
		int tmp = a[i];
		while (end >= 0)//ѭ����������
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
	if (left >= right) //�˳�����
		return;
	if (right - left + 1 <10)//�Ż�
	{
		InsertSort(a + left, right - left + 1);
	}
	int mid = left + ((right - left) >> 1);
	__MergeSort(a, left, mid, tmp); // �ݹ��������
	__MergeSort(a, mid + 1, right, tmp); // �ݹ��Ұ�����

										 //���ź��������������鲢������

	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;
	int index = left;

	while (begin1 <= end1 && begin2 <= end2)// ѭ����������һ�����������꣬����ֹ���������û�бȽ��������ֱ��һһ����ȥ
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

	while (begin1 <= end1)//�Ұ�����������
	{
		tmp[index++] = a[begin1++];
	}
	while (begin2 <= end2)//�������������
	{
		tmp[index++] = a[begin2++];
	}

	//tmp�����Ѿ��ź���,���������ݿ���ԭ���飬�ݹ�����һ����
	index = left;
	while (index <= right)
	{
		a[index] = tmp[index];
		++index;
	}
}

// �鲢����
void MergeSort(int *a, size_t n)
{
	int *tmp = new int[n]; // ��һ����������������ȡ�����ź���鲢�������
	__MergeSort(a, 0, n - 1, tmp);
	delete[] tmp; // ����ͷŵ������ռ�
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
	//��������
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
