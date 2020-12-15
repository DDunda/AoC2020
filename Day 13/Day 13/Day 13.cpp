#include "../../Utilities.h"

// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
// I did not write Part 2.

#define ONE 1
#define TWO 2

using namespace std;

struct guess {
	uintmax_t bus;
	uintmax_t o;
};

struct bguess {
	intmax_t x;
	uintmax_t mx;
};

// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
struct Bus { std::uintmax_t Index, ID; };

// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
template <typename T>
T ModPow(T Base, T Exp, T Modulo)
{
	Base %= Modulo;
	T Result = T(1);
	while (Exp > 0)
	{
		if (Exp & 1) Result = (Result * Base) % Modulo;
		Base = (Base * Base) % Modulo;
		Exp >>= 1;
	}
	return Result;
}

// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
std::uintmax_t Part2(const std::vector<Bus>& Busses)
{
	std::uintmax_t Product = 1;
	for (const auto& Bus : Busses) Product *= Bus.ID;
	std::uintmax_t Sum{};
	for (const auto& Bus : Busses)
	{
		const std::uintmax_t P = Product / Bus.ID;
		Sum += (Bus.ID - Bus.Index) * P * ModPow(P, Bus.ID - 2, Bus.ID);
	}
	return Sum % Product;
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

#define PART TWO
#if PART == ONE
	int i = 0;
	int estimate = GetInt(lines[0], i);
	i = 0;
	vector<int> bus;
	while (i < lines[1].size()) {
		string token = GetUntil(lines[1], i, ',');
		i++;
		if (token != "x") {
			int j = 0;
			bus.push_back(GetInt(token, j));
		}
	}
	SortVector(bus);

	int minWaitTime = -1;
	int minBus = 0;
	for (int b : bus) {
		int time = 0;
		while (time < estimate) time += b;
		int wait = time - estimate;
		if (minWaitTime == -1 || wait < minWaitTime) {
			minWaitTime = wait;
			minBus = b;
		}
	}
	cout << minWaitTime * minBus << endl;
#elif PART == TWO
	int i = 0;
	int estimate = GetInt(lines[0], i);
	i = 0;
	uintmax_t o = 0;
	vector<Bus> busses;
	int max = 0;
	int maxo = 0;
	while (i < lines[1].size()) {
		string token = GetUntil(lines[1], i, ',');
		i++;
		if (token != "x") {
			uintmax_t n = stoi(token);
			busses.push_back({ o, n });
		}
		o++;
	}

	// https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/gfnm16i?utm_source=share&utm_medium=web2x&context=3
	cout << Part2(busses) << endl;
	return;
#endif
}