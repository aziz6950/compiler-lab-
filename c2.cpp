#include <iostream>
using namespace std;

int main() {
    string s;
    cout << "Enter string: ";
    cin >> s;

    int i = 0;
    int n = s.size();

    while(i < n) {
        if(i == n-1 && s[i] == 'a') {
            cout << "Accepted\n";
            return 0;
        }

        if(s[i] == 'b') {
            i++;
        }
        else if(s[i] == 'a' && i+1 < n && s[i+1]=='b') {
            i += 2;
        }
        else {
            cout << "Rejected\n";
            return 0;
        }
    }

    cout << "Rejected\n";
}