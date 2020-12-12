#include "../../Utilities.h"

#define ONE 1
#define TWO 2

using namespace std;

#define FLOOR 0
#define EMPTY 1
#define FULL 2

#define SANE_CODE
// Sell your soul
//#undef SANE_CODE

void main()
{
	auto p1 = chrono::steady_clock::now();

	string line;
	ifstream input;
	input.open("input.txt");

	string seats;
	getline(input, seats);

	int w = seats.size();
	int h = 1;

	while (getline(input, line)) {
		seats += line;
		h++;
	}
	input.close();

	int i, occupied;
	bool changed;

	int cells = w * h;
	int* c1 = new int[cells] {0};
	int* c2 = new int[cells] {0};

	for (i = 0; i < cells; i++) {
		c1[i] = c2[i] = seats[i] == 'L';
	}
	
	occupied = 0;
	do {
		changed = false;
		i = 0;
		for (int y = 0; y < h; y++) {
#ifndef SANE_CODE
			bool u = y + 1 < h;
			bool d = y - 1 >= 0;
#endif
			for (int x = 0; x < w; x++) {
				int t = c1[i];
				if (t != FLOOR) {
					int count = 0;
#ifdef SANE_CODE
					for (int yo = -1; yo < 2; yo++) {
						for (int xo = -1; xo < 2; xo++) {
							if ((xo == 0 && yo == 0) || x + xo < 0 || y + yo < 0 || x + xo >= w || y + yo >= h) continue;
							count += c1[i + yo * w + xo] == FULL;
						}
					}
#else // INSANE_CODE
					if (u) { // Trust me, this is stupid fast
						if (x - 1 >= 0) count += c1[i + w - 1] == FULL;
						count += c1[i + w] == FULL;
						if (x + 1 < w) count += c1[i + w + 1] == FULL;
					}
					if (x - 1 >= 0) count += c1[i - 1] == FULL;
					if (x + 1 < w) count += c1[i + 1] == FULL;
					if (d) {
						if (x - 1 >= 0) count += c1[i - w - 1] == FULL;
						count += c1[i - w] == FULL;
						if (x + 1 < w) count += c1[i - w + 1] == FULL;
					}
#endif // INSANE_CODE

					if (count == 0 && t == EMPTY) {
						c2[i] = FULL;
						changed = true;
						occupied++;
					}
					else if (count >= 4 && t == FULL) {
						c2[i] = EMPTY;
						changed = true;
						occupied--;
					}
				}
				i++;
			}
		}
		for (i = 0; i < cells; i++)
			c1[i] = c2[i];

	} while (changed);
	cout << "Part One" << endl;
	cout << occupied << endl;

	auto p2 = chrono::steady_clock::now();

	for (i = 0; i < cells; i++)
		c1[i] = c2[i] = c1[i] != FLOOR;

	occupied = 0;
	do {
		changed = false;
		i = 0;

#define RAY(j, c) while (c) { j; if (c1[io] == FLOOR) continue;	count += c1[io] == FULL; break; }

		for (int y = 0; y < h; y++) {
#ifndef SANE_CODE
			bool u = y + 1 < h;
			bool d = y - 1 >= 0;
#endif // INSANE_CODE
			for (int x = 0; x < w; x++) {
				int t = c1[i];
				if (t != FLOOR) {
					int count = 0;
#ifdef SANE_CODE
					for (int yo = -1; yo < 2; yo++) {
						for (int xo = -1; xo < 2; xo++) {
							if ((xo == 0 && yo == 0) || x + xo < 0 || y + yo < 0 || x + xo >= w || y + yo >= h) continue;
							int xt = x + xo;
							int yt = y + yo;
							int o = xo + yo * w;
							int io = i;
							while (xt < w && yt < h && xt >= 0 && yt >= 0) {
								io += o;
								xt += xo;
								yt += yo;
								if (c1[io] == FLOOR) continue;
								count += c1[io] == FULL;
								break;
							}
						}
					}
#else // INSANE_CODE
					int xt, yt, io; // This is also stupid fast

					bool l = x - 1 >= 0;
					bool r = x + 1 < w;

					if (d) {
						if (l) {
							xt = x - 1;
							yt = y - 1;
							io = i;
							RAY(io += -1 - w; --xt; --yt, xt >= 0 && yt >= 0);

							if (r) {
								xt = x + 1;
								yt = y - 1;
								io = i;
								RAY(io += 1 - w; ++xt; --yt, xt < w&& yt >= 0);
							}
						}
						else {
							xt = x + 1;
							yt = y - 1;
							io = i;
							RAY(io += 1 - w; ++xt; --yt, xt < w&& yt >= 0);
						}

						yt = y - 1;
						io = i;
						RAY(io += -w; --yt, yt >= 0);

						if (u) {
							if (l) {
								xt = x - 1;
								yt = y + 1;
								io = i;
								RAY(io += -1 + w; --xt; ++yt, xt >= 0 && yt < h);

								if (r) {
									xt = x + 1;
									yt = y + 1;
									io = i;
									RAY(io += 1 + w; ++xt; ++yt, xt < w&& yt < h);
								}
							}
							else {
								xt = x + 1;
								yt = y + 1;
								io = i;
								RAY(io += 1 + w; ++xt; ++yt, xt < w&& yt < h);
							}

							yt = y + 1;
							io = i;
							RAY(io += w; ++yt, yt < h);
						}
					}
					else {
						if (l) {
							xt = x - 1;
							yt = y + 1;
							io = i;
							RAY(io += -1 + w; --xt; ++yt, xt >= 0 && yt < h);

							if (r) {
								xt = x + 1;
								yt = y + 1;
								io = i;
								RAY(io += 1 + w; ++xt; ++yt, xt < w&& yt < h);
							}
						}
						else {
							xt = x + 1;
							yt = y + 1;
							io = i;
							RAY(io += 1 + w; ++xt; ++yt, xt < w&& yt < h);
						}

						yt = y + 1;
						io = i;
						RAY(io += w; ++yt, yt < h);
					}

					if (l) {
						xt = x - 1;
						io = i;
						RAY(--io; --xt, xt >= 0);

						if (r) {
							xt = x + 1;
							io = i;
							RAY(++io; ++xt, xt < w);
						}
					}
					else {
						xt = x + 1;
						io = i;
						RAY(++io; ++xt, xt < w);
					}
#endif // INSANE_CODE
					
					if (count == 0 && c1[i] == EMPTY) {
						c2[i] = FULL;
						changed = true;
						occupied++;
					} else if (count >= 5 && c1[i] == FULL) {
						c2[i] = EMPTY;
						changed = true;
						occupied--;
					}
				}
				i++;
			}
		}

		for (i = 0; i < cells; i++) 
			c1[i] = c2[i];

	} while (changed);
	cout << "Part Two" << endl;
	cout << occupied << endl;

	delete[] c1;
	delete[] c2;

	auto p3 = chrono::steady_clock::now();

	cout << "Part one: " << chrono::duration_cast<chrono::nanoseconds>(p2 - p1).count() / 1000000.0 << "ms" << endl;
	cout << "Part two: " << chrono::duration_cast<chrono::nanoseconds>(p3 - p2).count() / 1000000.0 << "ms" << endl;
}