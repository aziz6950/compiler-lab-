#include <iostream>
#include <regex>
using namespace std;

int main() {
    string s;
    cout << "Enter integer constant: ";
    cin >> s;

   
    regex int_regex("^-?[0-9]+$");

    if (regex_match(s, int_regex)) {
        cout << "Valid Integer Constant\n";
    } else {
        cout << "Invalid Integer Constant\n";
    }

    return 0;
}
