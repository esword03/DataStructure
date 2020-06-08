#include<iostream>
#include<cstring>
#include<cstdlib>
#include<stack>
#include<queue>
#include<vector>
#include<string>
using namespace std;
class Node
{
public:
	Node(int data)
	{
		left = NULL;
		right = NULL;
		this->data = data;
	}
	Node *left, *right;
	int data;
};

typedef vector<int> tree;
vector<tree> test;
Node* Tree(string s, int left, int right)
{
	if (left > right)
		return NULL;
	Node* root;
	int a = 0;
	int i;
	for (i = left; i <= right; i++)
	{
		if (s[i] == '{')
			a++;
		else if (s[i] == '}')
			a--;
		if (a == 0 && i != left)
			break;
	}
	i += 2;
	string num = "";
	int j;
	for (j = i; s[j] >= '0' && s[j] <= '9'; j++)
	{
		num += s[j];
	}
	int n = atoi(num.c_str());
	root = new Node(n);
	root->left = Tree(s, left + 1, i - 3);
	root->right = Tree(s, j + 2, right - 1);

	return root;
}
void Load(Node* root, int level)
{
	if (root == NULL)
		return;
	if (level >= test.size())
	{
		tree v;
		v.push_back(root->data);
		test.push_back(v);
	}
	else
	{
		test[level].push_back(root->data);
	}
	Load(root->left, level + 1);
	Load(root->right, level + 1);
}
void Preview(Node* root)
{
	if (root == NULL)
		return;
	cout << root->data << " ";
	Preview(root->left);
	Preview(root->right);
}
void Level(Node* root)
{
	if (root == NULL)return;
	queue<Node*>q;
	q.push(root);
	while (!q.empty())
	{
		root = q.front();
		if (root->left != NULL)
			q.push(root->left);
		if (root->right != NULL)
			q.push(root->right);
		cout << q.front()->data << " ";
		q.pop();
	}
}




