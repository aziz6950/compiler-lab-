#include <iostream>
#include <regex>
using namespace std;

int main() {
    string s;
    cout << "Enter an identifier: ";
    cin >> s;

    regex id_regex("^[A-Za-z_][A-Za-z0-9_]*$");

    if (regex_match(s, id_regex)) {
        cout << "Valid Identifier\n";
        
    } else {
        cout << "Invalid Identifier\n";
    }

    return 0;
}