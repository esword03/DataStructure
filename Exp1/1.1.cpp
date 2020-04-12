#include <iostream>
#include <cmath>
#include <algorithm>
#include "1.1.h"
using namespace std;

int isp(char op) {
	int ret = 0;
	switch (op)
	{
	case '+':
	case '-':
		ret = 3;
		break;
	case '*':
	case '/':
	case'%':
		ret = 5;
		break;
	case '^':
		ret = 7;
		break;
	case '(':
		ret = 1;
		break;
	case ')':
		ret = 10;
		break;
	case '#':
		ret = 0;
		break;
	case'u':
		ret = 9;
		break;
	case'a':
		ret = 10;
		break;
	default:
		break;
	}
	return ret;
}

int icp(char op) {
	int ret = 0;
	switch (op)
	{
	case '+':
	case '-':
		ret = 2;
		break;
	case '*':
	case '/':
	case'%':
		ret = 4;
		break;
	case '^':
		ret = 6;
		break;
	case '(':
		ret = 10;
		break;
	case ')':
		ret = 1;
		break;
	case '#':
		ret = 0;
		break;
	case'u':
		ret = 8;
		break;
	case'a':
		ret = 10;
		break;
	default:
		break;
	}
	return ret;
}

class Calculator {
public:
	Calculator() {}
	int Run();
	void Clear();
private:
	void AddOperand(int value);
	bool Get2Operands(int& left, int& right);
	void DoOperator(char op);
	void DoOperator1(char op);
	bool Get1Operands(int& right);
	void AddOperator(char op);

	Stack<int> opds;
	Stack<char> oprs;
};
void Calculator::DoOperator1(char op) {
	int right;
	bool result;

	result = Get1Operands(right);
	if (!result) {
		Clear();
		return;
	}
	switch (op)
	{
	case 'u':
		opds.push(-right);
		break;
	case 'a':
		opds.push(abs(right));
		break;
		return;
	};
}

bool Calculator::Get1Operands(int& right) {
	if (opds.empty()) {
		cout << "NULL" << endl;
		return false;
	}
	right = opds.top();
	opds.pop();

	return true;
}

int Calculator::Run() {
	char ch;
	int newoperand;

	Clear();
	oprs.push('#');
	cin >> ch;
	while (ch != '=') {
		if (ch=='(') {
			AddOperator(ch);
			cin >> ch;
			if (ch == '-') {
				ch = 'u';
				AddOperator(ch);
			}
			else if(isdigit(ch)){
				cin.putback(ch);
				cin >> newoperand;
				AddOperand(newoperand);
			}
			else if(ch!='='){
				AddOperator(ch);
			}
			else {
				cout << "NULL" << endl;
				break;
			}
		}
		else if (isdigit(ch)) {
			cin.putback(ch);
			cin >> newoperand;
			AddOperand(newoperand);
		}
		else {
			AddOperator(ch);
		}

		cin >> ch;
	}
	AddOperator('#');
	return opds.top();
};

void Calculator::Clear() {
	while (!opds.empty()) {
		opds.pop();
	}
	while (!oprs.empty()) {
		oprs.pop();
	}
	return;
};

void Calculator::AddOperand(int value) {
	opds.push(value);
};

bool Calculator::Get2Operands(int& left, int& right) {
	if (opds.empty()) {
		cout << "NULL" << endl;
		return false;
	}
	right = opds.top();
	opds.pop();

	if (opds.empty()) {
		cout << "NULL" << endl;
		return false;
	}
	left = opds.top();
	opds.pop();

	return true;
};

void Calculator::DoOperator(char op) {
	if (op == 'u' || op == 'a') {
		DoOperator1(op);
	}
	else {
		int left, right;
		bool result;

		result = Get2Operands(left, right);
		if (!result) {
			Clear();
			return;
		}
		switch (op)
		{
		case '+':
			opds.push(left + right);
			break;
		case '-':
			opds.push(left - right);
			break;
		case '*':
			opds.push(left * right);
			break;
		case '/':
			if (right == 0) {
				cout << "NULL" << endl;
				Clear();
				return;
			}
			opds.push(left / right);
			break;
		case '^':
			opds.push(pow(left, right));
			break;
		case'%':
			opds.push(left%right);
			break;
		default:
			break;
		}
		return;
	}
};

void Calculator::AddOperator(char op) {
	if (op == ')') {
		while (!oprs.empty() &&
			oprs.top() != '('&&
			oprs.top() != '#') {
			DoOperator(oprs.top());
			oprs.pop();
		}
		if (oprs.top() == '#') {
			cout << "NULL" << endl;
			Clear();
			return;
		}
		else {
			oprs.pop();
		}
	}
	else if (op == '#') {
		while (!oprs.empty() &&
			oprs.top() != '(' &&
			oprs.top() != '#') {
			DoOperator(oprs.top());
			oprs.pop();
		}
		if (oprs.top() == '(') {
			cout << "NULL" << endl;
			Clear();
			return;
		}
		oprs.pop();
	}
	else if (op == 'b'||op=='s') {
		return;
	}
	else {
		while (!oprs.empty() && isp(oprs.top()) > icp(op)) {
			DoOperator(oprs.top());
			oprs.pop();
		}
		oprs.push(op);
	}
};

int main()
{
	Calculator cal;
	cout << cal.Run();
	cout << endl;
	return 0;
}
