#include "Parser.h"
#include "TrCommand.h"
#include "HeadCommand.h"
#include <cctype>
#include <algorithm>

#include "CommandLineInterpreter.h"

bool Parser::isNumber(const std::string &s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!std::isdigit(c)) return false;
    }
    return true;
}

Command* Parser::parseSingleSegment(const std::vector<Token>& segment) {
    if (segment.empty()) return nullptr;

    size_t localIdx = 0;

    const Token& nameToken = segment[localIdx++];
    if (nameToken.type != TokenType::WORD) {
        throw SyntaxError("Expected command name", nameToken.position);
    }

    std::string commandName = nameToken.value;

    if (factory.getInterpreter()) {
        commandName = factory.getInterpreter()->resolveAlias(commandName);
    }

    Command* command = factory.createCommand(commandName);

    try {
        IORedirection io;

        while (localIdx < segment.size()) {
            const Token& token = segment[localIdx];

            if (token.type == TokenType::INPUT_REDIRECT) {
                if (io.hasInputRedirect) throw SyntaxError("Multiple input redirections");
                localIdx++;
                if (localIdx >= segment.size()) throw SyntaxError("Expected filename after '<'");
                io.hasInputRedirect = true;
                io.inputFile = segment[localIdx++].value;
            }
            else if (token.type == TokenType::OUTPUT_REDIRECT) {
                if (io.hasOutputRedirect) throw SyntaxError("Multiple output redirections");
                localIdx++;
                if (localIdx >= segment.size()) throw SyntaxError("Expected filename after '>'");
                io.hasOutputRedirect = true;
                io.appendOutput = false;
                io.outputFile = segment[localIdx++].value;
            }
            else if (token.type == TokenType::APPEND_REDIRECT) {
                if (io.hasOutputRedirect) throw SyntaxError("Multiple output redirections");
                localIdx++;
                if (localIdx >= segment.size()) throw SyntaxError("Expected filename after '>>'");
                io.hasOutputRedirect = true;
                io.appendOutput = true;
                io.outputFile = segment[localIdx++].value;
            }
            else if (token.type == TokenType::WORD) {
                if (token.value.length() > 1 && token.value[0] == '-') {
                    command->addOption(token.value);
                } else {
                    command->addArgument(token.value, false);
                }
                localIdx++;
            }
            else if (token.type == TokenType::QUOTED_STRING) {
                command->addArgument(token.value, true);
                localIdx++;
            }
            else {
                throw SyntaxError("Unexpected token", token.position);
            }
        }

        command->setIORedirection(io);

    } catch (...) {
        delete command;
        throw;
    }

    return command;
}

void Parser::validatePipelineSemantics(const std::vector<Command*>& commands) {
    for (size_t i = 0; i < commands.size(); ++i) {
        Command* cmd = commands[i];
        bool isFirst = (i == 0);
        bool isLast = (i == commands.size() - 1);

        const IORedirection& io = cmd->getIO();

        if (!isFirst && !cmd->acceptsDirectInput()) {
            throw SyntaxError("Command '" + cmd->getName() + "' cannot receive piped input");
        }
        if (!isFirst && io.hasInputRedirect) {
            throw SyntaxError("Input redirection only allowed on first command in pipe");
        }
        if (!isLast && io.hasOutputRedirect) {
            throw SyntaxError("Output redirection only allowed on last command in pipe");
        }
    }
}

std::vector<Command*> Parser::parseCommandLine() {
    std::vector<Command*> commands;
    if (tokens.empty()) return commands;

    std::vector<std::vector<Token>> segments;
    std::vector<Token> currentSegment;

    for (const auto& token : tokens) {
        if (token.type == TokenType::PIPE) {
            if (currentSegment.empty()) throw SyntaxError("Empty pipe segment");
            segments.push_back(currentSegment);
            currentSegment.clear();
        } else {
            currentSegment.push_back(token);
        }
    }
    if (!currentSegment.empty()) {
        segments.push_back(currentSegment);
    } else if (!segments.empty()) {
        throw SyntaxError("Trailing pipe");
    }

    /*
     * if we want to reverse pipeline execution order (just for fun)
     *
     *bool reverseMode = false;
      if (!segments.empty()) {
          const auto& lastSeg = segments.back();
          if (lastSeg.size() == 1 && lastSeg[0].type == TokenType::WORD && lastSeg[0].value == "rev") {
              reverseMode = true;
              segments.pop_back();
          }
      }

     if (reverseMode) {
         std::reverse(segments.begin(), segments.end());
     }
     */

    try {
        for (size_t i = 0; i < segments.size(); ++i) {
            if (segments[i].size() == 1 && segments[i][0].type == TokenType::WORD && isNumber(segments[i][0].value)) {
                int refIndex = std::stoi(segments[i][0].value);

                if (refIndex < 1 || refIndex > static_cast<int>(segments.size())) {
                    throw SyntaxError("Numeric command reference out of range");
                }
                segments[i] = segments[refIndex - 1];
            }

            Command* cmd = parseSingleSegment(segments[i]);
            if (cmd) {
                commands.push_back(cmd);
            }
        }

        validatePipelineSemantics(commands);

    } catch (...) {
        for (Command* c : commands) delete c;
        throw;
    }

    return commands;
}