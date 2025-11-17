#include <iostream>
#include <regex>
using namespace std;

int main() {
    string email;
    cout << "Enter email: ";
    cin >> email;

    // Simple email regex
    regex email_regex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{1,}$");

    if (regex_match(email, email_regex)) {
        cout << "Valid Email\n";
    } else {
        cout << "Invalid Email\n";
    }

    return 0;
}