#ifndef CLI_COMMANDLINEINTERPRETER_H
#define CLI_COMMANDLINEINTERPRETER_H

#include <string>
#include <vector>

#include "CommandFactory.h"
#include "ErrorHandler.h"
#include "PipelineExecutor.h"
#include "SystemContext.h"

class CommandLineInterpreter : public SystemContext {
public:
    CommandLineInterpreter();

    void run();

    void processCommandLine(const std::string& line);

    void processLine(const std::string& line) override;

    void signalExit() override;
    void setPrompt(const std::string& newPrompt, bool oneTimeOnly) override;
    const std::vector<std::string>& getHistory() const override;
    void clearHistory() override;
    void addToHistory(const std::string &line) override;
    std::vector<std::string> getAvailableCommands() const override;

    void setAlias(const std::string &alias, const std::string &command) override;
    std::string resolveAlias(const std::string &name) override;

private:
    bool shouldExit;
    std::string prompt;
    std::string defaultPrompt;
    std::map<std::string, std::string> aliasMap;
    bool resetPromptNext;

    CommandFactory factory;
    ErrorHandler errorHandler;
    PipelineExecutor pipelineExecutor;

    std::vector<std::string> historyLog;
};

#endif //CLI_COMMANDLINEINTERPRETER_H