#include "../../Utilities.h"

#define ONE 1
#define TWO 2

using namespace std;

int RecursiveCombat(deque<int>& deck1, deque<int>& deck2) {
	map<tuple<unsigned long long, unsigned long long>, int> gameStates;
	int round = 0;
	while (deck1.size() > 0 && deck2.size() > 0) {
		round++;

		unsigned long long score1 = 0;
		for (int i = 0; i < deck1.size(); i++) {
			score1 *= 50;
			score1 += deck1[i];
		}
		unsigned long long score2 = 0;
		for (int i = 0; i < deck2.size(); i++) {
			score2 *= 50;
			score2 += deck2[i];
		}

		if (gameStates.count({ score1,score2 }) != 0)
			return 1;

		gameStates[{ score1, score2 }] = 1;

		int roundWinner;

		int play1 = deck1.front();
		int play2 = deck2.front();

		deck1.pop_front();
		deck2.pop_front();

		if (deck1.size() >= play1 && deck2.size() >= play2) {
			deque<int> subDeck1;
			deque<int> subDeck2;
			for (int i = 0; i < play1; i++) subDeck1.push_back(deck1[i]);
			for (int i = 0; i < play2; i++) subDeck2.push_back(deck2[i]);

			roundWinner = RecursiveCombat(subDeck1, subDeck2);
		}
		else
			roundWinner = play1 > play2 ? 1 : 2;

		if (roundWinner == 1) {
			deck1.push_back(play1);
			deck1.push_back(play2);
		}
		else {
			deck2.push_back(play2);
			deck2.push_back(play1);
		}
	}
	return deck2.size() == 0 ? 1 : 2;
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

//#define PRINT_DEBUG

#define PART TWO
#if PART == ONE
	deque<int> player1deck;
	deque<int> player2deck;
	int l = 1;
	for (; lines[l] != ""; l++) {
		player1deck.push_back(stoi(lines[l]));
	}
	l += 2;
	for (; l < lines.size(); l++) {
		player2deck.push_back(stoi(lines[l]));
	}
	int round = 0;
	while (player1deck.size() > 0 && player2deck.size() > 0) {
		round++;
		int player1play = player1deck.front();
		int player2play = player2deck.front();

#ifdef PRINT_DEBUG
		cout << "-- Round " << round << " --" << endl;
		cout << "Player 1's deck: " << player1deck.front();
		for (int i = 1; i < player1deck.size(); i++) cout << ", " << player1deck[i];
		cout << endl;
		cout << "Player 2's deck: " << player2deck.front();
		for (int i = 1; i < player2deck.size(); i++) cout << ", " << player2deck[i];
		cout << endl;
		cout << "Player 1 plays: " << player1play << endl;
		cout << "Player 2 plays: " << player2play << endl;
#endif // PRINT_DEBUG

		player1deck.pop_front();
		player2deck.pop_front();
		if (player1play > player2play) {
#ifdef PRINT_DEBUG
			cout << "Player 1 wins the round!" << endl;
#endif // PRINT_DEBUG
			player1deck.push_back(player1play);
			player1deck.push_back(player2play);
		}
		else {
#ifdef PRINT_DEBUG
			cout << "Player 2 wins the round!" << endl;
#endif // PRINT_DEBUG
			player2deck.push_back(player2play);
			player2deck.push_back(player1play);
		}
#ifdef PRINT_DEBUG
		cout << endl;
#endif // PRINT_DEBUG
	}
#ifdef PRINT_DEBUG
	cout << endl;
#endif // PRINT_DEBUG
	cout << "== Post-game results ==" << endl;
	cout << "Player 1's deck: ";
	if (player1deck.size() > 0) {
		cout << player1deck.front();
		for (int i = 1; i < player1deck.size(); i++) cout << ", " << player1deck[i];
	}
	cout << endl;
	cout << "Player 2's deck: ";
	if (player2deck.size() > 0) {
		cout << player2deck.front();
		for (int i = 1; i < player2deck.size(); i++) cout << ", " << player2deck[i];
	}
	cout << endl;

	deque<int>& winnersDeck = player1deck.size() == 0 ? player2deck : player1deck;
	long long score = 0;
	for (int i = 0; i < winnersDeck.size(); i++) {
		score += winnersDeck[i] * (winnersDeck.size() - i);
	}
	cout << "Winner's score: " << score << endl;
#elif PART == TWO
	deque<int> player1deck;
	deque<int> player2deck;
	int l = 1;
	for (; lines[l] != ""; l++) {
		player1deck.push_back(stoi(lines[l]));
	}
	l += 2;
	for (; l < lines.size(); l++) {
		player2deck.push_back(stoi(lines[l]));
	}

	int winner = RecursiveCombat(player1deck, player2deck);

	cout << "== Post-game results ==" << endl;
	cout << "Player 1's deck: ";
	if (player1deck.size() > 0) {
		cout << player1deck.front();
		for (int i = 1; i < player1deck.size(); i++) cout << ", " << player1deck[i];
	}
	cout << endl;
	cout << "Player 2's deck: ";
	if (player2deck.size() > 0) {
		cout << player2deck.front();
		for (int i = 1; i < player2deck.size(); i++) cout << ", " << player2deck[i];
	}
	cout << endl;

	deque<int>& winnersDeck = winner == 1 ? player1deck : player2deck;
	long long score = 0;
	for (int i = 0; i < winnersDeck.size(); i++) {
		score += winnersDeck[i] * (winnersDeck.size() - i);
	}
	cout << "Winner's score: " << score << endl;
#endif
}