#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Grammar {
    map<string, vector<vector<string>>> prod;

public:
    void addProduction(const string& lhs, const vector<string>& rhs) {
        prod[lhs].push_back(rhs);
    }

    void eliminateLeftRecursion() {
        map<string, vector<vector<string>>> newProd;

        for (auto &p : prod) {
            string A = p.first;
            vector<vector<string>> alpha, beta;

            for (auto &rhs : p.second) {
                if (!rhs.empty() && rhs[0] == A) {
                    alpha.push_back(
                        vector<string>(rhs.begin() + 1, rhs.end())
                    );
                } else {
                    beta.push_back(rhs);
                }
            }

            if (!alpha.empty()) {
                string Aprime = A + "'";

                for (auto &b : beta) {
                    b.push_back(Aprime);
                    newProd[A].push_back(b);
                }

                for (auto &a : alpha) {
                    a.push_back(Aprime);
                    newProd[Aprime].push_back(a);
                }

                newProd[Aprime].push_back({"epsilon"});
            } else {
                newProd[A] = p.second;
            }
        }

        prod = newProd;
    }

    void printGrammar() {
        cout << "\nGrammar after eliminating left recursion:\n";
        for (auto &p : prod) {
            cout << p.first << " -> ";
            for (int i = 0; i < p.second.size(); i++) {
                for (auto &s : p.second[i])
                    cout << s << " ";
                if (i + 1 < p.second.size()) cout << "| ";
            }
            cout << endl;
        }
    }
};

int main() {
    Grammar g;

    cout << "Enter grammar (one production per line)\n";
    
    cout << "Press ENTER on empty line to finish\n\n";

    string line;
    while (true) {
        getline(cin, line);
        if (line.empty()) break;

        stringstream ss(line);
        string lhs, arrow, tok;
        ss >> lhs >> arrow;

        vector<string> rhs;
        while (ss >> tok) {
            if (tok == "|") {
                g.addProduction(lhs, rhs);
                rhs.clear();
            } else {
                rhs.push_back(tok);
            }
        }
        if (!rhs.empty())
            g.addProduction(lhs, rhs);
    }

    g.eliminateLeftRecursion();
    g.printGrammar();

    return 0;
}
