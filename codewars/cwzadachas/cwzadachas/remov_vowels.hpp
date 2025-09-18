//https://www.codewars.com/kata/52fba66badcd10859f00097e
#include <string>

using namespace std;

string disemvowel(string inputStr) {
	
	string vowels = "aeiouAEOUI";
	int lastid;
	int lid = 0;
	while(true){
		lastid = inputStr.find(vowels[lid]);
		if (lastid != string::npos)
		{
			
			inputStr.erase(lastid,1);
		}
		else {
			if (lid>=vowels.size())
			{
				return inputStr;
			}
			lid++;
		}
		
	}
	
	
	
}
