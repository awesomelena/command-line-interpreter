#ifndef CLI_SPLITCOMMAND_H
#define CLI_SPLITCOMMAND_H

#include "Command.h"

class SplitCommand : public Command {
public:
    SplitCommand() : Command("split") {}

    bool acceptsDirectInput() const override { return true; }
    bool argumentsAsInput() const override { return false; }

    void execute() override;
};

#endif //CLI_SPLITCOMMAND_H