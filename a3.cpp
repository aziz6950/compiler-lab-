#include <iostream>
#include <string>
using namespace std;

enum State { S0, S1, S2 }; 

bool isAccepted(const string &s) {
    State cur = S0;

    for (char ch : s) {
        if (cur == S0) {
            if (ch == 'a') cur = S0;
            else if (ch == 'b') cur = S1;
            else return false; 
        } 
        else if (cur == S1) {
            if (ch == 'a') cur = S0;
            else if (ch == 'b') cur = S2; 
            else return false;
        } 
        else if (cur == S2) {
            return false; 
        }
    }

    return cur != S2; 
}

int main() {
    string input;
    cout << "Enter a string over {a, b}: ";
    cin >> input;

    if (isAccepted(input))
        cout << "String accepted by the DFA.\n";
    else
        cout << "String rejected by the DFA.\n";

    return 0;
}