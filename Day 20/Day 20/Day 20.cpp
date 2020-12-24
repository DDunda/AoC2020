#include "../../Utilities.h"

#define ONE 1
#define TWO 2

using namespace std;

struct tile {
	int ID;
	bool data[100]{false};
	union {
		struct {
			short u, r, d, l;
			short uf, rf, df, lf;
		};
		struct {
			short sides[4];
			short sidesf[4];
		};
		short sidesd[8]{ 0 };
	};
	int x = 0, y = 0;
};

struct dragon {
	int w, h;
	bool shape[60];
};

#define I true,
#define O false,

const dragon dragons[8]{
	{
		20, 3,
		{
			O O O O O O O O O O O O O O O O O O I O
			I O O O O I I O O O O I I O O O O I I I
			O I O O I O O I O O I O O I O O I O O O
		}
	},
	{
		20, 3,
		{
			O I O O I O O I O O I O O I O O I O O O
			I O O O O I I O O O O I I O O O O I I I
			O O O O O O O O O O O O O O O O O O I O
		}
	},
	{
		20, 3,
		{
			O I O O O O O O O O O O O O O O O O O O
			I I I O O O O I I O O O O I I O O O O I
			O O O I O O I O O I O O I O O I O O I O
		}
	},
	{
		20, 3,
		{
			O O O I O O I O O I O O I O O I O O I O
			I I I O O O O I I O O O O I I O O O O I
			O I O O O O O O O O O O O O O O O O O O
		}
	},
	{
		3, 20,
		{
			O I O
			I O O
			O O O
			O O O
			I O O
			O I O
			O I O
			I O O
			O O O
			O O O
			I O O
			O I O
			O I O
			I O O
			O O O
			O O O
			I O O
			O I O
			O I I
			O I O
		}
	},
	{
		3, 20,
		{
			O I O
			O I I
			O I O
			I O O
			O O O
			O O O
			I O O
			O I O
			O I O
			I O O
			O O O
			O O O
			I O O
			O I O
			O I O
			I O O
			O O O
			O O O
			I O O
			O I O
		}
	},
	{
		3, 20,
		{
			O I O
			O O I
			O O O
			O O O
			O O I
			O I O
			O I O
			O O I
			O O O
			O O O
			O O I
			O I O
			O I O
			O O I
			O O O
			O O O
			O O I
			O I O
			I I O
			O I O
		}
	},
	{
		3, 20,
		{
			O I O
			I I O
			O I O
			O O I
			O O O
			O O O
			O O I
			O I O
			O I O
			O O I
			O O O
			O O O
			O O I
			O I O
			O I O
			O O I
			O O O
			O O O
			O O I
			O I O
		}
	}
};

#undef I
#undef O

const tuple<int, int> directions[4] = { {0,1}, {1,0}, {0, -1 }, {-1, 0} };

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

	vector<tile*> toplace;

	int size = lines[1].size();

	for (int l = 0; l < lines.size(); l++) {
		tile* t = new tile();

		int i = 5;
		int ID = GetInt(lines[l], i);
		t->ID = ID;

		l++;

		bool* k = t->data;
		for (int y = 0; y < size; y++, l++)
			for (int x = 0; x < size; x++)
				*(k++) = lines[l][x] == '#';

		for (int j = 0; j < size; j++) {
			t->u <<= 1;
			t->r <<= 1;
			t->d <<= 1;
			t->l <<= 1;
			t->uf <<= 1;
			t->rf <<= 1;
			t->df <<= 1;
			t->lf <<= 1;
			t->u |= t->data[j];
			t->uf |= t->data[size - 1 - j];
			t->l |= t->data[(size - 1 - j) * size];
			t->lf |= t->data[j * size];
			t->r |= t->data[size - 1 + j * size];
			t->rf |= t->data[size * size - 1 - j * size];
			t->d |= t->data[size * size - 1 - j];
			t->df |= t->data[size * size - size + j];
		}

		toplace.push_back(t);
	}

	vector<tile*> placed;
	map<tuple<int,int>, tile*> placegrid;

	placed.push_back(toplace[0]);
	placegrid[{ 0, 0 }] = toplace[0];
	EraseSwap(toplace, 0);

	while (toplace.size() > 0) {
		for (int j = 0; j < placed.size(); j++) {
			tile* tile1 = placed[j];
			for (int i = 0; i < toplace.size(); i++) {
				tile* tile2 = toplace[i];
				for (int side1 = 0; side1 < 4; side1++) {
					tuple<int, int> dst = { tile1->x, tile1->y };
					get<0>(dst) += get<0>(directions[side1]);
					get<1>(dst) += get<1>(directions[side1]);
					if (placegrid.count(dst) != 0) continue;
					short side1num = tile1->sidesf[side1];
					for (int side2 = 0; side2 < 4; side2++) {
						// Flip along matched - but flipped - edge
						if (tile2->sidesf[side2] == side1num) {
							for (int k = 0; k < 4; k++) {
								short t = tile2->sides[k];
								tile2->sides[k] = tile2->sidesf[k];
								tile2->sidesf[k] = t;
							}
							short t = tile2->sides[(side2 + 1) % 4];
							short tf = tile2->sidesf[(side2 + 1) % 4];
							tile2->sides[(side2 + 1) % 4] = tile2->sides[(side2 + 3) % 4];
							tile2->sidesf[(side2 + 1) % 4] = tile2->sidesf[(side2 + 3) % 4];
							tile2->sides[(side2 + 3) % 4] = t;
							tile2->sidesf[(side2 + 3) % 4] = tf;

							if (side2 == 0 || side2 == 2) {
								// Horizontal flip
								for (int y = 0; y < size; y++) {
									for (int x = 0; x < size / 2; x++) {
										bool t = tile2->data[y * size + x];
										tile2->data[y * size + x] = tile2->data[y * size + (size - 1 - x)];
										tile2->data[y * size + (size - 1 - x)] = t;
									}
								}
							}
							else {
								// Vertical flip
								for (int x = 0; x < size; x++) {
									for (int y = 0; y < size / 2; y++) {
										bool t = tile2->data[y * size + x];
										tile2->data[y * size + x] = tile2->data[(size - 1 - y) * size + x];
										tile2->data[(size - 1 - y) * size + x] = t;
									}
								}
							}
						}
						if (tile2->sides[side2] == side1num) {
							// Rotate tile to correct rotation - clockwise
							while (side1 != (side2 + 2) % 4) {
								side2++;
								short t = tile2->u;
								tile2->u = tile2->l;
								tile2->l = tile2->d;
								tile2->d = tile2->r;
								tile2->r = t;
								short tf = tile2->uf;
								tile2->uf = tile2->lf;
								tile2->lf = tile2->df;
								tile2->df = tile2->rf;
								tile2->rf = tf;

								// https://www.codespeedy.com/rotate-a-matrix-in-cpp/
								for (int y = 0; y < 5; y++)
								{
									for (int x = y; x < 9 - y; x++)
									{
										// Swapping elements after each iteration in Clockwise direction
										int temp = tile2->data[y * size + x];
										tile2->data[y * size + x] = tile2->data[(size - 1 - x) * size + y];
										tile2->data[(size - 1 - x) * size + y] = tile2->data[(size - y) * size - 1 - x];
										tile2->data[(size - y) * size - 1 - x] = tile2->data[x * size + size - 1 - y];
										tile2->data[x * size + size - 1 - y] = temp;
									}
								}
							}

							EraseSwap(toplace, i);
							placegrid[dst] = tile2;
							placed.push_back(tile2);
							tile2->x = get<0>(dst);
							tile2->y = get<1>(dst);
							side1 = 4;
							i--;
							break;
						}
					}
				}
			}
		}
	}

	tile* scanner = placed[0];
	int w = 1;
	int h = 1;
	while (placegrid.count({ scanner->x, scanner->y + 1 }) > 0) scanner = placegrid[{ scanner->x, scanner->y + 1 }];
	while (placegrid.count({ scanner->x - 1, scanner->y }) > 0) scanner = placegrid[{ scanner->x - 1, scanner->y }];
	int left = scanner->x;
	int top = scanner->y;
	long long product = scanner->ID;
	while (placegrid.count({ scanner->x + 1, scanner->y }) > 0) {
		scanner = placegrid[{ scanner->x + 1, scanner->y }];
		w++;
	}
	product *= scanner->ID;
	while (placegrid.count({ scanner->x, scanner->y - 1 }) > 0) {
		scanner = placegrid[{ scanner->x, scanner->y - 1 }];
		h++;
	}
	product *= scanner->ID;
	scanner = placegrid[{ left, top - h + 1 }];
	product *= scanner->ID;
	cout << product << endl;

	int size2 = size - 2;

	w *= size2;
	h *= size2;

	bool* image = new bool[w * h];

	for (int y = 0; y < h; y++) {
		int iy = (y % size2) + 1;
		for (int x = 0; x < w; x++) {
			tile* t = placegrid[{(x / size2) + left, top - (y / size2) }];
			int ix = (x % size2) + 1;
			bool b = t->data[iy * size + ix];
			image[y * w + x] = b;
		}
	}

	bool* dragonMask = new bool[w * h]{ false };

	long long dragonCount = 0;

	for (int d = 0; dragonCount == 0 && d < 8; d++) {
		const dragon& cd = dragons[d];

		for (int y = 0; y < h - cd.h; y++)
			for (int x = 0; x < w - cd.w; x++) {
				bool valid = true;
				int i = 0;
				for (int iy = 0; iy < cd.h; iy++)
					for (int ix = 0; ix < cd.w; ix++)
						if (cd.shape[i++] && !image[(y + iy) * w + (x + ix)]) {
							valid = false;
							break;
						}

				if (!valid) continue;
				i = 0;
				for (int iy = 0; iy < cd.h; iy++)
					for (int ix = 0; ix < cd.w; ix++)
						dragonMask[(y + iy) * w + (x + ix)] |= cd.shape[i++];

				dragonCount++;
			}
	}

	int roughCount = 0;
	for (int i = 0; i < w * h; i++)
		roughCount += image[i] && !dragonMask[i];

	cout << roughCount << endl;
}