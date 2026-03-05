#ifndef CLI_TEECOMMAND_H
#define CLI_TEECOMMAND_H

#include "Command.h"

class TeeCommand : public Command {
public:
    TeeCommand() : Command("tee") {}

    bool requiresArgument() const override { return true; }
    bool acceptsDirectInput() const override { return true; }
    bool argumentsAsInput() const override { return false; }

    void execute() override;
};

#endif //CLI_TEECOMMAND_H