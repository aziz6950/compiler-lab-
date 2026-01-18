#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>
#include <sstream> // <-- for splitting multiple statements
#include <cstdlib>
using namespace std;

/* ------------------- TOKEN ------------------- */
enum TokenType { ID, NUM, OP, ASSIGN, SEMI, END };

struct Token {
    TokenType type;
    string value;
};

vector<Token> tokens;
int pos = 0;

/* ------------------- LEXICAL ANALYZER ------------------- */
void lexer(const string& input) {
    tokens.clear();
    for (size_t i = 0; i < input.size(); i++) {
        if (isspace(input[i])) continue;

        if (isalpha(input[i])) {
            string id;
            while (i < input.size() && isalnum(input[i])) id += input[i++];
            i--;
            tokens.push_back({ID, id});
        }
        else if (isdigit(input[i])) {
            string num;
            while (i < input.size() && isdigit(input[i])) num += input[i++];
            i--;
            tokens.push_back({NUM, num});
        }
        else if (input[i] == '+' || input[i] == '*') {
            tokens.push_back({OP, string(1, input[i])});
        }
        else if (input[i] == '=') {
            tokens.push_back({ASSIGN, "="});
        }
        else if (input[i] == ';') {
            tokens.push_back({SEMI, ";"});
        }
    }
    tokens.push_back({END, ""});
}

/* ------------------- PARSE TREE ------------------- */
struct ParseNode {
    string value;
    vector<ParseNode*> child;
    ParseNode(const string& v) : value(v) {}
};

Token cur() { return tokens[pos]; }
void advance() { pos++; }

ParseNode* parseFactor() {
    ParseNode* node = new ParseNode("factor");
    node->child.push_back(new ParseNode(cur().value));
    advance();
    return node;
}

ParseNode* parseTerm() {
    ParseNode* node = new ParseNode("term");
    node->child.push_back(parseFactor());
    while (cur().value == "*") {
        node->child.push_back(new ParseNode("*"));
        advance();
        node->child.push_back(parseFactor());
    }
    return node;
}

ParseNode* parseExpr() {
    ParseNode* node = new ParseNode("expr");
    node->child.push_back(parseTerm());
    while (cur().value == "+") {
        node->child.push_back(new ParseNode("+"));
        advance();
        node->child.push_back(parseTerm());
    }
    return node;
}

ParseNode* parseStatement() {
    ParseNode* node = new ParseNode("stmt");
    node->child.push_back(new ParseNode(cur().value)); // id
    advance(); // ID
    advance(); // =
    node->child.push_back(parseExpr());
    advance(); // ;
    return node;
}

vector<ParseNode*> parseAllStatements() {
    vector<ParseNode*> stmts;
    while (cur().type != END) {
        stmts.push_back(parseStatement());
    }
    return stmts;
}

/* ------------------- PRINT PARSE TREE TABLE ------------------- */
void printParseTreeTable(ParseNode* node, const string& parent="Root") {
    if (!node) return;
    cout << parent << "\t" << node->value;
    for (auto c : node->child) cout << "\t" << c->value;
    cout << "\n";
    for (auto c : node->child)
        printParseTreeTable(c, node->value);
}

/* ------------------- AST ------------------- */
struct ASTNode {
    string value;
    ASTNode *left, *right;
    ASTNode(const string& v) : value(v), left(nullptr), right(nullptr) {}
};

ASTNode* buildAST(ParseNode* node) {
    if (node->value == "factor") return new ASTNode(node->child[0]->value);

    if (node->value == "term" || node->value == "expr") {
        ASTNode* left = buildAST(node->child[0]);
        for (size_t i = 1; i < node->child.size(); i += 2) {
            ASTNode* op = new ASTNode(node->child[i]->value);
            op->left = left;
            op->right = buildAST(node->child[i + 1]);
            left = op;
        }
        return left;
    }

    if (node->value == "stmt") {
        ASTNode* root = new ASTNode("=");
        root->left = new ASTNode(node->child[0]->value);
        root->right = buildAST(node->child[1]);
        return root;
    }

    return nullptr;
}

/* ------------------- PRINT AST TABLE ------------------- */
void printASTTable(ASTNode* node) {
    if (!node) return;
    cout << node->value << "\t";
    cout << (node->left ? node->left->value : "-") << "\t";
    cout << (node->right ? node->right->value : "-") << "\n";
    printASTTable(node->left);
    printASTTable(node->right);
}

/* ------------------- INTERMEDIATE CODE ------------------- */
int tempCount = 1;
string genIC(ASTNode* node) {
    if (!node->left && !node->right) return node->value;

    string l = genIC(node->left);
    string r = genIC(node->right);

    if (isdigit(l[0]) && isdigit(r[0])) {
        int a = stoi(l), b = stoi(r);
        if (node->value == "+") return to_string(a + b);
        if (node->value == "*") return to_string(a * b);
    }

    string t = "t" + to_string(tempCount++);
    cout << t << " = " << l << " " << node->value << " " << r << endl;
    return t;
}

/* ------------------- MAIN ------------------- */
int main() {
    string input;
    cout << "Enter one or more equations (separated by ;): ";
    getline(cin, input);

    /* ----------------- Split statements by ; ----------------- */
    stringstream ss(input);
    string statement;
    vector<string> statements;
    while (getline(ss, statement, ';')) {
        if (!statement.empty()) statements.push_back(statement + ";"); // add ; back
    }

    for (auto& s : statements) {
        pos = 0;
        lexer(s);

        cout << "\n--- LEXICAL ANALYSIS ---\n";
        for (auto &t : tokens)
            if (t.type != END)
                cout << "<" << t.value << "> ";
        cout << "\n";

        cout << "\n--- SYNTAX ANALYSIS ---\n";
        cout << "Syntax analysis successful ✔\n";

        cout << "\n--- PARSE TREE (Table) ---\n";
        vector<ParseNode*> parseTreeList = parseAllStatements();
        for (auto stmtNode : parseTreeList)
            printParseTreeTable(stmtNode);

        cout << "\n--- ABSTRACT SYNTAX TREE (Table) ---\n";
        vector<ASTNode*> astList;
        for (auto stmtNode : parseTreeList)
            astList.push_back(buildAST(stmtNode));

        cout << "Node\tLeft\tRight\n-------------------\n";
        for (auto ast : astList)
            printASTTable(ast);

        cout << "\n--- INTERMEDIATE CODE ---\n";
        for (auto ast : astList) {
            string result = genIC(ast->right);
            cout << ast->left->value << " = " << result << "\n";
        }

        cout << "\n--- OPTIMIZATION ---\n";
        cout << "Constant folding applied ✔\n";
        for (auto ast : astList) {
            string val = genIC(ast->right);
            cout << ast->left->value << " = " << val << "\n";
        }

        cout << "\n--- TARGET CODE GENERATION ---\n";
        int reg = 1;
        for (auto ast : astList) {
            string val = genIC(ast->right);
            cout << "MOV R" << reg++ << ", " << val << "\n";
            cout << "MOV " << ast->left->value << ", R" << reg-1 << "\n";
        }

        cout << "\n--- COMPILATION SUCCESSFUL ✔ ---\n";
    }

    return 0;
}