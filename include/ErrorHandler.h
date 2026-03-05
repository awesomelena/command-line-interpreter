#ifndef CLI_ERRORHANDLER_H
#define CLI_ERRORHANDLER_H

#include <string>
#include <iostream>

class LexicalError;
class SyntaxError;
class CommandError;
class FileError;
class UnknownCommandError;

class ErrorHandler {
public:
    virtual ~ErrorHandler() = default;

    virtual void handleLexicalError(const LexicalError& error);
    virtual void handleSyntaxError(const SyntaxError& error);
    virtual void handleCommandError(const CommandError& error);
    virtual void handleFileError(const FileError& error);
    virtual void handleUnknownCommandError(const UnknownCommandError& error);
};

#endif //CLI_ERRORHANDLER_H