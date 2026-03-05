#ifndef CLI_BETWEENCOMMAND_H
#define CLI_BETWEENCOMMAND_H

#include "Command.h"

class BetweenCommand : public Command {
public:
    BetweenCommand() : Command("between") {}

    bool acceptsDirectInput() const override { return true; }
    bool argumentsAsInput() const override { return true; }

    void execute() override;
};

#endif //CLI_BETWEENCOMMAND_H