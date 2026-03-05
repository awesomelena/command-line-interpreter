#ifndef CLI_REPEATCOMMAND_H
#define CLI_REPEATCOMMAND_H

#include "Command.h"

class RepeatCommand : public Command {
public:
    RepeatCommand() : Command("repeat") {}

    bool acceptsDirectInput() const override { return true; }
    bool argumentsAsInput() const override { return true; }

    void execute() override;
};

#endif //CLI_REPEATCOMMAND_H