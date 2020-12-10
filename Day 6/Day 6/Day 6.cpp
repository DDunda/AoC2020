#define ONE 1
#define TWO 2

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

#define PART TWO

#if PART == ONE
	bool answers[26];
	int total = 0;
	for (int i = 0; i < 26; i++) answers[i] = false;
	for (string line : lines) {
		if (line.length() == 0) {
			int count = 0;
			for (int i = 0; i < 26; i++) {
				if (answers[i]) count++;
				answers[i] = false;
			}
			total += count;
		}
		else {
			for (char c : line) answers[c - 'a'] = true;
		}
	}
#elif PART == TWO
	int answers[26];
	int total = 0;
	int groupCount = 0;
	for (int i = 0; i < 26; i++) answers[i] = 0;
	for (string line : lines) {
		if (line.length() == 0) {
			int count = 0;
			for (int i = 0; i < 26; i++) {
				if (answers[i] == groupCount) count++;
				answers[i] = 0;
			}
			total += count;
			groupCount = 0;
		}
		else {
			for (char c : line) answers[c - 'a']++;
			groupCount++;
		}
	}
#endif
	cout << total;
}