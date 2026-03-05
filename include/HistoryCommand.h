#ifndef CLI_HISTORYCOMMAND_H
#define CLI_HISTORYCOMMAND_H

#include "Command.h"

class HistoryCommand : public Command {
public:
    HistoryCommand() : Command("history") {}

    bool requiresArgument() const override { return false; }
    bool acceptsDirectInput() const override { return false; }
    bool argumentsAsInput() const override {return false; }

    void execute() override;
};

#endif //CLI_HISTORYCOMMAND_H