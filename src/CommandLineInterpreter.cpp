#include "CommandLineInterpreter.h"
#include "Lexer.h"
#include "Parser.h"
#include <iostream>
#include <sstream>

CommandLineInterpreter::CommandLineInterpreter() : prompt("$"), defaultPrompt("$"), resetPromptNext(false), shouldExit(false) {
    factory.setInterpreter(this);
}

void CommandLineInterpreter::signalExit() {
    shouldExit = true;
}

void CommandLineInterpreter::setPrompt(const std::string& newPrompt, bool oneTimeOnly) {
    prompt = newPrompt;
    if (!oneTimeOnly) {
        defaultPrompt = newPrompt;
    }
    resetPromptNext = oneTimeOnly;
}

void CommandLineInterpreter::setAlias(const std::string &alias, const std::string &command) {
    aliasMap[alias] = command;
}

std::string CommandLineInterpreter::resolveAlias(const std::string &name) {
    auto it = aliasMap.find(name);
    if (it != aliasMap.end()) {
        return it->second;
    }
    return name;
}

const std::vector<std::string>& CommandLineInterpreter::getHistory() const {
    return historyLog;
}

void CommandLineInterpreter::clearHistory() {
    historyLog.clear();
}

void CommandLineInterpreter::addToHistory(const std::string &line) {
    historyLog.push_back(line);
}

std::vector<std::string> CommandLineInterpreter::getAvailableCommands() const {
    return factory.getAvailableCommands();
}

void CommandLineInterpreter::run() {
    std::string line;

    while (!shouldExit) {
        try {
            if (std::cin.eof()) {
                std::cin.clear();
            }

            std::cout << prompt << " " << std::flush;

            if (!std::getline(std::cin, line)) {
                break;
            }

            if (resetPromptNext) {
                prompt = defaultPrompt;
                resetPromptNext = false;
            }

            if (line.empty()) continue;

            historyLog.push_back(line);

            processCommandLine(line);
        }
        catch (InterpreterException& e) {
            e.accept(errorHandler);
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        catch (...) {
            std::cout << "Unexpected error!" << std::endl;
        }
    }
}

void CommandLineInterpreter::processCommandLine(const std::string& line) {
    Lexer lexer(line);
    std::vector<Token> tokens = lexer.tokenize();
    if (tokens.empty()) return;

    Parser parser(tokens, factory);
    std::vector<Command*> commands = parser.parseCommandLine();

    try {
        pipelineExecutor.execute(commands);

        for (Command* cmd : commands) delete cmd;
    }
    catch (InterpreterException& e) {
        e.accept(errorHandler);
        for (Command* cmd : commands) delete cmd;
    }
    catch (...) {
        for (Command* cmd : commands) delete cmd;
        throw;
    }
}

void CommandLineInterpreter::processLine(const std::string& line) {
    processCommandLine(line);
}