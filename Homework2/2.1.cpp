#include"2.1.h"

int main(){
	LinkedList *l1 = new LinkedList();
	l1->append(1);
	l1->append(2);
	l1->append(3);
	l1->append(4);
	l1->append(5);
	cout<<l1->size()<<endl;
	cout << l1->FindByPos(3)->data<<endl;
	l1->insert(4, 4);
	l1->remove(5);
	cout << l1->size()<<endl;
	cout << l1->FindByVal(5);
}