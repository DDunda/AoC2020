#include "../../Utilities.h"

#define ONE 1
#define TWO 2

using namespace std;

struct range {
	int min, max;
};

struct field {
	string name;
	vector<range> ranges;
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
	int li = 0;
	vector<field> fields;
	while (lines[li] != "") {
		int i = 0;
		string name = GetUntil(lines[li], i, ':');
		i++;
		vector<range> ranges;
		do {
			int min = GetInt(lines[li], i);
			i++;
			int max = GetInt(lines[li], i);
			ranges.push_back({ min, max });
		} while (GetToken(lines[li], i) == "or");
		fields.push_back({ name, ranges });
		li++;
	}

	vector<int> myTicket;
	li += 2;
	int i = 0;
	do {
		myTicket.push_back(GetInt(lines[li], i));
	} while (GetChar(lines[li], i) == ',');

	vector<vector<int>> nearTickets;
	li += 2;
	for (; li < lines.size(); li++) {
		vector<int> tmp;
		i = 0;
		do {
			tmp.push_back(GetInt(lines[li], i));
		} while (GetChar(lines[li], i) == ',');
		nearTickets.push_back(tmp);
	}

	int total = 0;
	
	for (vector<int> nums : nearTickets) {
		for (int num : nums) {
			bool valid = false;
			for (field f : fields) {
				for (range r : f.ranges) {
					if (num >= r.min && num <= r.max) valid = true;
				}
			}
			if (!valid) total += num;
		}
	}
	cout << total;
#elif PART == TWO
	int li = 0;
	vector<field> fields;
	while (lines[li] != "") {
		int i = 0;
		string name = GetUntil(lines[li], i, ':');
		i++;
		vector<range> ranges;
		do {
			int min = GetInt(lines[li], i);
			i++;
			int max = GetInt(lines[li], i);
			ranges.push_back({ min, max });
		} while (GetToken(lines[li], i) == "or");
		fields.push_back({ name, ranges });
		li++;
	}

	vector<int> myTicket;
	li += 2;
	int i = 0;
	do {
		myTicket.push_back(GetInt(lines[li], i));
	} while (GetChar(lines[li], i) == ',');

	vector<vector<int>> nearTickets;
	li += 3;
	for (; li < lines.size(); li++) {
		vector<int> tmp;
		i = 0;
		do {
			tmp.push_back(GetInt(lines[li], i));
		} while (GetChar(lines[li], i) == ',');
		nearTickets.push_back(tmp);
	}

	int total = 0;

	for (int ti = 0; ti < nearTickets.size(); ti++ ) {
		for (int num : nearTickets[ti]) {
			bool valid = false;
			for (field f : fields) {
				for (range r : f.ranges) {
					if (num >= r.min && num <= r.max) valid = true;
				}
			}
			if (!valid) {
				nearTickets[ti] = nearTickets[nearTickets.size() - 1];
				nearTickets.pop_back();
				ti--;
				break;
			}
		}
	}

	vector<vector<int>> columns(nearTickets[0].size());
	for (vector<int>& nums : nearTickets) {
		for (int i = 0; i < nums.size(); i++) {
			columns[i].push_back(nums[i]);
		}
	}

	vector<string> columnNames(columns.size());
	vector<vector<int>*> toAnalyse(columns.size());
	vector<field> remainingFields(fields);
	for (int i = 0; i < columns.size(); i++) {
		toAnalyse[i] = &columns[i];
	}

	while (remainingFields.size() > 0) {
		for (int c = 0; c < toAnalyse.size(); c++) {
			if (toAnalyse[c] != NULL) {
				string name = "";
				int fieldindex = -1;
				vector<int>& cCol = *toAnalyse[c];
				for (int f = 0; f < remainingFields.size(); f++) {
					bool valid = true;
					field& cField = remainingFields[f];
					for (int i = 0; i < cCol.size(); i++) {
						bool inRange = false;
						for (range r : cField.ranges) {
							if (cCol[i] >= r.min && cCol[i] <= r.max) {
								inRange = true;
								break;
							}
						}
						if (!inRange) {
							valid = false;
							break;
						}
					}
					if (valid) {
						if (fieldindex != -1) {
							name = "";
							fieldindex = -1;
							break;
						}
						name = cField.name;
						fieldindex = f;
					}
				}
				if (fieldindex != -1) {
					columnNames[c] = name;
					toAnalyse[c] = NULL;
					EraseSwap(remainingFields, fieldindex);
				}
			}
		}
	}

	long long product = 1;
	for (int c = 0; c < columns.size(); c++) {
		int i = 0;
		if (GetToken(columnNames[c], i) == "departure") {
			cout << c  << ": " << myTicket[c] << endl;
			product *= myTicket[c];
		}
	}
	cout << endl;
	cout<< product << endl;
#endif
}