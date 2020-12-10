#define ONE 1
#define TWO 2
#define PART TWO

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

int GetInt(string& input, int& iter) {
	int output = 0;
	for (; iter < input.size() && input[iter] >= '0' && input[iter] <= '9'; iter++)
		output = output * 10 + input[iter] - '0';

	return output;
}

string GetToEnd(string& input, int& iter) {
	string output;
	for (; iter < input.size(); iter++)
		output += input[iter];

	return output;
}

char GetChar(string& input, int& iter) {
	if (iter >= input.size()) return NULL;

	return input[iter++];
}

string GetNChars(string& input, int& iter, int n) {
	string output;
	for (int i = 0; i < n; i++)
		output += GetChar(input, iter);

	return output;
}

int CountTrees(vector<string>& grid, int w, int h, int vx, int vy) {
	int y = 0;
	int x = 0;
	int trees = 0;
	while (y < h) {
		if (grid[y][x] == '#') trees++;
		x += vx;
		x %= w;
		y += vy;
	}
	return trees;
}
int main()
{
	string line;
	ifstream input;
	input.open("input.txt");

	vector<string> grid;
	while (getline(input, line)) {
		grid.push_back(line);
	}
#if PART == ONE
	int height = grid.size();
	int width = grid[0].size();
	int y = 0;
	int x = 0;
	int trees = 0;
	while (y < height) {
		if (grid[y][x] == '#') trees++;
		x += 3;
		x %= width;
		y++;
	}
	cout << trees;
#elif PART == TWO
	int height = grid.size();
	int width = grid[0].size();
	long long trees0 = CountTrees(grid, width, height, 1, 1);
	long long trees1 = CountTrees(grid, width, height, 3, 1);
	long long trees2 = CountTrees(grid, width, height, 5, 1);
	long long trees3 = CountTrees(grid, width, height, 7, 1);
	long long trees4 = CountTrees(grid, width, height, 1, 2);
	cout << trees0 * trees1 * trees2 * trees3 * trees4;
#endif
	input.close();
}

// Golf - 157 chars
/*
#include <fstream>
#include <string>
int main(){std::ifstream i("i");int x=0,t=0;for(std::string l;getline(i,l);(x+=3)%=l.size())t+=l[x]==35;printf("%i",t);}
*/