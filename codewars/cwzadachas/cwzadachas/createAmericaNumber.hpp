//https://www.codewars.com/kata/525f50e3b73515a6db000b83
#include <string>

using namespace std;

std::string createPhoneNumber(const int arr[10]) {
	return "(" + to_string(arr[0]) + to_string(arr[1]) + to_string(arr[2]) + ") " + to_string(arr[3]) + to_string(arr[4]) + to_string(arr[5])+"-" + to_string(arr[6]) + to_string(arr[7]) + to_string(arr[8]) + to_string(arr[9]);
}
