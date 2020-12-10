#include "../../Utilities.h"

#define ONE 1
#define TWO 2

using namespace std;

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

	vector<int> numbers;

	for (string line : lines) {
		int i = 0;
		numbers.push_back(GetInt(line, i));
	}
	deque<int> queue;
	for (int i = 0; i < 25; i++) queue.push_back(numbers[i]);

#define PART TWO
#if PART == ONE
	for (int i = 25; i < numbers.size(); i++) {
		bool found = false;
		for (int x = 0; x < 25; x++) {
			for (int y = 0; y < 25; y++) {
				if (queue[x] + queue[y] == numbers[i] && x != y) {
					found = true;
				}
			}
		}
		if (!found) {
			cout << numbers[i];
			return;
		}
		queue.push_back(numbers[i]);
		queue.pop_front();
	}
#elif PART == TWO
	int invalid = 0;
	for (int i = 25; i < numbers.size(); i++) {
		bool found = false;
		for (int x = 0; x < 25; x++) {
			for (int y = 0; y < 25; y++) {
				if (queue[x] + queue[y] == numbers[i] && x != y) {
					found = true;
				}
			}
		}
		if (!found) {
			invalid = numbers[i];
			break;
		}
		queue.push_back(numbers[i]);
		queue.pop_front();
	}
	for (int i = 0; i < numbers.size(); i++) {
		int sum = numbers[i];
		int j = i + 1;
		while (sum < invalid) {
			sum += numbers[j];
			j++;
		}
		if (sum == invalid) {
			int min = numbers[i];
			int max = numbers[i];
			for (int k = i; k < j; k++) {
				if (numbers[k] < min) min = numbers[k];
				if (numbers[k] > max) max = numbers[k];
			}
			cout << min + max;
			return;
		}
	}
#endif
}