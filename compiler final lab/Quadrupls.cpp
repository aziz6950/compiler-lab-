#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

// Structure to store a quadruple
struct Quad {
    string op;
    string arg1;
    string arg2;
    string res;
};

// Global temporary variable counter
int tempCount = 1;

// Function to generate new temporary variable
string newTemp() {
    return "t" + to_string(tempCount++);
}

// Function to generate quadruples for simple expressions
vector<Quad> generateQuadruples(const vector<string>& postfix) {
    stack<string> st;
    vector<Quad> quads;

    for (auto token : postfix) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            string b = st.top(); st.pop();
            string a = st.top(); st.pop();
            string t = newTemp();
            quads.push_back({token, a, b, t});
            st.push(t);
        } else if (token == "=") {
            string val = st.top(); st.pop();
            string lhs = st.top(); st.top(); // assignment uses lhs on stack
            st.pop();
            quads.push_back({token, val, "-", lhs});
        } else {
            st.push(token);
        }
    }

    return quads;
}

// Simple helper to split expression into tokens (space-separated)
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

    vector<Quad> quads = generateQuadruples(postfix);

    cout << "\nGenerated Quadruples:\n";
    cout << "Op\tArg1\tArg2\tResult\n";
    cout << "-------------------------------\n";

    for (auto q : quads) {
        cout << q.op << "\t" << q.arg1 << "\t" << q.arg2 << "\t" << q.res << endl;
    }

    return 0;
}