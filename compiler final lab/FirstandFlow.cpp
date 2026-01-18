#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>

using namespace std;

map<char, vector<string>> prod;
map<char, set<char>> FIRST, FOLLOW;
set<char> NT;
char startSymbol;

bool isNonTerminal(char c) {
    return c >= 'A' && c <= 'Z';
}

/* -------- FIRST -------- */
void findFIRST(char X) {
    if (!FIRST[X].empty()) return;

    for (string rhs : prod[X]) {
        for (int i = 0; i < rhs.size(); i++) {
            char Y = rhs[i];

            if (!isNonTerminal(Y)) {
                FIRST[X].insert(Y);
                break;
            }

            findFIRST(Y);
            bool hasEpsilon = false;

            for (char f : FIRST[Y]) {
                if (f == '#') hasEpsilon = true;
                else FIRST[X].insert(f);
            }

            if (!hasEpsilon) break;
            if (i == rhs.size() - 1)
                FIRST[X].insert('#');
        }
    }
}

/* -------- FOLLOW -------- */
void findFOLLOW(char X) {
    if (X == startSymbol)
        FOLLOW[X].insert('$');

    for (auto &p : prod) {
        char A = p.first;
        for (string rhs : p.second) {
            for (int i = 0; i < rhs.size(); i++) {
                if (rhs[i] == X) {
                    bool epsilonFound = true;

                    for (int j = i + 1; j < rhs.size(); j++) {
                        char B = rhs[j];
                        epsilonFound = false;

                        if (!isNonTerminal(B)) {
                            FOLLOW[X].insert(B);
                            break;
                        }

                        for (char f : FIRST[B]) {
                            if (f != '#')
                                FOLLOW[X].insert(f);
                        }

                        if (FIRST[B].count('#'))
                            epsilonFound = true;
                        else break;
                    }

                    if (epsilonFound && A != X) {
                        for (char f : FOLLOW[A])
                            FOLLOW[X].insert(f);
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;

    cout << "Enter productions (example: E->TR|# )\n";
    for (int i = 0; i < n; i++) {
        string line;
        cin >> line;

        char lhs = line[0];
        NT.insert(lhs);
        if (i == 0) startSymbol = lhs;

        string rhs = line.substr(3);
        string temp = "";

        for (char c : rhs) {
            if (c == '|') {
                prod[lhs].push_back(temp);
                temp = "";
            } else {
                temp += c;
            }
        }
        prod[lhs].push_back(temp);
    }

    for (char nt : NT)
        findFIRST(nt);

    for (int i = 0; i < 2; i++)
        for (char nt : NT)
            findFOLLOW(nt);

    cout << "\nFIRST Sets:\n";
    for (char nt : NT) {
        cout << "FIRST(" << nt << ") = { ";
        for (char c : FIRST[nt]) cout << c << " ";
        cout << "}\n";
    }

    cout << "\nFOLLOW Sets:\n";
    for (char nt : NT) {
        cout << "FOLLOW(" << nt << ") = { ";
        for (char c : FOLLOW[nt]) cout << c << " ";
        cout << "}\n";
    }

    return 0;
}