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

#define PART TWO
#if PART == ONE
	int* a = new int[lines.size()];
	int j = 0;
	for (string l : lines) {
		int i = 0;
		a[j] = GetInt(l, i);
		j++;
	}

	SortArray(a, a + lines.size());

	int d1 = 0;
	int d3 = 0;
	int jolts = 0;

	for (int i = 0; i < lines.size(); i++) {
		if (a[i] - jolts == 1) d1++;
		if (a[i] - jolts == 3) d3++;
		jolts = a[i];
	}
	d3++;
	jolts += 3;
	cout << d1 * d3;
	return;
#elif PART == TWO
	vector<int> a;
	a.push_back(0);
	for (string l : lines) {
		int i = 0;
		a.push_back(GetInt(l, i));
	}

	SortVector(a);

	long long c3 = 0;
	long long c2 = 0;
	long long c1 = 1;
	for (int i = 1; i < a.size(); i++) {
		int p = a[i];
		long long c = 0;
		if (i-1 >= 0 && p - a[i-1] <= 3) c += c1;
		if (i-2 >= 0 && p - a[i-2] <= 3) c += c2;
		if (i-3 >= 0 && p - a[i-3] <= 3) c += c3;
		c3 = c2;
		c2 = c1;
		c1 = c;
	}
	cout << c1;
#endif
}
