#include "Lexer.h"
#include "InterpreterException.h"
#include <iostream>
#include <cctype>

const std::string Lexer::VALID_SPECIAL_CHARS = "|<>";
const std::string Lexer::VALID_WHITESPACE = " \t\r";

Lexer::Lexer(const std::string& line) : position(0) {

    if (line.length() > 512) {
        input = line.substr(0, 512);
    } else {
        input = line;
    }
}

void Lexer::skipWhitespace()
{
    while (position < input.length() && isValidWhitespace(input[position])) {
        position++;
    }
}

bool Lexer::isValidWhitespace(char c) const
{
    return VALID_WHITESPACE.find(c) != std::string::npos;
}

bool Lexer::isValidSpecialChar(char c) const
{
    return VALID_SPECIAL_CHARS.find(c) != std::string::npos;
}

bool Lexer::isValidWordChar(char c) const
{
    return std::isalnum(static_cast<unsigned char>(c)) ||
           c == '.' ||
           c == '_' ||
           c == '-' ||
           c == '/' ||
           c == '\\' ||
           c == ':';
}

void Lexer::validateCharacters()
{
    std::vector<int> invalidPositions;
    bool insideQuotes = false;

    for (size_t i = 0; i < input.length(); i++) {
        char c = input[i];

        if (c == '"') {
            insideQuotes = !insideQuotes;
            continue;
        }

        if (insideQuotes) {
            if (c == '\n') {
                invalidPositions.push_back(i);
            }
            continue;
        }

        if (!isValidWhitespace(c) && !isValidSpecialChar(c) && !isValidWordChar(c) && c != '"') {
            invalidPositions.push_back(i);
        }
    }

    if (!invalidPositions.empty()) {
        throw LexicalError("Unexpected characters", input, invalidPositions);
    }

    if (insideQuotes) {
        throw LexicalError("Unterminated quoted string", input, std::vector<int>());
    }
}

std::string Lexer::readQuotedString()
{
    size_t start = position;
    position++;
    std::string result;

    while (position < input.length() && input[position] != '"') {
        result += input[position];
        position++;
    }

    if (position >= input.length()) {
        throw LexicalError("Unterminated quoted string", start, input);
    }

    position++;
    return result;
}

std::string Lexer::readWord()
{
    std::string result;
    while (position < input.length() && isValidWordChar(input[position])) {
        result += input[position];
        position++;
    }
    return result;
}

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;
    position = 0;

    validateCharacters();

    while (position < input.length()) {
        skipWhitespace();
        if (position >= input.length()) break;

        char c = input[position];
        size_t tokenStart = position;

        if (c == '"') {
            std::string quoted = readQuotedString();
            tokens.emplace_back(TokenType::QUOTED_STRING, quoted, tokenStart);
        }
        else if (c == '|') {
            tokens.emplace_back(TokenType::PIPE, "|", tokenStart);
            position++;
        }
        else if (c == '<') {
            tokens.emplace_back(TokenType::INPUT_REDIRECT, "<", tokenStart);
            position++;
        }
        else if (c == '>') {
            if (position + 1 < input.length() && input[position + 1] == '>') {
                tokens.emplace_back(TokenType::APPEND_REDIRECT, ">>", tokenStart);
                position += 2;
            } else {
                tokens.emplace_back(TokenType::OUTPUT_REDIRECT, ">", tokenStart);
                position++;
            }
        }
        else if (c == '-') {
            if (position + 1 < input.length() && input[position + 1] == '"') {
                tokens.emplace_back(TokenType::WORD, "-", tokenStart);
                position++;
                std::string quoted = readQuotedString();
                tokens.emplace_back(TokenType::QUOTED_STRING, quoted, position - quoted.length() - 1);
            }
            else {
                std::string word = readWord();
                if (word.empty()) {
                    tokens.emplace_back(TokenType::WORD, "-", tokenStart);
                    position++;
                } else {
                    tokens.emplace_back(TokenType::WORD, word, tokenStart);
                }
            }
        }
        else {
            std::string word = readWord();
            if (word.empty()) {
                throw LexicalError("Unexpected character", position, input);
            }
            tokens.emplace_back(TokenType::WORD, word, tokenStart);
        }
    }

    return tokens;
}