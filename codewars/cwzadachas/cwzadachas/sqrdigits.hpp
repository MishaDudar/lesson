//https://www.codewars.com/kata/546e2562b03326a88e000020
#include <string>

using namespace std;

int square_digits(int num) {
	if (num==0)
	{
		return 0;
	}
	int ent;
	string res = "";
	
	while (num!=0)
	{
		ent = num % 10;
		res = to_string((ent * ent))+res;
		
		num -= ent;
		num /= 10;
		
	}
	return stoi(res);
}
