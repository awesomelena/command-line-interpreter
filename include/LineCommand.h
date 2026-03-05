#ifndef CLI_LINECOMMAND_H
#define CLI_LINECOMMAND_H

#include "Command.h"

class LineCommand : public Command {
public:
    LineCommand() : Command("line") {}

    bool acceptsDirectInput() const override { return true; }
    bool argumentsAsInput() const override { return true; }

    void execute() override;
};

#endif //CLI_LINECOMMAND_H