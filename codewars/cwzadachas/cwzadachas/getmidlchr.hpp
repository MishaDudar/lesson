//https://www.codewars.com/kata/56747fd5cb988479af000028
#include <string>
using namespace std;

string get_middle(string input)
{
	string res="";
	if (input.size()%2==0)
	{
		res += input[input.size() / 2-1];
		res += input[input.size() / 2];
		return res;
	}
	else
	{
		res += input[input.size() / 2 + 0.5];
		return res;
	}
}