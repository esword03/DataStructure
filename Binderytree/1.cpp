#include <algorithm>
#include<stack>	
#include<iostream>
using namespace std;
class BiTreeNode {
public:
	int data;
	BiTreeNode *leftChild;
	BiTreeNode *rightChild;
	BiTreeNode(int elem):data(elem){}
};

class BinaryTree {
private:
	BiTreeNode *root;
	void makeEmpty(BiTreeNode *current);
	void Create(BiTreeNode * &current);
	void PreOrder(BiTreeNode *current);
	void InOrder(BiTreeNode *current);
	void PostOrder(BiTreeNode *current);
public:
	BinaryTree():root(NULL){}
	~BinaryTree();
	void Create();
	void PreOrder();
	void InOrder();
	void PostOrder();
};

BinaryTree::~BinaryTree() {
	makeEmpty(root);
}

void BinaryTree::makeEmpty(BiTreeNode *current) {
	if (current != NULL) {
		makeEmpty(current->leftChild);
		makeEmpty(current->rightChild);
		delete current;
	}
}
void BinaryTree::Create() {
	Create(root);
}
void BinaryTree::Create(BiTreeNode * &current) {
	int elem;

	cin >> elem;

	if (elem == 0) {
		current = NULL;
	}
	else {
		current = new BiTreeNode(elem);
		Create(current->leftChild);
		Create(current->rightChild);
	}
}

void BinaryTree::PreOrder() {
	PreOrder(root);
}

void BinaryTree::PreOrder(BiTreeNode *current) {
	if (current != NULL) {
		cout << current->data << "  ";
		PreOrder(current->leftChild);
		PreOrder(current->rightChild);
	}
}
void BinaryTree::InOrder() {
	InOrder(root);
}

void BinaryTree::InOrder(BiTreeNode *current) {
	if (current != NULL) {
		InOrder(current->leftChild);
		cout << current->data << "  ";
		InOrder(current->rightChild);
	}
}
void BinaryTree::PostOrder() {
	PostOrder(root);
}

void BinaryTree::PostOrder(BiTreeNode *current) {
	if (current != NULL) {
		PostOrder(current->leftChild);
		PostOrder(current->rightChild);
		cout << current->data << "  ";
	}
}

int main() {
	BinaryTree myTree;
	myTree.Create();
	myTree.PreOrder(); cout << endl;
	myTree.InOrder(); cout << endl;
	myTree.PostOrder(); cout << endl;
}