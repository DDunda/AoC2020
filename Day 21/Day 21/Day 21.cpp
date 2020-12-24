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

	vector<string> dangerousIngredients;
	map<string, string> solvedAllergens;
	map<string, string> solvedIngredients;
	map<string, vector<string>> allergens;
	map<string, int> allAllergens;
	map<string, int> allIngredients;
	for (string l : lines) {
		vector<string> ingredients;
		int i = 0;
		string ingredient = GetToken(l, i);
		while (ingredient[0] != '(') {
			if (allIngredients.count(ingredient) == 0) allIngredients[ingredient] = 0;
			allIngredients[ingredient]++;
			ingredients.push_back(ingredient);
			ingredient = GetToken(l, i);
		} 

		string allergen;
		char suff;
		do {
			allergen = GetToken(l, i);
			suff = allergen[allergen.size() - 1];
			allergen.pop_back();

			if (allAllergens.count(allergen) == 0) allAllergens[allergen] = 0;
			allAllergens[allergen]++;

			if (allergens.count(allergen) == 0) {
				allergens[allergen] = ingredients;
			} else if (solvedAllergens.count(allergen) == 0) {
				for (int a = 0; a < allergens[allergen].size(); a++) {
					bool valid = false;
					for (int i = 0; i < ingredients.size(); i++) {
						if (ingredients[i] != allergens[allergen][a]) continue;
						valid = true;
						break;
					}
					if (valid) continue;
					EraseSwap(allergens[allergen], a);
					a--;
				}

				if (allergens[allergen].size() == 1) {
					solvedAllergens[allergen] = allergens[allergen][0];
					solvedIngredients[allergens[allergen][0]] = allergen;
					dangerousIngredients.push_back(allergens[allergen][0]);
				}
			}
		} while (suff != ')');
	}

	while (solvedAllergens.size() != allergens.size()) {
		for (auto& a : allergens) {
			if (solvedAllergens.count(a.first) == 0) {
				for (int ia = 0; ia < a.second.size(); ia++) {
					bool valid = true;
					for (auto ib : solvedAllergens) {
						if (a.second[ia] != ib.second) continue;
						valid = false;
						break;
					}
					if (valid) continue;

					EraseSwap(a.second, ia);
					ia--;
				}

				if (a.second.size() == 1) {
					solvedAllergens[a.first] = a.second[0];
					solvedIngredients[a.second[0]] = a.first;
					dangerousIngredients.push_back(a.second[0]);
				}
			}
		}
	}

	/*for (auto& a : solvedIngredients) {
		cout << a.first << " is a " << a.second << " allergen." << endl;
	}
	cout << endl;*/
	long long total = 0;
	for (auto& i : allIngredients) {
		if (solvedIngredients.count(i.first) != 0) continue;
		total += i.second;
		//cout << i.first << " is not an allergen (" << total << ")" << endl;
	}
	//cout << endl;
	cout << "Total non allergen ingredient appearances: " << total << endl;

	SortVector(dangerousIngredients);
	sort(dangerousIngredients.begin(), dangerousIngredients.end(), [&](string a, string b) {return (solvedIngredients[a]) < (solvedIngredients[b]); });

	cout << endl << "Dangerous ingredient list:" << endl;
	cout << dangerousIngredients[0];
	for (int i = 1; i < dangerousIngredients.size(); i++) cout << ',' << dangerousIngredients[i];
	cout << endl;
}