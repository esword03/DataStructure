#include<iostream>
#include<thread>
#include<mutex>
#include<ctime>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

//��֧����
mutex fork[5];

//ÿ������ʣ�������
int nud[5] = { 50,50,50,50,50 };

//������
void Eat(int id) {
	//idΪ��ѧ�ұ��
	while (true) {
		//����ͬʱ�������ֱߺ����ֱߵĲ���
		if (fork[id].try_lock()) {//�ȳ����������ֱߵĲ���
								  //������������ֱߵĲ��ӣ��������ֱߵ�
			if (fork[(id + 1) % 5].try_lock()) {//���Ҳ���������ֱߵĲ��ӣ�������
												//���ԣ�ÿ�γԵ�������������10-20֮��
				printf("��ѧ��%d��ʼ����\n", id + 1);
				srand((unsigned)time(NULL));
				int numbereated = rand() % (20 - 10 + 1) + 10;
				sleep_for(seconds(numbereated % 10));//��һ��ʱ��
				nud[id] -= numbereated;
				if (nud[id] <= 0) {
					printf("                          ��ѧ��%d����������������\n", id + 1);
					fork[id].unlock();
					fork[(id + 1) % 5].unlock();
					break;
				}
				printf("��ѧ��%d���꣬����ʣ��\n", id + 1, nud[id]);
				fork[id].unlock();
				fork[(id + 1) % 5].unlock();
				sleep_for(milliseconds(200));//����֮��Ъһ�ᣬ��������ѧ���ܹ�����
			}
			else {
				//���û�취�������ֱߵĲ��ӣ��Ͱ����ֱߵĲ��ӷ�����
				fork[id].unlock();
				sleep_for(milliseconds(100));//Ъһ�ᣬ��������ѧ���ܹ�����
			}
		}
	}
}

int main()
{
	printf("ÿ��50����\n");
	thread t1(Eat, 0);
	thread t2(Eat, 1);
	thread t3(Eat, 2);
	thread t4(Eat, 3);
	thread t5(Eat, 4);
	t1.join(); t2.join(); t3.join(); t4.join(); t5.join();
	printf("������ѧ�ҳ���\n");
	return 0;
}