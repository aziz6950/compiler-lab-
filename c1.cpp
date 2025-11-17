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
            else { state = -1; break; }
        }
        else if(state == 1) {      
            if(c=='b' || c=='c')
                state = 1;
            else { state = -1; break; }
        }
    }

    if(state == 1)
        cout << "Accepted\n";
    else
        cout << "Rejected\n";
}