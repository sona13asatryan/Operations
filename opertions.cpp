#include <iostream> 
#include <stack>

// I used this articles
// https://runestone.academy/ns/books/published/pythonds/BasicDS/InfixPrefixandPostfixExpressions.html
// https://quescol.com/data-structure/infix-to-prefix

void validate(std::string exp) {
    if (exp.size() < 3 || !exp.size()%2) {
        std::cerr << "Not an expression, try again!" << std::endl;
        std::abort();
    }
    for (int i = 0; i< exp.size(); i += 2) {
        if (exp[i] <= '0' || exp[i] >= '9') {
            std::cerr << "Not an expression, try again!" << std::endl;
            std::abort();
        }
    }
    for (int i = 1; i< exp.size(); i += 2) {
        if (exp[i] != '+' && exp[i] != '*') {
            std::cerr << "Not an expression, try again!" << std::endl;
            std::abort();
        }
    }
}   


std::string prefix (std::string exp) {

    std::string answer = "";
    std::stack<char> s;

    for (int i = exp.size()-1; i >=0 ; --i) {
        if ('0' <= exp[i] && exp[i] <= '9') {
            answer = exp[i] + answer;
        } else if (exp[i] == '+' || exp[i] == '*') {
            if (s.empty()) {
                s.push(exp[i]);
                continue;
            }
            if (exp[i] == '*' && s.top() == '+') {
                s.push(exp[i]);
            } else if (exp[i] == '+' && s.top() == '*') {
                while (!s.empty() && s.top() != '+') {
                    answer = s.top() + answer;
                    s.pop();
                }
                s.push(exp[i]);
            } else if (exp[i] == s.top()) {
                s.push(exp[i]);
            }
        }
    }
    while (!s.empty()) {
        answer = s.top() + answer;
        s.pop();
    }
    return answer;
}

int solve(std::string exp) {
    std::stack<int> s;
    for (int i = exp.size()-1 ; i >= 0; --i) {
        if('0' <= exp[i] && exp[i] <= '9') {
            s.push(exp[i] - '0');
        } else {
            int temp1 = s.top();
            s.pop();
            int temp2 = s.top();
            s.pop();
            if (exp[i] == '+') {
                s.push(temp1 + temp2);
            } else {
                s.push(temp1 * temp2);
            }
        }
    }
    return s.top();
}

int main() {

    std::string expression;
    std::cout << "Enter a numerical expression using only +, * and single digit numbers!" << std::endl;
    std::cin >> expression;
    validate(expression);
    int result = solve(prefix(expression));
    std::cout << result;

    return 0;
}