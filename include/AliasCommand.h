#ifndef CLI_ALIASCOMMAND_H
#define CLI_ALIASCOMMAND_H

#include "Command.h"

class AliasCommand : public Command {
public:
    AliasCommand() : Command("alias") {}

    bool requiresArgument() const override {return true;}
    bool acceptsDirectInput() const override {return false;}
    bool argumentsAsInput() const override {return false;}
    bool producesOutput() const override {return false;}

    void execute() override;
};

#endif //CLI_ALIASCOMMAND_H