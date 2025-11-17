#include <iostream>
using namespace std;

string moveState(string s, char c){
    if (s == "q0q1") {
        return (c=='a') ? "q1" : "q2";
    }
    if (s == "q1") {
        return (c=='a') ? "q1" : "q2";
    }
    if (s == "q2") {
        return "";
    }
    return "";
}

bool isAccept(string s){
    return (s == "q2");
}

int main(){
    string in;
    cout << "Enter string (a,b): ";
    cin >> in;

    string state = "q0q1"; // start

    for(char c : in){
        state = moveState(state, c);
    }

    if(isAccept(state))
        cout << "Accepted\n";
    else
        cout << "Rejected\n";
}