#include<iostream>
using namespace std;

 bool evenOnes(const string &s){
    bool parity = true;
    for(char c:s) if (c == '1') parity = !parity;
    return parity;
 }
 int main(){
    string tests[] = {"1110", "10101", "1100111"};
    for(string s : tests)
    cout << s << " -->" << (evenOnes(s) ? "Accepted" : "Rejected")<< endl;

 }