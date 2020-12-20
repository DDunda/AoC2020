#include "../../Utilities.h"

#define ONE 1
#define TWO 2

using namespace std;

long long Eval1(string, int&);

long long GetNumber1(string line, int& iter) {
	while (iter < line.size() && IsWhitespace(line[iter])) iter++;
	if (iter >= line.size())
		return -1;
	if (line[iter] == '(') {
		iter++;
		return Eval1(line, iter);
	}
	return GetInt(line, iter);
}

long long Eval1(string line, int& iter) {
	if (iter >= line.size())
		return -1;
	long long number = GetNumber1(line, iter);
	while (iter < line.size()) {
		while (iter < line.size() && IsWhitespace(line[iter])) iter++;
		char op = line[iter];
		iter++;
		switch (op)
		{
		case ')':
			return number;
		case '+':
			number += GetNumber1(line, iter);
			break;
		case '*':
			number *= GetNumber1(line, iter);
			break;
		}
	}
	return number;
}
long long Eval2(string, int&);

long long GetNumber2(string line, int& iter) {
	while (iter < line.size() && IsWhitespace(line[iter])) iter++;
	if (iter >= line.size())
		return -1;
	if (line[iter] == '(') {
		iter++;
		return Eval2(line, iter);
	}
	return GetInt(line, iter);
}

struct operation {
	long long number;
	char type;
};

long long Eval2(string line, int& iter) {
	if (iter >= line.size())
		return -1;
	vector<long long> nums = { GetNumber2(line, iter) };
	while (iter < line.size()) {
		while (iter < line.size() && IsWhitespace(line[iter])) iter++;
		char op = line[iter];
		iter++;
		if (op == ')') break;
		else if (op == '+') nums[nums.size() - 1] += GetNumber2(line, iter);
		else nums.push_back(GetNumber2(line, iter));
	}
	long long number = 1;
	for (int i = 0; i < nums.size(); i++) {
		number *= nums[i];
	}
	return number;
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

	long long sum1 = 0;
	long long sum2 = 0;
	int iter = 0;
	for (string line : lines) {
		iter = 0;
		sum1 += Eval1(line, iter);
		iter = 0;
		sum2 += Eval2(line, iter);
	}
	cout << "Part One:" << endl << sum1 << endl << "Part Two:" << endl << sum2 << endl;
}