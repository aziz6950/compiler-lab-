#include <iostream>
using namespace std;

int main() {
    string s;
    cout << "Enter string: ";
    cin >> s;

    int state = 0;   

    for(char c : s) {

        if(state == 0) {
            if(c == 'a') state = 1;
            else if(c == 'b') state = 2;
            else { state = -1; break; }
        }

        else if(state == 1) {   
            if(c == 'a') state = 1;
            else { state = -1; break; }
        }

        else if(state == 2) {   
            if(c=='a' || c=='b') state = 3;
            else { state = -1; break; }
        }

        else if(state == 3) {   
            state = -1; break;  
        }
    }

    if(state == 0 || state == 1 || state == 3)
        cout << "Accepted\n";
    else
        cout << "Rejected\n";
}