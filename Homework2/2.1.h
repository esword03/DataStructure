#include<cstdio>
#include<iostream>
using namespace std;
class ListNode {
public:
	int data;
	ListNode * link;
	ListNode() { data = NULL; link = NULL; };
	ListNode(int item, ListNode* node) { data = item; link = node; };
	ListNode* nextNode();
	//return the pointer to the next node
	void insertAfter(ListNode* p);
	ListNode* removeAfter();
};

class LinkedList {
public:
	ListNode* first;
	ListNode* last;

	LinkedList();
	void clear() { delete first; };
	int size();
	void append(int elem);
	int FindByVal(int elem);
	ListNode* FindByPos(int i);
	int insert(int value, int i);
	int remove(int i);

	//question2
	int  getMiddleelement();
	void removeDuplicates();
	void reverse();
	void pairwiseSwap();
};

void ListNode::insertAfter(ListNode* p){
	link = p;
}
ListNode* ListNode::removeAfter() {
	ListNode* next = link;
	link = next->link;//让link指向下下个节点
	delete next;
	return NULL;
}
LinkedList::LinkedList() {
	first = new ListNode(); 
	last = new ListNode();
	first->link = last;
}
int LinkedList::size() {
	int i = 0;
	ListNode* node = first->link;
	while (node != last) {
		i++;
		node = node->link;
	}
	return i;
}
void LinkedList::append(int elem) {
	ListNode* node = first;
	while (node->link != last) {
		node = node->link;
	}
	ListNode* node2 = new ListNode(elem, last);
	node->link = node2;
}
int LinkedList::FindByVal(int elem) {
	ListNode* start = first->link;
	int i = 1;
	while (start->data != elem && start->link != NULL) {
		i++;
		start = start->link;
	}
	if (start->data != elem && start->link == NULL) {
		return 0;
	}
	return i;
}
ListNode* LinkedList::FindByPos(int i) {
	int n = 0;
	ListNode* start = first;
	while (n < i) {
		start = start->link;
		n++;
	}
	return start;
}

int LinkedList::insert(int value, int i) {

		ListNode* p = first;
		while (i-- != 1) {
			p = p->link;
		}
		ListNode* q = new ListNode(value, p->link);
		p->insertAfter(q);
	return 1;
}
int LinkedList::remove(int i) {
		ListNode* p = first;
		for (int j = 1; j < i; j++) {
			p = p->link;
		}
		p->removeAfter();
	return 1;
}
//question2
int  LinkedList::getMiddleelement()
{
	if (first->link == last) {
		return NULL;
	}
	else {
		ListNode* middle = first->link;
		ListNode* all = first->link;
		int i = 0;
		int j = 0;
		while (all != last)
		{
			if (i / 2 > j)
			{
				j++;
				middle = middle->link;
			}
			i++;
			all = all->link;
		}
		if (i % 2 == 0)
		{
			return middle->link->data;
		}
		else
		{
			return middle->data;
		}
	}
}
void LinkedList::removeDuplicates()
{
	ListNode* n1 = first->link;
	ListNode* temp;
	while (n1!=last)
	{
		if (n1->link!=last)
		{
			ListNode* n2 = n1->link;
			temp = n1;
			while (n2) {
				if (n1->data == n2->data)
				{
					temp->link = n2->link;
				}
				temp = temp->link;
				n2 = n2->link;
			}
		}
		n1 = n1->link;
	}

}
void LinkedList::reverse() {
	cout << 1;
	ListNode* p = first->link;
	ListNode* temp;

	while (p->link!=last) {
		ListNode* r = first->link;
		temp = p->link;
		first->link = temp;
		p->link = temp->link;
		temp->link = r;
	}
}
void LinkedList::pairwiseSwap()
{
	ListNode* p = first->link;
	ListNode* q = first;
	ListNode* temp;
	while (p->link!=last)
	{
		temp = p->link;
		q->link = temp;
		p->link = temp->link;
		temp->link = p;
		q = p;
		if (p->link == NULL) {
			break;
		}
		p = p->link;
	}
};
