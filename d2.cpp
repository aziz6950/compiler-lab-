#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <set>
using namespace std;

// Set of C/C++ keywords
set<string> keywords = {
    "int", "float", "double", "char", "void", "if", "else",
    "for", "while", "return", "switch", "case", "break", "continue",
    "do", "long", "short", "unsigned", "signed", "bool", "const"
};

// Function to check if a string is a valid identifier
bool isIdentifier(const string& s) {
    regex id("^[A-Za-z_][A-Za-z0-9_]*$");
    return regex_match(s, id);
}

int main() {
    cout << "Enter C/C++ code (Ctrl+D to end input on Linux/Mac, Ctrl+Z on Windows):\n";

    string line, word;
    int identifierCount = 0;

    while (getline(cin, line)) {
        // Remove punctuation except underscore
        for (char &c : line) {
            if (!isalnum(c) && c != '_') {
                c = ' ';
            }
        }

        stringstream ss(line);
        while (ss >> word) {
            if (isIdentifier(word) && keywords.find(word) == keywords.end()) {
                identifierCount++;
            }
        }
    }

    cout << "Total Identifiers: " << identifierCount << endl;

    return 0;
}