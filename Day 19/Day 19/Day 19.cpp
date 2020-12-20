#include "../../Utilities.h"

#define ONE 1
#define TWO 2

using namespace std;

class Matcher {
public:
	vector<string> startTokens;
	vector<string> endTokens;
	Matcher(vector<string>& matches1, vector<string>& matches2) : startTokens(matches1), endTokens(matches2) {};
	bool CheckMatch(string l) {
		int checkpoint = 0;
		int i = 0;
		int x = 0, y = 0;
		while (i < l.size()) {
			bool valid = false;
			for (string token : startTokens) {
				int t = 0;
				for (; t < token.size() && i < l.size(); t++, i++) {
					if (token[t] != l[i]) break;
				}
				if (t == token.size()) {
					checkpoint = i;
					x++;
					valid = true;
					break;
				}
				else i = checkpoint;
			}
			if (!valid) break;
		}
		while (i < l.size()) {
			bool valid = false;
			for (string token : endTokens) {
				int t = 0;
				for (; t < token.size() && i < l.size(); t++, i++) {
					if (token[t] != l[i]) break;
				}
				if (t == token.size()) {
					checkpoint = i;
					y++;
					valid = true;
					break;
				}
				else i = checkpoint;
			}
			if (!valid) break;
		}
		return i == l.size() && x > 1 && y > 0 && y < x;
	}
};

struct rule {
	string rule;
	vector<string> compiledRules;
};

vector<string> MakeTokens(map<int, rule>& matches, int rule) {
	if (matches.count(rule) == 0)
		return {};

	if (matches[rule].compiledRules.size() != 0)
		return matches[rule].compiledRules;

	string match = matches[rule].rule;
	if (match == "\"a\"") {
		matches[rule].compiledRules = { "a" };
		return { "a" };
	}
	if (match == "\"b\"") {
		matches[rule].compiledRules = { "b" };
		return { "b" };
	}

	vector<string> rules;
	int i = 0;
	vector<string> subrules = MakeTokens(matches, stoi(GetToken(match, i)));
	while (i < match.size()) {
		string token = GetToken(match, i);
		if (token == "|") {
			AppendVector(rules, subrules);
			subrules = MakeTokens(matches, stoi(GetToken(match, i)));
		}
		else {
			vector<string> as;
			vector<string> bs = MakeTokens(matches, stoi(token));
			for (string a : subrules) {;
				for (string b : bs) {
					as.push_back(a + b);
				}
			}
			subrules = as;
		}
	}
	AppendVector(rules, subrules);

	matches[rule].compiledRules = rules;

	return rules;
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

	map<int, rule> matches;
	int l = 0;
	while (l < lines.size() && lines[l] != "") {
		int i = 0;
		int number = GetInt(lines[l], i);
		i += 2;
		string match = GetToEnd(lines[l], i);
		matches[number] = { match };
		l++;
	}
	l++;
	vector<string> cantidates;
	while (l < lines.size()) {
		cantidates.push_back(lines[l]);
		l++;
	}

#define PART TWO
#if PART == ONE
	vector<string> tokens = MakeTokens(matches, 0);

	long long total = 0;
	for (string cantidate : cantidates) {
		for (string token : tokens) {
			if (cantidate != token) continue;
			total++;
			break;
		}
	}
	cout << total;
#elif PART == TWO
	vector<string> tokens1 = MakeTokens(matches, 42);
	vector<string> tokens2 = MakeTokens(matches, 31);
	Matcher matcher(tokens1, tokens2);

	long long total = 0;
	for (string cantidate : cantidates)
		if(matcher.CheckMatch(cantidate))
			total++;

	cout << total;
#endif
}