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

struct BagQ {
	int num;
	string name;
};

bool checkRecursive(string colour, map<string, vector<BagQ>>& bs) {
	for (auto b : bs[colour]) {
		if (b.name == "shiny gold") return true;
		else if (checkRecursive(b.name, bs)) return true;
	}
	return false;
}

long countRecursive(string colour, map<string, vector<BagQ>>& bs) {
	if (bs.size() == 0) return 1;
	long long counter = 1;
	for (auto b : bs[colour]) {
		counter += b.num * countRecursive(b.name, bs);
	}
	return counter;
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

	map<string, vector<BagQ>> bags;

	for (string line : lines) {
		int i = 0;
		vector<string> nameTk;
		string token;
		while (i < line.size() && (token = GetToken(line, i)) != "contain") {
			nameTk.push_back(token);
		}
		nameTk.pop_back();
		string name = nameTk[0];
		for (int t = 1; t < nameTk.size(); t++) name += " " + nameTk[t];

		vector<BagQ> contents;

		while (i < line.size()) {
			i++;
			int size = GetInt(line, i);
			vector<string> subTk;
			do {
				token = GetToken(line, i);
				subTk.push_back(token);
			} while (
				token != "bag," &&
				token != "bags," &&
				token != "bag." &&
				token != "bags."
				);
			subTk.pop_back();
			string sub = subTk[0];
			for (int t = 1; t < subTk.size(); t++) sub += " " + subTk[t];
			if (sub != "no other") {
				contents.push_back({ size,sub });
			}
		}

		bags[name] = contents;
	}

#define PART TWO

#if PART == ONE
	int c = 0;
	for (auto b : bags) {
		if (b.first != "shiny gold") {
			if (checkRecursive(b.first, bags)) c++;
		}
	}
	cout << c;
#elif PART == TWO
	cout << countRecursive("shiny gold", bags) - 1;
#endif
}