#include "ErrorHandler.h"
#include "InterpreterException.h"

void ErrorHandler::handleLexicalError(const LexicalError& error)
{
    std::cerr << "Error - unexpected characters:" << std::endl;

    const std::string& originalLine = error.getOriginalLine();
    if (originalLine.empty()) return;

    std::cerr << originalLine << std::endl;

    std::string errorLine(originalLine.length(), ' ');

    const std::vector<int>& errorPositions = error.getErrorPositions();

    for (int pos : errorPositions) {
        if (pos >= 0 && pos < errorLine.length()) {
            errorLine[pos] = '^';
        }
    }

    std::cerr << errorLine << std::endl;
}


void ErrorHandler::handleSyntaxError(const SyntaxError& error)
{
    std::cerr << "Syntax error: " << error.getMessage() << std::endl;
}

void ErrorHandler::handleCommandError(const CommandError& error)
{
    std::cerr << "Command error";
    if (!error.getCommandName().empty()) {
        std::cerr << " (" << error.getCommandName() << ")";
    }
    std::cerr << ": " << error.getMessage() << std::endl;
}

void ErrorHandler::handleFileError(const FileError& error)
{
    std::cerr << "File error";
    if (!error.getFilename().empty()) {
        std::cerr << " (" << error.getFilename() << ")";
    }
    std::cerr << ": " << error.getMessage() << std::endl;
}

void ErrorHandler::handleUnknownCommandError(const UnknownCommandError& error)
{
    std::cerr << "Unknown command: " << error.getCommandName() << std::endl;
}
