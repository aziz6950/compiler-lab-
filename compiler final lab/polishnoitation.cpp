#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
using namespace std;


vector<string> split(const string& s) {
    vector<string> tokens;
    string temp;
    istringstream iss(s);
    while (iss >> temp) tokens.push_back(temp);
    return tokens;
}

// Convert postfix to prefix (Polish notation)
vector<string> postfixToPrefix(const vector<string>& postfix) {
    stack<vector<string>> st;

    for (auto token : postfix) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            vector<string> b = st.top(); st.pop();
            vector<string> a = st.top(); st.pop();
            vector<string> temp;
            temp.push_back(token);            
            temp.insert(temp.end(), a.begin(), a.end());
            temp.insert(temp.end(), b.begin(), b.end());
            st.push(temp);
        } 
        else if (token == "=") {              
            vector<string> rhs = st.top(); st.pop();
            vector<string> lhs = st.top(); st.pop();
            vector<string> temp;
            temp.push_back("=");             
            temp.insert(temp.end(), lhs.begin(), lhs.end());
            temp.insert(temp.end(), rhs.begin(), rhs.end());
            st.push(temp);
        }
        else { // operand
            st.push({token});
        }
    }

    return st.top();
}

// Print vector
void printVector(const vector<string>& v) {
    for (auto s : v) cout << s << " ";
    cout << endl;
}

int main() {
    cout << "Enter postfix expression (space-separated, with = at end for assignment):\n";
    cout << "Example: a b + c d - * x =\n";

    string line;
    getline(cin, line);
    vector<string> postfix = split(line);

    vector<string> prefix = postfixToPrefix(postfix);

    cout << "\nPrefix (Polish notation):\n";
    printVector(prefix);

    return 0;
}