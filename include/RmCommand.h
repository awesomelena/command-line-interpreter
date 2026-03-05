#ifndef CLI_RMCOMMAND_H
#define CLI_RMCOMMAND_H

#include "Command.h"

class RmCommand : public Command {
public:
    RmCommand() : Command("rm") {};

    bool requiresArgument() const override { return true; }
    bool acceptsDirectInput() const override { return false; }
    bool argumentsAsInput() const override { return false; }

    void execute() override;
};

#endif //CLI_RMCOMMAND_H