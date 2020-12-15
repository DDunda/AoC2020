#include "../../Utilities.h"

#define ONE 1
#define TWO 2

using namespace std;

struct mask {
	unsigned long long a;
	unsigned long long o;
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

#define PART TWO
#if PART == ONE
	unsigned long long andMask = ~(0uLL);
	unsigned long long orMask = 0uLL;
	map<unsigned long long, unsigned long long> addrs;
	for (string line : lines) {
		int i = 0;
		string token = GetToken(line, i);
		i += 2;
		if (token == "mask") {
			i += 1;
			andMask = 0;
			orMask = 0;
			for (int b = 0; b < 36; b++) {
				andMask <<= 1;
				orMask <<= 1;
				char c = GetChar(line, i);
				if (c == 'X') {
					andMask |= 1;
				}
				else {
					orMask |= c - '0';
				}
			}
		}
		else {
			int j = 4;
			unsigned long long addr = GetInt(line, j);
			unsigned long long value = GetInt(line, i);
			j++;
			addrs[addr] = (value & andMask) | orMask;
		}
	}
	unsigned long long sum = 0;
	for (auto kp : addrs) {
		sum += kp.second;
	}
	cout << sum << endl;
#elif PART == TWO
	sizeof(long);
	vector<mask> masks;
	map<unsigned long long, unsigned long long> addrs;
	for (string line : lines) {
		int i = 0;
		string token = GetToken(line, i);
		i += 2;
		if (token == "mask") {
			i += 1;
			masks.clear();
			masks.push_back({0,0});
			for (int b = 0; b < 36; b++) {
				for (mask& m : masks) {
					m.a <<= 1;
					m.o <<= 1;
				}
				char c = GetChar(line, i);
				if (c == 'X') {
					vector<mask> tmp = masks;
					for (mask m : tmp) {
						masks.push_back({ m.a, m.o | 1 });
					}
				}
				else if (c == '0') {
					for (mask& m : masks) {
						m.a |= 1;
					}
				}
				else {
					for (mask& m : masks) {
						m.o |= 1;
					}
				}
			}
		}
		else {
			int j = 4;
			unsigned long long addr = GetInt(line, j);
			unsigned long long value = GetInt(line, i);
			for(mask m : masks) {
				unsigned long long addr2 = (addr & m.a) | m.o;
				addrs[addr2] = value;
			}
		}
	}
	unsigned long long sum = 0;
	for (auto kp : addrs) {
		sum += kp.second;
	}
	cout << sum << endl;
#endif
}