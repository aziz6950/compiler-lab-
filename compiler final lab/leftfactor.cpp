#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class LeftFactoring {
private:
    map<string, vector<string>> grammar;

    // Find longest common prefix among a vector of strings
    string commonPrefix(const vector<string>& prods) {
        if (prods.empty()) return "";
        string prefix = prods[0];
        for (size_t i = 1; i < prods.size(); i++) {
            size_t j = 0;
            while (j < prefix.size() && j < prods[i].size() && prefix[j] == prods[i][j])
                j++;
            prefix = prefix.substr(0, j);
        }
        return prefix;
    }

public:
    void inputGrammar() {
        int n;
        cout << "Enter number of productions: ";
        cin >> n;
        cin.ignore();

        cout << "Enter productions in format 'A->alpha|beta':\n";
        for (int i = 0; i < n; i++) {
            string line;
            getline(cin, line);
            size_t pos = line.find("->");
            if (pos == string::npos) continue;

            string nt = line.substr(0, pos);
            string rhs = line.substr(pos + 2);

            size_t start = 0;
            size_t bar;
            while ((bar = rhs.find('|', start)) != string::npos) {
                grammar[nt].push_back(rhs.substr(start, bar - start));
                start = bar + 1;
            }
            grammar[nt].push_back(rhs.substr(start));
        }
    }

    void performLeftFactoring() {
        map<string, vector<string>> newGrammar;
        bool changed = true;

        while (changed) {
            changed = false;
            map<string, vector<string>> tempGrammar = grammar;

            for (auto it = grammar.begin(); it != grammar.end(); ++it) {
                string nt = it->first;
                vector<string>& prods = it->second;

                string prefix = commonPrefix(prods);

                if (prefix.empty() || prods.size() == 1) {
                    newGrammar[nt] = prods;
                    continue;
                }

                changed = true;
                string newNt = nt + "'";

                vector<string> newProds; // for new non-terminal
                vector<string> remaining; // for original NT

                for (size_t i = 0; i < prods.size(); i++) {
                    string p = prods[i];
                    if (p.substr(0, prefix.size()) == prefix) {
                        string rem = p.substr(prefix.size());
                        if (rem.empty()) rem = "ε";
                        newProds.push_back(rem);
                    } else {
                        remaining.push_back(p);
                    }
                }

                remaining.push_back(prefix + newNt);

                newGrammar[nt] = remaining;
                newGrammar[newNt] = newProds;

                break; // only process one NT at a time in loop
            }

            grammar = newGrammar;
        }
    }

    void displayGrammar() {
        cout << "\nGrammar after left factoring:\n";
        for (auto it = grammar.begin(); it != grammar.end(); ++it) {
            string nt = it->first;
            vector<string>& prods = it->second;

            cout << nt << " -> ";
            for (size_t i = 0; i < prods.size(); i++) {
                cout << prods[i];
                if (i != prods.size() - 1) cout << " | ";
            }
            cout << endl;
        }
    }
};

int main() {
    LeftFactoring lf;

    cout << "=== Left Factoring of CFG ===\n";
    lf.inputGrammar();
    lf.performLeftFactoring();
    lf.displayGrammar();

    return 0;
}