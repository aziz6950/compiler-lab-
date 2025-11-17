#include <iostream>
#include <regex>
#include <sstream>
using namespace std;

bool isKeyword(const string& s) {
    return (s == "int" || s == "float" || s == "if" || s == "else");
}

bool isIdentifier(const string& s) {
    regex id("^[A-Za-z_][A-Za-z0-9_]*$");
    return regex_match(s, id);
}

bool isNumber(const string& s) {
    regex num("^[0-9]+$");
    return regex_match(s, num);
}

bool isOperator(const string& s) {
    return (s == "+" || s == "-" || s == "*" || s == "/" || s == "=");
}

int main() {
    string input;
    cout << "Enter code: ";
    getline(cin, input);

    stringstream ss(input);
    string token;

    while (ss >> token) {
        if (isKeyword(token))
            cout << token << " -> KEYWORD\n";
        else if (isOperator(token))
            cout << token << " -> OPERATOR\n";
        else if (isNumber(token))
            cout << token << " -> NUMBER\n";
        else if (isIdentifier(token))
            cout << token << " -> IDENTIFIER\n";
        else
            cout << token << " -> UNKNOWN\n";
    }

    return 0;
}