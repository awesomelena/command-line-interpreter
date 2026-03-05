#ifndef CLI_TYPES_H
#define CLI_TYPES_H

#include <string>

enum class TokenType {
    WORD, QUOTED_STRING, PIPE, INPUT_REDIRECT, OUTPUT_REDIRECT, APPEND_REDIRECT
};

struct Token {
    TokenType type;
    std::string value;
    int position;

    Token(TokenType type, const std::string& value, int position)
        : type(type), value(value), position(position) {}
};

struct IORedirection {
    bool hasInputRedirect = false;
    bool hasOutputRedirect = false;
    bool appendOutput = false;
    std::string inputFile;
    std::string outputFile;

    friend bool operator == (const IORedirection& lhs, const IORedirection& rhs) {
        return lhs.hasInputRedirect == rhs.hasInputRedirect &&
               lhs.hasOutputRedirect == rhs.hasOutputRedirect &&
               lhs.appendOutput == rhs.appendOutput &&
               lhs.inputFile == rhs.inputFile &&
               lhs.outputFile == rhs.outputFile;
    }
};

#endif //CLI_TYPES_H