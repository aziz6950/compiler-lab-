#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << "Paste code (CTRL+D to finish):\n";

    string code = "", line;
    while (getline(cin, line)) {
        code += line + "\n";     
    }

    string result = "";
    bool inBlock = false;       
    bool inLine = false;       

    for (size_t i = 0; i < code.size(); i++) {

       
        if (!inBlock && !inLine && code[i] == '/' && code[i+1] == '*') {
            inBlock = true;
            i++;                
            continue;
        }

        
        if (inBlock && code[i] == '*' && code[i+1] == '/') {
            inBlock = false;
            i++;                
            continue;
        }

       
        if (!inBlock && !inLine && code[i] == '/' && code[i+1] == '/') {
            inLine = true;
            i++;                
            continue;
        }

        
        if (inLine && code[i] == '\n') {
            inLine = false;
            result += '\n';
            continue;
        }

        
        if (!inBlock && !inLine) {
            result += code[i];
        }
    }

    cout << "\n--- Cleaned Code ---\n";
    cout << result;

    return 0;
}
