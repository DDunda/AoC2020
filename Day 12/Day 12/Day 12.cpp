#include "../../Utilities.h"

#define ONE 1
#define TWO 2

using namespace std;

struct instruction {
	char command;
	int number;
};

void main()
{
	string line;
	ifstream input;
	input.open("input.txt");

	vector<instruction> instructions;
	while (!input.eof()) {
		getline(input, line);
		char c = line[0];
		int i = 1;
		int ds = GetInt(line, i);
		if (c == 'R') {
			ds = (4 - (ds / 90)) % 4;
			c = 'r';
		} else if (c == 'L') {
			ds = (ds / 90) % 4;
			c = 'r';
		}
		instructions.push_back({c,ds});
	}
	input.close();

	ofstream output;
	output.open("output.csv");
	output << "result (1), result (2), time (1), time(2)" << endl;
	for(int k = 0; k < 10000; k++) {
	auto p1 = chrono::steady_clock::now();

	int x = 0, y = 0;
	int dir = 0;
	for (instruction l : instructions) {
		switch (l.command)
		{
		case 'N':
			y += l.number;
			break;
		case 'E':
			x += l.number;
			break;
		case 'S':
			y -= l.number;
			break;
		case 'W':
			x -= l.number;
			break;
		case 'r':
			dir = (dir + l.number) % 4;
			break;
		default:
			switch (dir) {
			case 0:
				x += l.number;
				break;
			case 1:
				y += l.number;
				break;
			case 2:
				x -= l.number;
				break;
			case 3:
				y -= l.number;
				break;
			}
		}
	}
	int result1 = abs(x) + abs(y);
	auto p2 = chrono::steady_clock::now();

	int wx = 10, wy = 1;
	x = 0, y = 0;
	for (instruction l : instructions) {
		switch (l.command)
		{
		case 'N':
			wy += l.number;
			break;
		case 'E':
			wx += l.number;
			break;
		case 'S':
			wy -= l.number;
			break;
		case 'W':
			wx -= l.number;
			break;
		case 'r':
			for (int i = 0; i < l.number; i++) {
				int k = wy;
				wy = wx;
				wx = -k;
			}
			break;
		default:
			x += wx * l.number;
			y += wy * l.number;
		}
	}
	int result2 = abs(x) + abs(y);
	auto p3 = chrono::steady_clock::now();

	//cout << "Part one: " << result1 << " (" << chrono::duration_cast<chrono::nanoseconds>(p2 - p1).count() / 1000000.0 << "ms)" << endl;
	//cout << "Part two: " << result2 << " (" << chrono::duration_cast<chrono::nanoseconds>(p3 - p2).count() / 1000000.0 << "ms)" << endl;
	output << result1 << ", " << result2 << ", " << chrono::duration_cast<chrono::nanoseconds>(p2 - p1).count() / 1000000.0 << ", " << chrono::duration_cast<chrono::nanoseconds>(p3 - p2).count() / 1000000.0 << endl;
	}
	output.close();
}