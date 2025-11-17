#include <iostream>
using namespace std;

int nextState(int s, char c) {
    switch (s) {
        case 0: return (c=='a') ? 1 : 0;
        case 1: return (c=='a') ? 1 : 2;
        case 2: return (c=='a') ? 1 : 3;
        case 3: return (c=='a') ? 1 : 0;
    }
    return 0;
}

int main() {
    string s;
    cout << "Enter string: ";
    cin >> s;

    int state = 0;
    for (char c : s) {
        state = nextState(state, c);
    }

    if (state == 3)
        cout << "Accepted\n";
    else
        cout << "Rejected\n";
}