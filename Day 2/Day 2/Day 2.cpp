#define ONE 1
#define TWO 2
#define PART TWO

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

int GetInt(string& input, int& iter) {
	int output = 0;
	for (; iter < input.size() && input[iter] >= '0' && input[iter] <= '9'; iter++) {
		output *= 10;
		output += input[iter] - '0';
	}
	return output;
}

string GetToEnd(string& input, int& iter) {
	string output;
	for (; iter < input.size(); iter++)
		output += input[iter];

	return output;
}

char GetChar(string& input, int& iter) {
	if (iter < input.size())
		return input[iter++];

	return NULL;
}

string GetNChars(string& input, int& iter, int n) {
	string output;
	for(int i = 0; i < n; i++)
		output += GetChar(input, iter);

	return output;
}

int main()
{
	string line;
	ifstream input;
	input.open("input.txt");
	int valid = 0;

	while (getline(input, line)) {
		int i = 0;
#if PART == ONE
		int min = GetInt(line, i); i += 1;
		int max = GetInt(line, i); i += 1;
		char letter = GetChar(line, i); i += 2;
		string password = GetToEnd(line, i);

		int counter = 0;
		for (char c : password) if (c == letter) counter++;

		if (counter < min || counter > max) continue;
#elif PART == TWO
		int pos1 = GetInt(line, i) - 1; i += 1;
		int pos2 = GetInt(line, i) - 1; i += 1;
		char letter = GetChar(line, i); i += 2;
		string password = GetToEnd(line, i);

		if ((password[pos1] == letter) == (password[pos2] == letter)) continue;
#endif
		cout << password << endl;
		valid++;
	}

	cout << valid << endl;
	input.close();
}