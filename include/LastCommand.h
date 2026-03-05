#ifndef CLI_LASTCOMMAND_H
#define CLI_LASTCOMMAND_H

#include "Command.h"

class LastCommand : public Command {
public:
    LastCommand() : Command("last") {}

    bool requiresArgument() const override {return false;}
    bool argumentsAsInput() const override {return false;}
    bool acceptsDirectInput() const override {return true;}

    void execute() override;
};

#endif //CLI_LASTCOMMAND_H