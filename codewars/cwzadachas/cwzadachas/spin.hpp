#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string spinWords(const string& str)	
{
	string res;
	string word;
	for (int i = 0; i < str.size(); i++)
	{
		//cout << "cycle" << endl;
		if (str[i] == ' ' )
		{
			if (word.size()>4)
			{

			
			reverse(word.begin(), word.end());
			
			res += word+" ";
			
			word = "";}
			else {
				res += word + " ";
				word = "";
				//cout << "as";
			}
		}
		else if (str[i] == str[str.size()])
		{
			if (word.size() > 4)
			{
				reverse(word.begin(), word.end());

				res += word;
			}
			else {
				res += word + " ";
				word = "";
				//cout << "as";
			}
		}

		else
		{
			word.push_back(str[i]);
			cout << i << " ";
		}
		
		
	}
	return res;
}