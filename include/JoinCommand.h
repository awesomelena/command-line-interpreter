#ifndef CLI_JOINCOMMAND_H
#define CLI_JOINCOMMAND_H

#include "Command.h"

class JoinCommand : public Command {
public:
    JoinCommand() : Command("join") {}

    bool acceptsDirectInput() const override { return true; }
    bool argumentsAsInput() const override { return false; }

    void execute() override;
};

#endif //CLI_JOINCOMMAND_H