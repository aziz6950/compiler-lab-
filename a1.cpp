#include <iostream>
using namespace std;

int main() {
    string s;
    cout << "Enter binary string: ";
    cin >> s;

    int state = 0; 

    for (char c : s) {
        switch (state) {
            case 0: 
                if (c == '0') state = 1;
                else state = 0;
                break;

            case 1: 
                if (c == '0') state = 1;
                else state = 2;
                break;

            case 2: 
                if (c == '0') state = 1;
                else state = 0;
                break;
        }
    }

    if (state == 2)
        cout << "Accepted (string ends with 01)" << endl;
    else
        cout << "Rejected (string does NOT end with 01)" << endl;

    return 0;
}