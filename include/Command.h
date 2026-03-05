#ifndef CLI_COMMAND_H
#define CLI_COMMAND_H

#include "Types.h"
#include "StreamManager.h"
#include "InterpreterException.h"
#include "SystemContext.h"

#include <vector>
#include <string>
#include <algorithm>

class PipelineExecutor;

class Command {
public:
    Command(const std::string& commandName) : name(commandName), context(nullptr) {}
    virtual ~Command() {}

    virtual void execute() = 0;

    virtual bool requiresArgument() const {return false;}
    virtual bool acceptsDirectInput() const {return true;}
    virtual bool argumentsAsInput() const {return true;}
    virtual bool producesOutput() const { return true; }

    void addOption(const std::string& option) {options.push_back(option);}
    void addArgument(const std::string& argument, bool isLiteral) {arguments.push_back(argument); isArgumentLiteral.push_back(isLiteral);}
    void setIORedirection(const IORedirection& ioRedir) { io = ioRedir; }
    void setContext(SystemContext* ctx) { context = ctx; }

    const std::string& getName() const {return name;}
    const std::vector<std::string>& getOptions() const {return options;}
    const std::vector<std::string>& getArguments() const {return arguments;}
    const IORedirection& getIO() const {return io;}

    bool hasOption(const std::string& option) const;

    virtual void run();

    friend class CommandFactory;
    friend class PipelineExecutor;

protected:
    std::string readInput();
    std::string name;
    std::vector<std::string> options;
    std::vector<std::string> arguments;
    std::vector<bool> isArgumentLiteral;
    StreamManager streamManager;
    IORedirection io;
    SystemContext* context;
};

#endif //CLI_COMMAND_H