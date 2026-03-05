#ifndef CLI_INTERPRETEREXCEPTION_H
#define CLI_INTERPRETEREXCEPTION_H

#include "ErrorHandler.h"

#include <exception>
#include <vector>

class InterpreterException : public std::exception {
public:
    InterpreterException(const std::string& message, int position = -1) : message(message), position(position) {}
    virtual ~InterpreterException() = default;

    virtual const char* what() const noexcept override {return message.c_str();}
    virtual void accept(ErrorHandler& handler) const = 0;

    int getPosition() const {return position;}
    const std::string& getMessage() const {return message;}

protected:
    std::string message;
    int position;
};

class LexicalError : public InterpreterException {
public:
    LexicalError(const std::string& message, const std::string& line, const std::vector<int>& positions)
        : InterpreterException(message), originalLine(line), errorPositions(positions) {}

    LexicalError(const std::string& message, int position, const std::string& line = "")
        : InterpreterException(message, position), originalLine(line) {
        if (position >= 0) {
            errorPositions.push_back(position);
        }
    }

    void accept(ErrorHandler& handler) const override;
    const std::string& getOriginalLine() const {return originalLine;}
    const std::vector<int>& getErrorPositions() const {return errorPositions;}

private:
    std::string originalLine;
    std::vector<int> errorPositions;
};

class SyntaxError : public InterpreterException {
public:
    SyntaxError(const std::string& message, int position = -1) : InterpreterException(message, position) {}
    void accept(ErrorHandler& handler) const override;
};

class CommandError : public InterpreterException {
public:
    CommandError(const std::string& message, const std::string& command = "") : InterpreterException(message), commandName(command) {}

    void accept(ErrorHandler& handler) const override;
    const std::string& getCommandName() const {return commandName;}

private:
    std::string commandName;
};

class FileError : public InterpreterException {
public:
    FileError(const std::string& message, const std::string& file = "") : InterpreterException(message), fileName(file) {}

    void accept(ErrorHandler& handler) const override;
    const std::string& getFilename() const {return fileName;}

private:
    std::string fileName;
};

class UnknownCommandError : public InterpreterException {
public:
    UnknownCommandError(const std::string& command) : InterpreterException("Unknown Command: " + command), commandName(command) {}

    void accept(ErrorHandler& handler) const override;
    const std::string& getCommandName() const {return commandName;}

private:
    std::string commandName;
};

inline void LexicalError::accept(ErrorHandler& handler) const { handler.handleLexicalError(*this); }
inline void SyntaxError::accept(ErrorHandler& handler) const { handler.handleSyntaxError(*this); }
inline void CommandError::accept(ErrorHandler& handler) const { handler.handleCommandError(*this); }
inline void FileError::accept(ErrorHandler& handler) const { handler.handleFileError(*this); }
inline void UnknownCommandError::accept(ErrorHandler& handler) const  { handler.handleUnknownCommandError(*this); }

#endif //CLI_INTERPRETEREXCEPTION_H