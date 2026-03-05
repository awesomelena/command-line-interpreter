#include "CalcCommand.h"
#include <sstream>

void CalcCommand::execute() {
    std::string content = readInput();

    std::string expr;

    for (char c : content) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            expr += c;
        }
    }

    size_t opPos = std::string::npos;
    char op = '\0';

    for (size_t i = 1; i < expr.size(); ++i) {
        if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            opPos = i;
            op = expr[i];
            break;
        }
    }

    if (opPos == std::string::npos) {
        throw CommandError("invalid expression", name);
    }

    double left, right;

    try {
        left = std::stod(expr.substr(0, opPos));
        right = std::stod(expr.substr(opPos + 1));
    } catch (...) {
        throw CommandError("invalid numbers in expression", name);
    }

    double result;
    switch (op) {
        case '+': result = left + right; break;
        case '-': result = left - right; break;
        case '*': result = left * right; break;
        case '/':
            if (right == 0.0) {
                throw CommandError("division by zero", name);
            }
            result = left / right;
            break;
        default:
            throw CommandError("unknown operator", name);
    }

    streamManager.getOutputStream() << result << std::endl;
}