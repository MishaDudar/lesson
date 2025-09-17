//https://www.codewars.com/kata/54ff3102c1bad923760001f3
#include <string>

using namespace std;

int getCount(string inputStr) {
	int num_vowels = 0;
	string vowels = "aeiou";
	int lastid;
	int lid = 0;
	while(true){
		lastid = inputStr.find(vowels[lid]);
		if (lastid != string::npos)
		{
			num_vowels++;
			inputStr.erase(lastid,1);
		}
		else {
			if (lid>=vowels.size())
			{
				return num_vowels;
			}
			lid++;
		}
		
	}
	
	
	
}
//в чужих рішеннях через count_if(), вперше його бачив