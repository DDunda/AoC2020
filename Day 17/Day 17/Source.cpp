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

#define InRange(k,m) ((k) >= 0 && (k) < m)

#define PART ONE
#if PART == ONE
	int boot = 6;

	// x
	int w = lines[0].size() + boot * 2;
	// y
	int d = lines.size() + boot * 2;
	// z
	int h = 1 + boot * 2;

	bool* space = new bool[w * d * h]{false};
	bool* space2 = new bool[w * d * h]{ false };

	int i = w * d * boot + w * boot + boot;
	int boxes = 0;
	for (int y = 0; y < lines.size(); y++) {
		for (int x = 0; x < lines[y].size(); x++) {
			boxes += space2[i] = space[i] = lines[y][x] == '#';
			i++;
		}
		i -= lines[y].size();
		i += w;
	}

	for (int b = 0; b < boot; b++) {
		i = 0;
		for (int z = 0; z < h; z++) {
			for (int y = 0; y < d; y++) {
				for (int x = 0; x < w; x++) {
					space2[i] = space[i];
					int neighbours = 0;
					for (int zo = -1; zo < 2; zo++)
						if(InRange(z + zo, h))
							for (int yo = -1; yo < 2; yo++)
								if (InRange(y + yo, d))
									for (int xo = -1; xo < 2; xo++)
										if (InRange(x + xo, w))
											if(xo != 0 || yo != 0 || zo != 0)
												if (space[i + xo + yo * w + zo * w * d])
													neighbours++;

					if (space[i]) {
						if (neighbours != 2 && neighbours != 3) {
							space2[i] = false;
							boxes--;
						}
					}
					else {
						if (neighbours == 3) {
							space2[i] = true;
							boxes++;
						}
					}
					i++;
				}
			}
		}
		bool* tmp = space;
		space = space2;
		space2 = tmp;
	}
	cout << boxes << endl;
#elif PART == TWO
	int boot = 6;

	// x
	int width = lines[0].size() + boot * 2;
	// y
	int depth = lines.size() + boot * 2;
	// z
	int height = 1 + boot * 2;
	// w
	int weight = 1 + boot * 2;

	int arraySize = width * depth * height * weight;

	bool* space = new bool[arraySize]{ false };
	bool* space2 = new bool[arraySize]{ false };

	//      w                               z                      y              x
	int i = height * width * depth * boot + width * depth * boot + width * boot + boot;
	int boxes = 0;
	for (int y = 0; y < lines.size(); y++) {
		for (int x = 0; x < lines[y].size(); x++) {
			boxes += space2[i] = space[i] = lines[y][x] == '#';
			i++;
		}
		i -= lines[y].size();
		i += width;
	}

	for (int b = 0; b < boot; b++) {
		i = 0;
		for (int w = 0; w < weight; w++) {
			for (int z = 0; z < height; z++) {
				for (int y = 0; y < depth; y++) {
					for (int x = 0; x < width; x++) {
						space2[i] = space[i];
						int neighbours = 0;
						for (int wo = -1; wo < 2; wo++)
							if (InRange(w + wo, weight))
								for (int zo = -1; zo < 2; zo++)
									if (InRange(z + zo, height))
										for (int yo = -1; yo < 2; yo++)
											if (InRange(y + yo, depth))
												for (int xo = -1; xo < 2; xo++)
													if (InRange(x + xo, width))
														if (xo != 0 || yo != 0 || zo != 0 || wo != 0)
															if (space[i + xo + yo * width + zo * width * depth + wo * width * depth * height])
																neighbours++;
																	// HOLY SHIT LOOK AT THIS NESTING
																	// 14 LAYERS
						if (space[i]) {
							if (neighbours != 2 && neighbours != 3) {
								space2[i] = false;
								boxes--;
							}
						}
						else {
							if (neighbours == 3) {
								space2[i] = true;
								boxes++;
							}
						}
						i++;
					}
				}
			}
		}
		bool* tmp = space;
		space = space2;
		space2 = tmp;
	}
	cout << boxes << endl;
#endif
}