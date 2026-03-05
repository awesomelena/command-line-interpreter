#ifndef CLI_MOVECOMMAND_H
#define CLI_MOVECOMMAND_H

#include "Command.h"

class MoveCommand : public Command {
public:
    MoveCommand() : Command("move") {}

    bool requiresArgument() const override {return true;}
    bool acceptsDirectInput() const override {return false;}
    bool argumentsAsInput() const override {return false;}
    bool producesOutput() const override {return false;}

    void execute() override;
};

#endif //CLI_MOVECOMMAND_H