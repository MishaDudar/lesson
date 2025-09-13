
#include <iostream>

using namespace std;

void eval(int num) {
	if (num % 2 == 0)
	{
		cout << "the num is even" << endl;
	}
	else
	{
		cout << "the num is odd" << endl;
	}
}

int main()
{
	int num;
	while (true)
	{
		cin >> num;
		eval(num);
	}
}

