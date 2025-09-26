using namespace std;
//https://www.codewars.com/kata/53da3dbb4a5168369a0000fe
#include <string>

std::string even_or_odd(int number)
{
	if (number % 2 == 0) {
		return "Even";
	}
	return "Odd";
}
//https://www.codewars.com/kata/56bc28ad5bdaeb48760009b0
#include <string>
#include <algorithm>

using namespace std;

string sliceString(string str)
{
	str.pop_back();
	reverse(str.begin(), str.end());
	str.pop_back();
	reverse(str.begin(), str.end());

	return str;
}
//https://www.codewars.com/kata/5265326f5fda8eb1160004c8
#include <string>

std::string number_to_string(int num) {
	return std::to_string(num);
}
//https://www.codewars.com/kata/57a0e5c372292dd76d000d7e
// 
#include <string>

std::string repeat_str(size_t repeat, const std::string& str) {
	std::string result;
	result.reserve(repeat * str.size());
	for (size_t i = 0; i < repeat; ++i) {
		result += str;
	}
	return result;
}
//https://www.codewars.com/kata/5ab6538b379d20ad880000ab
int area_or_perimeter(int l, int w) {
	if (l == w) {
		return l * w;
	}
	else {
		return l * 2 + w * 2;
	}
	return 0;
}
//https://www.codewars.com/kata/583710ccaa6717322c000105
int simpleMultiplication(int a) {
	if (a % 2 == 0) {
		return a * 8;
	}
	else {
		return a * 9;
	}
}
//https://www.codewars.com/kata/53dc54212259ed3d4f00071c
#include <vector>

int sum(const std::vector<int>& nums) {
	float sum=0;
	for (size_t i = 0; i < nums.size(); i++)
	{
		sum += nums[i];
	}
	return sum;
}
//https://www.codewars.com/kata/56676e8fabd2d1ff3000000c
#include <vector>
#include <string>

std::string findNeedle(const std::vector<std::string>& haystack)
{
	for (int i = 0; i < haystack.size(); i++)
	{
		if (haystack[i]=="needle")
		{
			return "found the needle at position " + std::to_string(i);
		}
	}

        
}
//https://www.codewars.com/kata/57eae20f5500ad98e50002c5
#include <string>
#include <iostream>

std::string no_space(const std::string& x)
{
	string res;
	string word;
	for (int i = 0; i < x.size(); i++)
	{
		//cout << "cycle" << endl;
		if (x[i] == ' ')
		{
			
			
		}

		else
		{
			word.push_back(x[i]);
			//cout << i << " ";
		}


	}
	return word;
}
//https://www.codewars.com/kata/54edbc7200b811e956000556
#include <vector>

using namespace std;

int count_sheep(vector<bool> arr)
{
	int res=0;
	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i])
		{
			res++;
		}
	}
	return res;
}

