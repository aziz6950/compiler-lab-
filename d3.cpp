#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << "Paste code (CTRL+D to finish):\n";

    string code = "", line;
    while (getline(cin, line)) {
        code += line + "\n";     // collect all input code
    }

    string result = "";
    bool inBlock = false;        // inside /* */ ?
    bool inLine = false;         // inside // ?

    for (size_t i = 0; i < code.size(); i++) {

        // check for start of block comment: /* */
        if (!inBlock && !inLine && code[i] == '/' && code[i+1] == '*') {
            inBlock = true;
            i++;                // skip '*'
            continue;
        }

        // check for end of block comment
        if (inBlock && code[i] == '*' && code[i+1] == '/') {
            inBlock = false;
            i++;                // skip '/'
            continue;
        }

        // check for single-line comment
        if (!inBlock && !inLine && code[i] == '/' && code[i+1] == '/') {
            inLine = true;
            i++;                // skip second '/'
            continue;
        }

        // end of single-line comment
        if (inLine && code[i] == '\n') {
            inLine = false;
            result += '\n';
            continue;
        }

        // if not inside any comment, keep character
        if (!inBlock && !inLine) {
            result += code[i];
        }
    }

    cout << "\n--- Cleaned Code ---\n";
    cout << result;

    return 0;
}