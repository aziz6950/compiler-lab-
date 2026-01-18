#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>
using namespace std;

unordered_map<string, string> symbolTable;


bool isInt(const string& s) {
    if (s.empty()) return false;
    for (char c : s) if (!isdigit(c)) return false;
    return true;
}


bool isFloat(const string& s) {
    if (s.empty()) return false;
    bool dotSeen = false;
    for (char c : s) {
        if (c == '.') {
            if (dotSeen) return false;
            dotSeen = true;
        } else if (!isdigit(c)) return false;
    }
    return true;
}


bool isString(const string& s) {
    return s.size() >= 2 && s.front() == '"' && s.back() == '"';
}


bool typeCheck(const string& var, const string& val) {
    if (symbolTable.find(var) == symbolTable.end()) {
        cout << "Error: variable " << var << " not declared.\n";
        return false;
    }

    string varType = symbolTable[var];

    if (varType == "int") return isInt(val);
    if (varType == "float") return isFloat(val);
    if (varType == "string") return isString(val);

    return false;
}

int main() {
    cout << "Enter all declarations and assignments in one line (semicolon-separated):\n";
    cout << "Example:\n";
   

    string line;
    getline(cin, line);

    stringstream ss(line);
    string stmt;

    while (getline(ss, stmt, ';')) {
        if (stmt.empty()) continue;

        stringstream sstmt(stmt);
        string first, second, third;

        sstmt >> first;

        if (first == "int" || first == "float" || first == "string") {
            
            sstmt >> second;
            symbolTable[second] = first;
        } else {
            
            size_t eqPos = stmt.find('=');
            if (eqPos == string::npos) continue;

            string var = stmt.substr(0, eqPos);
            string val = stmt.substr(eqPos + 1);

          
            var.erase(remove(var.begin(), var.end(), ' '), var.end());
            val.erase(remove(val.begin(), val.end(), ' '), val.end());

            if (typeCheck(var, val)) {
                cout << "Assignment valid: " << var << " = " << val << endl;
            } else {
                cout << "Type error: cannot assign " << val << " to " << var << endl;
            }
        }
    }

    return 0;
}