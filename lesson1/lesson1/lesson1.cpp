
#include <iostream>
#include <vector>
#include <algorithm>

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

int findLargest(const std::vector<int>& nums) {
	return *max_element(nums.begin(), nums.end());
}

int main()
{
	vector<int> nums = {
		5, 12, 23, 7, 45,
		18, 29, 33, 41, 56,
		67, 72, 84, 91, 100,
		3, 9, 14, 27, 39, -371
	};
	int num;
	num = findLargest(nums);
	cout << num << endl;
	
	while (true)
	{
		cin >> num;
		eval(num);
	}
}

