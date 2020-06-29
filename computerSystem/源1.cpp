#include<iostream>
#include<thread>
#include<mutex>
#include<ctime>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

//五支叉子
mutex fork[5];

//每个盘子剩余的面条
int nud[5] = { 50,50,50,50,50 };

//吃面条
void Eat(int id) {
	//id为哲学家编号
	while (true) {
		//尝试同时拿起左手边和右手边的叉子
		if (fork[id].try_lock()) {//先尝试拿起左手边的叉子
								  //如果能拿起左手边的叉子，再拿右手边的
			if (fork[(id + 1) % 5].try_lock()) {//如果也能拿起右手边的叉子，吃面条
												//开吃，每次吃掉的面条数量在10-20之间
				printf("哲学家%d开始吃面\n", id + 1);
				srand((unsigned)time(NULL));
				int numbereated = rand() % (20 - 10 + 1) + 10;
				sleep_for(seconds(numbereated % 10));//吃一段时间
				nud[id] -= numbereated;
				if (nud[id] <= 0) {
					printf("                          哲学家%d吃完了他的所有面\n", id + 1);
					fork[id].unlock();
					fork[(id + 1) % 5].unlock();
					break;
				}
				printf("哲学家%d吃完，面条剩余\n", id + 1, nud[id]);
				fork[id].unlock();
				fork[(id + 1) % 5].unlock();
				sleep_for(milliseconds(200));//吃完之后歇一会，让其它哲学家能够吃上
			}
			else {
				//如果没办法拿起右手边的叉子，就把左手边的叉子放下来
				fork[id].unlock();
				sleep_for(milliseconds(100));//歇一会，让其它哲学家能够吃上
			}
		}
	}
}

int main()
{
	printf("每人50面条\n");
	thread t1(Eat, 0);
	thread t2(Eat, 1);
	thread t3(Eat, 2);
	thread t4(Eat, 3);
	thread t5(Eat, 4);
	t1.join(); t2.join(); t3.join(); t4.join(); t5.join();
	printf("所有哲学家吃完\n");
	return 0;
}