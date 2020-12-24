#include "../../Utilities.h"

#define ONE 1
#define TWO 2

using namespace std;

void E(tuple<int, int, int>& ref) {
	get<0>(ref) += 1;
	get<1>(ref) -= 1;
}

void SE(tuple<int, int, int>& ref) {
	get<0>(ref) += 1;
	get<2>(ref) -= 1;
}

void SW(tuple<int, int, int>& ref) {
	get<1>(ref) += 1;
	get<2>(ref) -= 1;
}

void W(tuple<int, int, int>& ref) {
	get<0>(ref) -= 1;
	get<1>(ref) += 1;
}

void NW(tuple<int, int, int>& ref) {
	get<0>(ref) -= 1;
	get<2>(ref) += 1;
}

void NE(tuple<int, int, int>& ref) {
	get<1>(ref) -= 1;
	get<2>(ref) += 1;
}

tuple<int, int, int> e(tuple<int, int, int> ref) {
	E(ref);
	return ref;
}

tuple<int, int, int> se(tuple<int, int, int> ref) {
	SE(ref);
	return ref;
}

tuple<int, int, int> sw(tuple<int, int, int> ref) {
	SW(ref);
	return ref;
}

tuple<int, int, int> w(tuple<int, int, int> ref) {
	W(ref);
	return ref;
}
tuple<int, int, int> nw(tuple<int, int, int> ref) {
	NW(ref);
	return ref;
}

tuple<int, int, int> ne(tuple<int, int, int> ref) {
	NE(ref);
	return ref;
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

#define WHITE false
#define BLACK true

	map<tuple<int, int, int>, bool> hexagons;

	for (int l = 0; l < lines.size(); l++) {
		tuple<int, int, int> pos = { 0,0,0 };
		int i = 0;
		string line = lines[l];
		while (i < line.size()) {
			char d = GetChar(line, i);
			if (d == 'n') {
				d = GetChar(line, i);
				if (d == 'e') {
					NE(pos);
				} else {
					NW(pos);
				}
			} else if (d == 's') {
				d = GetChar(line, i);
				if (d == 'e') {
					SE(pos);
				}
				else {
					SW(pos);
				}
			}
			else if (d == 'e') {
				E(pos);
			}
			else {
				W(pos);
			}
		}
		
		if (hexagons.count(pos) == 0)
			hexagons[pos] = WHITE;

		hexagons[pos] = !hexagons[pos];
	}

	int count = 0;
	for (auto h : hexagons) {
		if (h.second == BLACK) count++;
	}
	cout << count << endl;

	map<tuple<int, int, int>, int> neighbourCounter;

	cout << "|--------|" << endl;

	for (int day = 0; day < 100; day++) {
		neighbourCounter.clear();
		for (auto h : hexagons) {
			auto p = h.first;
			int inc = h.second == BLACK;
			if (neighbourCounter.count(p) == 0) neighbourCounter[p] = 0;
			NE(p);
			if (neighbourCounter.count(p) == 0) neighbourCounter[p] = 0;
			neighbourCounter[p] += inc;
			SE(p);
			if (neighbourCounter.count(p) == 0) neighbourCounter[p] = 0;
			neighbourCounter[p] += inc;
			SW(p);
			if (neighbourCounter.count(p) == 0) neighbourCounter[p] = 0;
			neighbourCounter[p] += inc;
			W(p);
			if (neighbourCounter.count(p) == 0) neighbourCounter[p] = 0;
			neighbourCounter[p] += inc;
			NW(p);
			if (neighbourCounter.count(p) == 0) neighbourCounter[p] = 0;
			neighbourCounter[p] += inc;
			NE(p);
			if (neighbourCounter.count(p) == 0) neighbourCounter[p] = 0;
			neighbourCounter[p] += inc;
		}

		for (auto n : neighbourCounter) {
			if (hexagons.count(n.first) == 0) {
				if (n.second == 2) hexagons[n.first] = BLACK;
			}
			else if (hexagons[n.first] == WHITE) {
				if (n.second == 2) hexagons[n.first] = BLACK;
				else hexagons.erase(n.first);
			}
			else {
				if (n.second == 0 || n.second > 2) hexagons.erase(n.first);
			}
		}

		if ((day + 1) % 10 == 0) cout << '#';
	}

	cout << endl;

	count = 0;
	for (auto h : hexagons) {
		if (h.second == BLACK) count++;
	}
	cout << count << endl;
}