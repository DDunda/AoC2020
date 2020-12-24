#include "../../Utilities.h"

#define ONE 1
#define TWO 2

using namespace std;

struct Cup {
public:
	int label;
	Cup* clockwise = NULL;
	Cup* lowerNumber = NULL;
};

#define NUM_CUPS    1000000
#define PART2_MOVES 10000000

void main()
{
	string line;
	ifstream input;
	input.open("input.txt");
	getline(input, line);
	input.close();

	vector<int> cupInput;
	for(char label : line) {
		cupInput.push_back(label - '0');
	}

#define PART TWO
#if PART == ONE
	vector<int> cups = cupInput;
	int current = 0;
	for (int round = 0; round < 100; round++) {
		for (int i = 0; i < cups.size(); i++) cout << (i == current ? "(" + to_string(cups[i]) + ")" : " " + to_string(cups[i]) + " ");
		cout << endl;

		vector<int> removed;
		current++;
		for (int i = 0; i < 3; i++) {
			current %= cups.size();
			removed.push_back(cups[current]);
			EraseShift(cups, current);
		}
		current = (current + (cups.size() - 1)) % cups.size();

		int selected = cups[current];
		int destination = -1;
		while (destination == -1) {
			selected--;
			if (selected <= 0) selected = 9;
			for (int i = 0; i < cups.size(); i++) {
				if (cups[i] == selected && i != current) {
					destination = i;
					break;
				}
			}
		}
		if (destination < current) current += 3;
		while (removed.size() > 0) {
			cups.insert(cups.begin() + destination + 1, removed[removed.size() - 1]);
			removed.pop_back();
		}
		current++;
		current %= cups.size();
	}
	for (int i = 0; i < cups.size(); i++) cout << (i == current ? "(" + to_string(cups[i]) + ")" : " " + to_string(cups[i]) + " ");
	cout << endl;
#elif PART == TWO
	vector<Cup> cups(NUM_CUPS);

	Cup* cup1 = NULL;
	Cup* currentCup = &cups[0];

	Cup* prev = &cups[NUM_CUPS - 1];
	int i = 0;
	for (; i < cupInput.size(); i++) {
		cups[i].label = cupInput[i];
		prev->clockwise = &cups[i];
		prev = &cups[i];
		if (cupInput[i] == 1) cup1 = &cups[i];
	}
	for (; i < NUM_CUPS; i++) {
		cups[i].label = i + 1;
		cups[i].lowerNumber = prev;
		prev->clockwise = &cups[i];
		prev = &cups[i];
	}

	Cup* minCup = &cups[0];
	int min = minCup->label;
	Cup* maxCup = minCup;
	int max = min;

	for (int i = 0; i < cupInput.size(); i++) {
		if (cups[i].label < min) {
			min = cupInput[i];
			minCup = &cups[i];
		}
		if (cups[i].label > max) {
			max = cupInput[i];
			maxCup = &cups[i];
		}
	}

	minCup->lowerNumber = &cups[NUM_CUPS - 1];
	cups[cupInput.size()].lowerNumber = maxCup;
	
	for (Cup* cup = minCup; cup != maxCup; ) {
		int minmin = cup->label;
		Cup* minj = cup;
		int min = 0;
		for (int j = 0; j < cupInput.size(); j++) {
			if (cups[j].label > minmin && (minj == cup || cups[j].label < min)) {
				minj = &cups[j];
				min = minj->label;
			}
		}
		// l <--> j
		minj->lowerNumber = cup;
		cup = minj;
	}

	for (int move = 0; move < PART2_MOVES; move++) {

		Cup* removedCup1 = currentCup->clockwise;
		Cup* removedCup2 = removedCup1->clockwise;
		Cup* removedCup3 = removedCup2->clockwise;

		currentCup->clockwise = removedCup3->clockwise;

		Cup* destinationCup = currentCup;
		do {
			destinationCup = destinationCup->lowerNumber;
		} while (destinationCup == removedCup1 || destinationCup == removedCup2 || destinationCup == removedCup3);
		
		removedCup3->clockwise = destinationCup->clockwise;

		destinationCup->clockwise = removedCup1;

		currentCup = currentCup->clockwise;
	}

	cout << cup1->clockwise->label << " * " << cup1->clockwise->clockwise->label << " = " << (long long)cup1->clockwise->label * (long long)cup1->clockwise->clockwise->label << endl;
#endif
}