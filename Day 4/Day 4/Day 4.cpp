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

int main()
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

	int numValid = 0;
	int linenum = 0;
	int byr, iyr, eyr, hgt, hcl, ecl, pid;
	byr = iyr = eyr = hgt = hcl = ecl = pid = 0;
#if PART == ONE
	for (string line : lines) {
		if (line.size() == 0) {
			if (byr && iyr && eyr && hgt && hcl && ecl && pid) numValid++;
			byr = iyr = eyr = hgt = hcl = ecl = pid = 0;
		}
		else {
			int index = 0;
			while (index < line.size()) {
				string token = GetNChars(line, index, 3);
				index++;
				if (token == "byr") byr++;
				if (token == "iyr") iyr++;
				if (token == "eyr") eyr++;
				if (token == "hgt") hgt++;
				if (token == "hcl") hcl++;
				if (token == "ecl") ecl++;
				if (token == "pid") pid++;
				GetToken(line, index);
				index++;
			}
		}
	}
#elif PART == TWO
	for (string line : lines) {
		if (line.empty()) {
			if ((byr * iyr * eyr * hgt * hcl * ecl * pid) == 1) numValid++;
			else {
				numValid = numValid;
			}
			byr = iyr = eyr = hgt = hcl = ecl = pid = 0;
		}
		else {
			int index = 0;
			while (index < line.size()) {
				string token = GetNChars(line, index, 3);
				index++;
				if (token == "byr") {
					int yr = GetInt(line, index);
					if (yr >= 1920 && yr <= 2002) byr++;
				}
				else if (token == "iyr") {
					int yr = GetInt(line, index);
					if (yr >= 2010 && yr <= 2020) iyr++;
				}
				else if (token == "eyr") {
					int yr = GetInt(line, index);
					if (yr >= 2020 && yr <= 2030) eyr++;
				}
				else if (token == "hgt") {
					int h = GetInt(line, index);
					string suff = GetToken(line, index);
					if (suff == "in" && h >= 59 && h <= 76) hgt++;
					if (suff == "cm" && h >= 150 && h <= 193) hgt++;
				}
				else if (token == "hcl")
				{
					string colourcode = GetToken(line, index);
					char c = colourcode[0];
					if (c == '#') {
						string colour = colourcode.substr(1);
						if (colour.size() == 6 && IsChars(colour, "0123456789abcdef")) hcl++;
					}
				}
				else if (token == "ecl") {
					string col = GetToken(line, index);
					if (
						col == "amb" ||
						col == "blu" ||
						col == "brn" ||
						col == "gry" ||
						col == "grn" ||
						col == "hzl" ||
						col == "oth"
						) ecl++;
				}
				else if (token == "pid") {
					string num = GetToken(line, index);
					if (num.size() == 9 && IsNumeric(num)) pid++;
				}
				else if (token == "cid") {
					GetToken(line, index);
				}
				else {
					cout << token << endl;
				}
				while (index < line.size() && line[index] == ' ') index++;
			}
		}
	}
#endif
	cout << numValid;
}