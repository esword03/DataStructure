#include<iostream>
#include<algorithm>
#include<stack>
#include<queue>
using namespace std;

class Graph {
private:
	int *adjMatrix;// i,j=i*vn+j�ڽӾ��������ʾ
	int *adjMatrix1;
	int *ifv;//���α���Ⱦ�Ľڵ�
	int *ifv1;
	int vn;
	int ifn;//���α���Ⱦ�Ľڵ�����
	void dfs(int v, int *visited);
	int bgr=0;//����Ⱦ�Ľڵ�����
	void copyMatrix(int *Matrix,int *Matrix1 );
public:
	Graph();
	~Graph();
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v, int w);
	void dfs();
};

Graph::Graph() {
	cin >> vn;//����ͼ�ڵ���
	adjMatrix = new int[vn*vn];
	adjMatrix1 = new int[vn*vn];//�����ڽӾ���
	for (int i = 0; i < vn; i++) {//�����ڽӾ���
		for (int j = 0; j < vn; j++) {
			cin >> adjMatrix[i*vn + j];
		}
	}
	cin >> ifn;
	ifv = new int[ifn];
	for (int i = 0; i < ifn; i++) {
		cin >> ifv[i];
	}
	copyMatrix(adjMatrix, adjMatrix1);
}

Graph::~Graph() {
	delete[]adjMatrix;
	delete[]ifv;
}

int Graph::getFirstNeighbor(int v) {
	for (int col = 0; col < vn; col++) {
		if (adjMatrix[v*vn + col]) {
			return col;
		}
	}
	return -1;
}

int Graph::getNextNeighbor(int v, int w) {
	for (int col = w+1; col < vn; col++) {
		if (adjMatrix[v*vn + col]) {
			return col;
		}
	}
	return -1;
}
void Graph::copyMatrix(int *MatrixA, int *MatrixB) {
	for (int i = 0; i < vn; i++) {//�����ڽӾ���
		for (int j = 0; j < vn; j++) {
			MatrixB[i*vn + j] = MatrixA[i*vn + j];
		}
	}
}

void Graph::dfs() {
	int result=-1;
	int currentBgr=10000;//��ǰ����Ⱦ�Ľڵ���
	int *visited = new int[vn]; //�Ѿ������ʵĽڵ�ֵΪ1������Ϊ0
	
	for (int j=0; j < ifn; j++) {
		for (int i1 = 0; i1 < vn; i1++) {//��ʼ�����нڵ�
			visited[i1] = 0;
		}
		//ifv[j] = -1;
		for (int x = 0; x < vn; x++) {//ɾ���ڵ�
			for (int y = 0; y < vn; y++) {
				if (x == ifv[j] || y == ifv[j]) {
					adjMatrix[x*vn + y] = 0;
				}
			}
		}

		for (int i=0; i < ifn; i++) {
			//cout << i << endl;
			if (!visited[i])dfs(ifv[i], visited);//�Ա���Ⱦ�ڵ����������ȱ���
		}
		if (bgr < currentBgr) {
			currentBgr = bgr;
			result = ifv[j];
			
		}
		else if (bgr = currentBgr) {
			result = -1;
		}
		bgr = 0;
		copyMatrix(adjMatrix1, adjMatrix);
	}
	cout << result;


	//for (int i = 0; i < vn; i++) {
	//	if (!visited[i])dfs(i, visited);//����dfs���������нڵ�
	//}
	//delete[]visited;
	//dfs(0, visited);
}

void Graph::dfs(int v, int *visited) { //������ȱ���
	
	//cout << v << "    ";//�����ǰ�ڵ�
	visited[v] = 1;	//���������Ľڵ���Ϊ1
	bgr++;
	int w = getFirstNeighbor(v);
	while (w != -1) {
		if (!visited[w]) {
			dfs(w, visited);
		}
		w = getNextNeighbor(v, w);
	}
}
int main() {
	Graph g;
	g.dfs();
	return 0;
}