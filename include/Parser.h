#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#include "CommandFactory.h"
#include "Types.h"

#include <vector>

class Parser {
public:
    Parser(const std::vector<Token>& tokenList, CommandFactory& cmdFactory) : tokens(tokenList), currentToken(0), factory(cmdFactory) {}

    std::vector<Command*> parseCommandLine();

private:
    std::vector<Token> tokens;
    size_t currentToken;
    CommandFactory& factory;

    bool isNumber(const std::string& s);

    Command* parseSingleSegment(const std::vector<Token>& segment);

    void validatePipelineSemantics(const std::vector<Command*>& commands);
};

#endif //CLI_PARSER_H