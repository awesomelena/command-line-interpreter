#ifndef CLI_DIFFCOMMAND_H
#define CLI_DIFFCOMMAND_H

#include "Command.h"

class DiffCommand : public Command {
public:
    DiffCommand() : Command("diff") {}

    bool requiresArgument() const override {return true;}
    bool argumentsAsInput() const override {return false;}
    bool acceptsDirectInput() const override {return true;}

    void execute() override;
};

#endif //CLI_DIFFCOMMAND_H