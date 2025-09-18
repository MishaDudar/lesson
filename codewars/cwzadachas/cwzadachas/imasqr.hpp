//https://www.codewars.com/kata/54c27a33fb7da0db0100040e
#include <cmath>
bool is_square(int n)
{
	if (n<1)
	{
		return 0;
	}
	float sq = sqrt(n);
	if (round(sq) == sq)
	{
		return 1;
	}
	else {
		return 0;
	}
}