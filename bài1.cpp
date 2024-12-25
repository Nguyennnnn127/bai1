#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <cctype>

using namespace std;


bool kiemtra(const string &e) {
    int n = 0; 
    for (int i = 0; i < e.size(); i++) {
        char c = e[i];
        if (c == '(') n++;
        else if (c == ')') n--;
        if (n < 0) return false; 
    }
    return n == 0; 
}

bool applyOperator(char op, bool a, bool b = false) {
    if (op == '&') return a && b; 
    if (op == '|') return a || b; 
    if (op == '-') return !a || b; 
    if (op == '!') return !a; 
    return false;
}

bool evaluateExpression(const string &expr, const map<char, bool> &variables) {
    stack<bool> operands;  
    stack<char> operators; 

    for (int i = 0; i < expr.size(); i++) {
        char c = expr[i];

        
        if (isspace(c)) continue;

        if (isalpha(c)) { 
            operands.push(variables.at(c));
        } else if (c == '(') { 
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top(); operators.pop();
                bool val2 = operands.top(); operands.pop();
                bool val1 = (op != '!') ? operands.top() : false;
                if (op != '!') operands.pop();
                operands.push(applyOperator(op, val1, val2));
            }
            operators.pop(); 
        } else if (c == '&' || c == '|' || c == '-' || c == '!') { 
            while (!operators.empty() && operators.top() != '(' && (c != '!' || operators.top() == '!')) {
                char op = operators.top(); operators.pop();
                bool val2 = operands.top(); operands.pop();
                bool val1 = (op != '!') ? operands.top() : false;
                if (op != '!') operands.pop();
                operands.push(applyOperator(op, val1, val2));
            }
            operators.push(c);
        }
    }

    while (!operators.empty()) { 
        char op = operators.top(); operators.pop();
        bool val2 = operands.top(); operands.pop();
        bool val1 = (op != '!') ? operands.top() : false;
        if (op != '!') operands.pop();
        operands.push(applyOperator(op, val1, val2));
    }

    return operands.top();
}

int main() {
    string expression;
    cout << "Nhap bieu thuc logic (vi du: (A & B) -> C): ";
    getline(cin, expression);
    if (!kiemtra(expression)) {
        cout << "Bieu thuc không hop le!\n";
        return 1;
    }
    int n;
    cout << "Nhap so luong bien: ";
    cin >> n;

    map<char, bool> variables;
    for (int i = 0; i < n; ++i) {
        char var;
        bool value;
        cout << "Nhap ten bien va gia tri (vi du: A 1): ";
        cin >> var >> value;
        variables[var] = value;
    }
    try {
        bool result = evaluateExpression(expression, variables);
        cout << "Ket qua bieu thuc: " << (result ? "True" : "False") << endl;
    } catch (exception &e) {
        cout << "Loi: " << e.what() << endl;
    }

    return 0;
}
