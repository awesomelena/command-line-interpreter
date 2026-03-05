#ifndef CLI_WRAPCOMMAND_H
#define CLI_WRAPCOMMAND_H

#include "Command.h"

class WrapCommand : public Command {
public:
    WrapCommand() : Command("split") {}

    bool acceptsDirectInput() const override { return true; }
    bool argumentsAsInput() const override { return true; }

    void execute() override;
};

#endif //CLI_WRAPCOMMAND_H