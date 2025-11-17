#include <iostream>
using namespace std;

int main() {
    string s;
    cout << "Enter a binary string: ";
    if (!(cin >> s)) return 0;

   
    enum State { S0, S1, SACC };
    State cur = S0; 

    for (char ch : s) {
        if (ch != '0' && ch != '1') {
            cout << "Invalid input: only '0' and '1' allowed.\n";
            return 0;
        }

        
        if (cur == S0) {
            if (ch == '0') cur = S0;
            else cur = S1; 
        } else if (cur == S1) {
            if (ch == '0') cur = SACC;
            else cur = S1; 
        } else { 
            cur = SACC;
        }
    }

    if (cur == SACC) cout << "Accepted\n";
    else cout << "Rejected\n";

    return 0;
}