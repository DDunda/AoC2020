#define ONE 1
#define TWO 2
#define PART TWO

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <map>

using namespace std;

bool IsChars(char input, string chars) {
	for (char c : chars)
		if (input == c)
			return true;
	return false;
}

bool IsChars(string& input, string chars) {
	for (char c : input)
		if (!IsChars(c, chars))
			return false;
	return true;
}

bool IsNumeric(char input) {
	return input >= '0' && input <= '9';
}
bool IsNumeric(string& input) {
	for (char c : input)
		if (!IsNumeric(c))
			return false;
	return true;
}

bool IsUpper(char input) {
	return input >= 'A' && input <= 'Z';
}
bool IsUpper(string& input) {
	for (char c : input)
		if (!IsUpper(c))
			return false;
	return true;
}

bool IsLower(char input) {
	return input >= 'a' && input <= 'z';
}
bool IsLower(string& input) {
	for (char c : input)
		if (!IsLower(c))
			return false;
	return true;
}

bool IsAlpha(string& input) {
	return IsUpper(input) || IsLower(input);
}

bool IsAlphaNumeric(string& input) {
	return IsAlpha(input) || IsNumeric(input);
}

bool IsWhitespace(string& input) {
	return IsChars(input, " \t\r\n");
}

int GetInt(string& input, int& iter) {
	int output = 0;
	for (; iter < input.size() && IsNumeric(input[iter]); iter++)
		output = (output * 10) + (input[iter] - '0');

	return output;
}

string GetToEnd(string& input, int& iter) {
	string output;
	for (; iter < input.size(); iter++)
		output += input[iter];

	return output;
}

char GetChar(string& input, int& iter) {
	if (iter >= input.size()) return NULL;

	return input[iter++];
}

string GetNChars(string& input, int& iter, int n) {
	string output = "";
	for (int i = 0; i < n; i++)
		output += GetChar(input, iter);

	return output;
}

string GetToken(string& input, int& iter) {
	string output = "";
	for (; iter < input.size() && input[iter] == ' '; iter++);
	for (; iter < input.size() && input[iter] != ' '; iter++)
		output += input[iter];

	return output;
}

string GetUntil(string& input, int& iter, char stop) {
	string output = "";
	for (; iter < input.size() && input[iter] != stop; iter++)
		output += input[iter];

	return output;
}

void main()
{
	string line;
	ifstream input;
	input.open("input.txt");

	vector<string> lines;
	while (!input.eof()) {
		getline(input, line);
		lines.push_back(line);
	}
	int lineCount = lines.size();
	input.close();

	bool* seats = new bool[128 * 8];
#if PART == ONE
	for (int i = 0; i < 128 * 8; i++) seats[i] = false;
	for (string line : lines) {
		int minY = 0;
		int maxY = 127;
		int changeY = 64;
		for (int i = 0; i < 7; i++) {
			if (line[i] == 'B') minY += changeY;
			else maxY -= changeY;
			changeY /= 2;
		}
		int minX = 0;
		int maxX = 7;
		int changeX = 4;
		for (int i = 0; i < 3; i++) {
			if (line[i+7] == 'R') minX += changeX;
			else maxX -= changeX;
			changeX /= 2;
		}
		seats[minX + minY * 8] = true;
	}
	for (int i = (128 * 8) - 1; i >= 0; i--) {
		if (seats[i]) {
			cout << i;
			return;
		}
	}
#elif PART == TWO
	for (int i = 0; i < 128 * 8; i++) seats[i] = false;
	for (string line : lines) {
		int minY = 0;
		int maxY = 127;
		int changeY = 64;
		for (int i = 0; i < 7; i++) {
			if (line[i] == 'B') minY += changeY;
			else maxY -= changeY;
			changeY /= 2;
		}
		int minX = 0;
		int maxX = 7;
		int changeX = 4;
		for (int i = 0; i < 3; i++) {
			if (line[i + 7] == 'R') minX += changeX;
			else maxX -= changeX;
			changeX /= 2;
		}
		seats[minX + minY * 8] = true;
	}
	for (int i = 1; i < 128 * 8 - 1; i++) {
		if (seats[i-1] && !seats[i] && seats[i+1]) {
			cout << i;
			return;
		}
	}
#endif
}

// Golf - 235 characters
//#include <fstream>
//#include <string>
//int main(){std::ifstream n("i");std::string l;int s[1024]={0},I,i=0;while(getline(n,l)){for(I=i=0;i<10;i++)I=I*2|!(l[i]%82*l[i]%66);s[I]=1;}for(i=1;i<1023;i++)if(s[i-1]&s[i+1]&!s[i])printf("%i",i);}