//https://www.codewars.com/kata/514b92a657cdc65150000006
#include <string>

using namespace std;

int solution(int number)
{
	int sum=0;
	for (int i = 0; i < number; i++)
	{
		if (i%3==0)
		{
			sum += i;
		}
		else if (i % 5 == 0)
		{
			sum += i;
		}
	}
	return sum;
}




