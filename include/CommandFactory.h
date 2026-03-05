#ifndef CLI_COMMANDFACTORY_H
#define CLI_COMMANDFACTORY_H

#include "Command.h"

#include <string>
#include <vector>
#include <map>
#include <functional>

class CommandLineInterpreter;

class CommandFactory {
public:
    CommandFactory();

    ~CommandFactory();

    Command* createCommand(const std::string& name);

    bool isValidCommand(const std::string& name) const;

    std::vector<std::string> getAvailableCommands() const;

    void setInterpreter(CommandLineInterpreter* interp) { interpreter = interp; }

    CommandLineInterpreter* getInterpreter() const { return interpreter; }

private:
    CommandLineInterpreter* interpreter = nullptr;
    using CommandCreator = std::function<Command*()>;
    std::map<std::string, CommandCreator> commandRegistry;

    void registerCommands();
};

#endif //CLI_COMMANDFACTORY_H