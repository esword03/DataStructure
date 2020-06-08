#include"6.1.h";

int main()
{
	string s1;
	cout << "ÊäÈë¶þ²æÊ÷£º";
	cin >> s1;
	Node* root = Tree(s1, 1, s1.length() - 2);
	Preview(root);
	cout << endl;
	Level(root);
	cout << endl;
	Load(root, 0);
	int max = 0;
	int index = 0;
	for (int i = 0; i < test.size(); i++)
	{
		if (max <= test[i].size())
		{
			max = test[i].size();
			index = i;
		}
	}
	cout << index << endl;
	cout << max << endl;
	cout << test.size() - 1 << endl;

	return 0;
}