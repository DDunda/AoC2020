#define ONE 1
#define TWO 2

#include <iostream>
#include <iomanip>
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
	return GetSign(input,iter) * GetInt(input, iter);
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

#define NOP 0
#define JMP 1
#define ACC 2

struct op {
	int t = 0; // Type
	int o = 0; // Offset
};

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

	vector<op> instructions;
	int opCount = 0;
	for (string line : lines) {
		int iter = 0;
		string code = GetToken(line, iter);
		int type = -1;
		if (code == "nop") type = NOP;
		else if (code == "acc") type = ACC;
		else if (code == "jmp") type = JMP;
		if (type != -1) {
			instructions.push_back({ type, GetSignedInt(line, iter) });
			opCount++;
		}
	}

	// Tracks whether a certain instruction has been visited
	bool* visited = new bool[opCount] {false};

#define PART ONE
#if PART == ONE
	int acc = 0; // Accumulator
	int pc = 0; //  Program counter
	int pcWidth = ceil(log10(opCount));
	if (pcWidth < 2) pcWidth = 2;
	pcWidth++;
	int offWidth = 3;
	for (op o : instructions) {
		int l = to_string(o.o).size();
		if (l > offWidth) offWidth = l;
	}

	cout << left << setw(pcWidth) << " PC" << " \xB3 OPC \xB3 " << left << setw(offWidth) << "OFF" << " \xB3 ACC" << endl;
	cout << string(pcWidth, '\xC4') << "\xC4\xC5\xC4\xC4\xC4\xC4\xC4\xC5\xC4" << string(offWidth, '\xC4') << "\xC4\xC5\xC4\xC4\xC4\xC4\xC4\xC4" << endl;

	while (pc < opCount) {
		visited[pc] = true;
		op o = instructions[pc];
		switch (o.t)
		{
		case ACC:
			acc += o.o;
			cout << right << setw(pcWidth) << pc << " \xB3 ACC \xB3 " << right << setw(offWidth) << o.o << " \xB3 " << acc << endl;
			pc++;
			break;
		case NOP:
			cout << right << setw(pcWidth) << pc << " \xB3 NOP \xB3 " << right << setw(offWidth) << o.o << " \xB3 " << acc << endl;
			pc++;
			break;
		case JMP:
			cout << right << setw(pcWidth) << pc << " \xB3 JMP \xB3 " << right << setw(offWidth) << o.o << " \xB3 " << acc << endl;
			pc += o.o;
			break;
		}
		if (visited[pc]) {
			break;
		}
	}
#elif PART == TWO
	for (int i = 0; i < opCount; i++) {
		// Revert change
		if (i == 0) {}
		else if (instructions[i-1].t == NOP) instructions[i-1].t = JMP;
		else if (instructions[i-1].t == JMP) instructions[i-1].t = NOP;

		// Swap NOP<->JMP (skip if ACC)
		if      (instructions[i].t == NOP) instructions[i].t = JMP;
		else if (instructions[i].t == JMP) instructions[i].t = NOP;
		else continue;

		int acc = 0; // Accumulator
		int pc = 0; //  Program counter

		while (pc < opCount) {
			visited[pc] = true;
			op o = instructions[pc];
			switch (o.t)
			{
				case ACC:
					acc += o.o;
				case NOP:
					pc++;
					break;
				case JMP:
					pc += o.o;
					break;
			}
			if (visited[pc]) break; // Infinite loop
		}

		if (pc >= opN) {
			cout << acc << endl;
			break;
		}

		for (int j = 0; j < opCount; j++) visited[j] = false;
	}
#endif
	delete[] visited;
}