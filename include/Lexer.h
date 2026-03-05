#ifndef CLI_LEXER_H
#define CLI_LEXER_H

#include "Types.h"

#include <vector>

class Lexer {
public:
    Lexer(const std::string& line);

    std::vector<Token> tokenize();

private:
    std::string input;
    size_t position;

    static const std::string VALID_SPECIAL_CHARS;
    static const std::string VALID_WHITESPACE;

    void skipWhitespace();

    bool isValidWhitespace(char c) const;
    bool isValidSpecialChar(char c) const;
    bool isValidWordChar(char c) const;

    void validateCharacters();

    std::string readQuotedString();
    std::string readWord();
};

#endif //CLI_LEXER_H