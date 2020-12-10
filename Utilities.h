#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <map>
#include <deque>
#include <algorithm>

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

bool IsAlpha(char input) {
	return IsUpper(input) || IsLower(input);
}
bool IsAlpha(string& input) {
	for (char c : input)
		if (!IsAlpha(c))
			return false;
	return true;
}

bool IsAlphaNumeric(char& input) {
	return IsAlpha(input) || IsNumeric(input);
}
bool IsAlphaNumeric(string& input) {
	for (char c : input)
		if (!IsAlphaNumeric(c))
			return false;
	return true;
}

bool IsWhitespace(char input) {
	return input == ' ' || input == '\t' || input == '\r' || input == '\n';
}
bool IsWhitespace(string& input) {
	for (char c : input)
		if (!IsWhitespace(c))
			return false;
	return true;
}

char GetChar(string& input, int& iter) {
	if (iter >= input.size()) return NULL;

	return input[iter++];
}

int GetInt(string& input, int& iter) {
	int output = 0;
	while (iter < input.size() && IsWhitespace(input[iter])) iter++;
	for (; iter < input.size() && IsNumeric(input[iter]); iter++)
		output = (output * 10) + (input[iter] - '0');

	return output;
}

int GetSign(string& input, int& iter) {
	while (iter < input.size() && IsWhitespace(input[iter])) iter++;
	int sign = 0;
	if (iter < input.size()) {
		char s = GetChar(input, iter);
		if (s == '-') sign = -1;
		else if (s == '+') sign = 1;
		else iter--;
	}
	return sign;
}

int GetSignedInt(string& input, int& iter) {
	return GetSign(input, iter) * GetInt(input, iter);
}

string GetToEnd(string& input, int& iter) {
	string output;
	for (; iter < input.size(); iter++)
		output += input[iter];

	return output;
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

vector<string> Split(string const& in, string const& word) {
	vector<string> ret;

	int begin = 0;
	int end = 0;

	while (string::npos != (end = in.find(word, begin))) {
		ret.push_back(in.substr(begin, end - begin));
		begin = end + word.length() + 1;
		while (::isspace(in[begin]))
			++begin;
	}
	ret.push_back(in.substr(begin));
	return ret;
}

template<class T>
void SortDeque(deque<T>& t) {
	sort(t.begin(), t.end(), [](const T& x, const T& y) {
		return x < y;
	});
}

template<class T>
void SortVector(vector<T>& t) {
	sort(t.begin(), t.end(), [](const T& x, const T& y) {
		return x < y;
	});
}

template<class T>
void SortArray(T* start, T* end) {
	sort(start, end, [](const T& x, const T& y) {
		return x < y;
	});
}