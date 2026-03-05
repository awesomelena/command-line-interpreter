#ifndef CLI_SYSTEMCONTEXT_H
#define CLI_SYSTEMCONTEXT_H

#include <vector>
#include <string>

class SystemContext {
public:
    virtual ~SystemContext() = default;

    virtual void signalExit() = 0;
    virtual void setPrompt(const std::string& newPrompt, bool oneTimeOnly) = 0;

    virtual const std::vector<std::string>& getHistory() const = 0;
    virtual void clearHistory() = 0;
    virtual void addToHistory(const std::string& line) = 0;
    virtual std::vector<std::string> getAvailableCommands() const = 0;
    virtual void processLine(const std::string& line) = 0;
    virtual void setAlias(const std::string& alias, const std::string& command) = 0;
    virtual std::string resolveAlias(const std::string& name) = 0;
};

#endif //CLI_SYSTEMCONTEXT_H