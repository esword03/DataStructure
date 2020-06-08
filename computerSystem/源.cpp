//
//#include<iostream>
//#include<string>
//#include<queue>
//using namespace std;
//typedef struct pcb {
//	string pName;  //进程名
//	float arriveTime;//到达时间
//	float serviceTime;//服务时间
//	float estimatedRunningtime;//要求运行时间
//	float startTime;//开始运行时间
//	float finishTime;//完成运行时间
//	float turnaroundTime;//周转时间
//	float weightedTuraroundTime;//平均周转时间
//	float rank;//优先级
//	float waitingTime;//等待时间
//	float respinseTime;//相应时间
//	char state;//状态
//
//	bool operator<(const pcb &a)const {
//		if (arriveTime == a.arriveTime) return rank > a.rank;
//		return arriveTime > a.arriveTime;
//	}
//}PCB;
//
//void createProcess(priority_queue<PCB> &p, int n) {//创建n个进程
//	cout << endl << endl << "创建进程" << endl;
//	PCB r;//工作结点
//	for (int i = 0; i<n; i++) {
//		cout << "请输入第" << i + 1 << "个进程的名字、到达时间、服务时间、优先级(例如:A 12 8):";
//		cin >> r.pName;
//		cin >> r.arriveTime;
//		cin >> r.serviceTime;
//		cin >> r.rank;
//		r.state = 'A';
//		r.startTime = 0;
//		r.finishTime = 0;
//		r.estimatedRunningtime = r.serviceTime;
//		r.turnaroundTime = 0;
//		r.weightedTuraroundTime = 0;
//		r.waitingTime = 0;
//		r.respinseTime = 0;
//		p.push(r);
//	}
//}
//
//void printProcess(priority_queue<PCB> p) {//输出所有进程的信息
//	PCB q;
//	cout << "进程名\t到达时间 要求运行时间 开始时间 运行结束时间 周转时间 平均周转时间 等待时间" << endl;
//	while (p.size() != 0) {
//		q = p.top();
//		cout << q.pName << "\t" << q.arriveTime << "\t " << q.serviceTime << "\t  ";
//		cout << q.startTime << "\t   " << q.finishTime << "\t    " << q.turnaroundTime << "\t     " << q.weightedTuraroundTime << endl;
//		p.pop();
//	}
//	cout << endl << endl;
//}
//
//void runProcess(priority_queue<PCB> &p, priority_queue<PCB> &q, int n) {//运行进程
//	PCB s;
//	float finishTimeOfPriorProcess;
//	for (int i = 0; i<n; i++) {
//		s = p.top();
//		if (i == 0) {//当前进程是第一个进程
//			while (s.estimatedRunningtime != 0) {//输出当前运行进程的信息
//				cout << "正在运行的进程" << endl;
//				cout << "进程名\t到达时间 服务时间 已运行时间 还剩运行时间" << endl;
//				cout << s.pName << "\t" << s.arriveTime << "\t " << s.serviceTime << "\t  ";
//				cout << s.serviceTime - s.estimatedRunningtime << "\t     " << s.estimatedRunningtime << endl;
//				s.estimatedRunningtime--; //当前进程的估计运行时间减1
//			}
//			s.startTime = s.arriveTime;
//			s.finishTime = s.startTime + s.serviceTime;
//			s.turnaroundTime = s.finishTime - s.arriveTime;
//			s.weightedTuraroundTime = float(s.turnaroundTime*1.0 / n);
//			s.state = 'C';
//			s.waitingTime = finishTimeOfPriorProcess - s.arriveTime;
//
//			finishTimeOfPriorProcess = s.finishTime;
//
//		}
//		else {//当前进程不是第一个进程
//			while (s.estimatedRunningtime != 0) {
//				cout << "正在运行的进程" << endl;
//				cout << "进程名\t到达时间 服务时间 已运行时间 还剩运行时间" << endl;
//				cout << s.pName << "\t" << s.arriveTime << "\t " << s.serviceTime << "\t  ";
//				cout << s.serviceTime - s.estimatedRunningtime << "\t     " << s.estimatedRunningtime << endl;
//				s.estimatedRunningtime--;//当前进程的估计运行时间减1
//
//			}
//			s.startTime = finishTimeOfPriorProcess>s.arriveTime ? finishTimeOfPriorProcess : s.arriveTime;
//			s.finishTime = s.startTime + s.serviceTime;
//			s.turnaroundTime = s.finishTime - s.arriveTime;
//			s.weightedTuraroundTime = float(s.turnaroundTime*1.0 / n);
//			s.state = 'C';
//			finishTimeOfPriorProcess = s.finishTime;
//		}
//		q.push(s);
//		p.pop();
//		cout << "进程" << s.pName << "执行结束之后就绪队列中的进程" << endl;
//		printProcess(p);
//	}
//	cout << endl << endl;
//}
//
//int main() {
//	priority_queue<PCB> p, q;
//	int n;
//	cout << "请输入进程的个数:";
//	cin >> n;
//	createProcess(p, n);
//	runProcess(p, q, n);
//	cout << "所有进程执行结束之后的相关情况" << endl << endl;
//	printProcess(q);
//	getchar();
//	getchar();
//	return 0;
//}
