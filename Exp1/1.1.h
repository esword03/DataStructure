#pragma once
#include<assert.h>
template<class Type> class Stack {
private:
	int Top;
	Type *elements;
	int maxSize;
public:
	Stack(int = 300);
	~Stack() { delete[] elements; }
	void push(const Type & item);
	Type pop();
	Type top();
	void clear() { Top = -1; }
	int empty()const { return Top == -1; }
	int IsFull()const { return Top == maxSize - 1; }
};
template <class Type>
Stack<Type >::Stack(int s) :Top(-1), maxSize(s) {
	elements = new Type[maxSize];
	assert(elements != 0);
}
template <class Type>
void Stack<Type >::push(const Type& item) {
	assert(!IsFull());
	elements[++Top] = item;
}
template <class Type>
Type Stack<Type >::pop() {
	assert(!empty());
	return elements[Top--];
}
template <class Type>
Type Stack<Type >::top() {
	assert(!empty());
	return elements[Top];
}