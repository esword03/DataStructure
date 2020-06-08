//
//#include<iostream>
//#include<string>
//#include<queue>
//using namespace std;
//typedef struct pcb {
//	string pName;  //������
//	float arriveTime;//����ʱ��
//	float serviceTime;//����ʱ��
//	float estimatedRunningtime;//Ҫ������ʱ��
//	float startTime;//��ʼ����ʱ��
//	float finishTime;//�������ʱ��
//	float turnaroundTime;//��תʱ��
//	float weightedTuraroundTime;//ƽ����תʱ��
//	float rank;//���ȼ�
//	float waitingTime;//�ȴ�ʱ��
//	float respinseTime;//��Ӧʱ��
//	char state;//״̬
//
//	bool operator<(const pcb &a)const {
//		if (arriveTime == a.arriveTime) return rank > a.rank;
//		return arriveTime > a.arriveTime;
//	}
//}PCB;
//
//void createProcess(priority_queue<PCB> &p, int n) {//����n������
//	cout << endl << endl << "��������" << endl;
//	PCB r;//�������
//	for (int i = 0; i<n; i++) {
//		cout << "�������" << i + 1 << "�����̵����֡�����ʱ�䡢����ʱ�䡢���ȼ�(����:A 12 8):";
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
//void printProcess(priority_queue<PCB> p) {//������н��̵���Ϣ
//	PCB q;
//	cout << "������\t����ʱ�� Ҫ������ʱ�� ��ʼʱ�� ���н���ʱ�� ��תʱ�� ƽ����תʱ�� �ȴ�ʱ��" << endl;
//	while (p.size() != 0) {
//		q = p.top();
//		cout << q.pName << "\t" << q.arriveTime << "\t " << q.serviceTime << "\t  ";
//		cout << q.startTime << "\t   " << q.finishTime << "\t    " << q.turnaroundTime << "\t     " << q.weightedTuraroundTime << endl;
//		p.pop();
//	}
//	cout << endl << endl;
//}
//
//void runProcess(priority_queue<PCB> &p, priority_queue<PCB> &q, int n) {//���н���
//	PCB s;
//	float finishTimeOfPriorProcess;
//	for (int i = 0; i<n; i++) {
//		s = p.top();
//		if (i == 0) {//��ǰ�����ǵ�һ������
//			while (s.estimatedRunningtime != 0) {//�����ǰ���н��̵���Ϣ
//				cout << "�������еĽ���" << endl;
//				cout << "������\t����ʱ�� ����ʱ�� ������ʱ�� ��ʣ����ʱ��" << endl;
//				cout << s.pName << "\t" << s.arriveTime << "\t " << s.serviceTime << "\t  ";
//				cout << s.serviceTime - s.estimatedRunningtime << "\t     " << s.estimatedRunningtime << endl;
//				s.estimatedRunningtime--; //��ǰ���̵Ĺ�������ʱ���1
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
//		else {//��ǰ���̲��ǵ�һ������
//			while (s.estimatedRunningtime != 0) {
//				cout << "�������еĽ���" << endl;
//				cout << "������\t����ʱ�� ����ʱ�� ������ʱ�� ��ʣ����ʱ��" << endl;
//				cout << s.pName << "\t" << s.arriveTime << "\t " << s.serviceTime << "\t  ";
//				cout << s.serviceTime - s.estimatedRunningtime << "\t     " << s.estimatedRunningtime << endl;
//				s.estimatedRunningtime--;//��ǰ���̵Ĺ�������ʱ���1
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
//		cout << "����" << s.pName << "ִ�н���֮����������еĽ���" << endl;
//		printProcess(p);
//	}
//	cout << endl << endl;
//}
//
//int main() {
//	priority_queue<PCB> p, q;
//	int n;
//	cout << "��������̵ĸ���:";
//	cin >> n;
//	createProcess(p, n);
//	runProcess(p, q, n);
//	cout << "���н���ִ�н���֮���������" << endl << endl;
//	printProcess(q);
//	getchar();
//	getchar();
//	return 0;
//}
