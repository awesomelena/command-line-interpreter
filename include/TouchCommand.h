#ifndef CLI_TOUCHCOMMAND_H
#define CLI_TOUCHCOMMAND_H

#include "Command.h"

class TouchCommand : public Command {
public:
    TouchCommand() : Command("touch") {}

    bool requiresArgument() const override {return true;}
    bool acceptsDirectInput() const override {return false;}
    bool argumentsAsInput() const override {return false;}
    bool producesOutput() const override { return false; }

    void execute() override;
};

#endif //CLI_OUCHCOMMAND_H