#include "../../Utilities.h"

#define ONE 1
#define TWO 2

using namespace std;

void main()
{
	/*string line;
	ifstream input;
	input.open("input.txt");

	vector<string> lines;
	while (!input.eof()) {
		getline(input, line);
		lines.push_back(line);
	}
	int lineCount = lines.size();
	input.close();*/


#define PART TWO
#if PART == ONE
	vector<long long> numbers = { 18,8,0,5,4,1,20 };
	int turn = numbers.size() + 1;

	while (turn < 2021) {
		int i = 1;
		int gap = 0;
		int last = numbers[turn - 2];
		for (; i < turn - 1; i++) {
			if (numbers[i - 1] == last) {
				gap = (turn - 1) - i;
			}
		}
		turn++;
		numbers.push_back(gap);
	}

	cout << numbers[turn - 2] << endl;
#elif PART == TWO
	vector<long long> input = { 18,8,0,5,4,1,20 };
	int turn = input.size();

	map<long long, long long> numbers;
	for (int i = 0; i < turn; i++) numbers[input[i]] = i;

	long long lastNum = input[turn - 1];
	while (turn < 30000000) {
		long long thisNum = 0;
		if (numbers.count(lastNum) > 0)
			thisNum = (turn - 1) - numbers[lastNum];

		numbers[lastNum] = turn - 1;
		lastNum = thisNum;
		turn++;
	}

	cout << lastNum << endl;
#endif
}