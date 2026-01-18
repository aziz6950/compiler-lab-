#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

// Structure for triple
struct Triple {
    string op;
    string arg1;
    string arg2;
};

// Function to generate triples for postfix expression
vector<Triple> generateTriples(const vector<string>& postfix) {
    stack<string> st;
    vector<Triple> triples;

    for (auto token : postfix) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            string b = st.top(); st.pop();
            string a = st.top(); st.pop();
            triples.push_back({token, a, b});
            st.push("#" + to_string(triples.size() - 1)); // push index reference
        } else if (token == "=") {
            string val = st.top(); st.pop();
            string lhs = st.top(); st.pop();
            triples.push_back({token, val, lhs});
        } else {
            st.push(token);
        }
    }

    return triples;
}

// Helper to split string by space
vector<string> split(const string& s) {
    vector<string> res;
    string tok = "";
    for (char c : s) {
        if (c == ' ') {
            if (!tok.empty()) {
                res.push_back(tok);
                tok = "";
            }
        } else {
            tok += c;
        }
    }
    if (!tok.empty()) res.push_back(tok);
    return res;
}

int main() {
    cout << "Enter postfix expression (space-separated, with = at end for assignment):\n";
    cout << "Example: ";

    string line;
    getline(cin, line);

    vector<string> postfix = split(line);
    vector<Triple> triples = generateTriples(postfix);

    cout << "\nGenerated Triples:\n";
    cout << "Index\tOp\tArg1\tArg2\n";
    cout << "-------------------------------\n";

    for (size_t i = 0; i < triples.size(); i++) {
        cout << i << "\t" << triples[i].op << "\t" << triples[i].arg1
             << "\t" << triples[i].arg2 << endl;
    }

    return 0;
}